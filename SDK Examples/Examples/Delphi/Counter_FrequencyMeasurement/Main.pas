unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, jpeg, StdCtrls, ComCtrls, DaqUtils, OleCtrls,
  BDaqOcxLib_TLB;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    DataView: TPaintBox;
    yTLabel: TLabel;
    yMLabel: TLabel;
    yBLabel: TLabel;
    Enlarge: TImage;
    Shorten: TImage;
    xLLabel: TLabel;
    xRLabel: TLabel;
    Label1: TLabel;
    timerValueLabel: TLabel;
    timerTrackBar: TTrackBar;
    BtnStart: TButton;
    BtnPause: TButton;
    BtnStop: TButton;
    fm1_Label: TLabel;
    fm2_Label: TLabel;
    Timer1: TTimer;
    FreqMeterCtrl1: TFreqMeterCtrl;
    FreqMeterCtrl2: TFreqMeterCtrl;
    procedure FormCreate(Sender: TObject);
    procedure timerTrackBarChange(Sender: TObject);
    procedure EnlargeClick(Sender: TObject);
    procedure ShortenClick(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure BtnPauseClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
    m_graph : TSimpleGraph;
    frequency : array[0..1] of Double;
    m_yaxisMax : Double;
    isCounterReseted : Boolean;
    procedure SetFormTitle;
    procedure InitializeYAxis;
    procedure InitializeGraph;
    function FormatFreqString(freqHz : Double) : string;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

procedure TMainForm.FormCreate(Sender: TObject);
begin
   //The default device of project is demo device, users can choose other devices according to their needs.
   if not FreqMeterCtrl1.Initialized and not FreqMeterCtrl2.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'FrequencyMeasurement', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   SetFormTitle; 

   m_yaxisMax := 1000000;  // default is 1MHz
   isCounterReseted := true;
   
   self.DoubleBuffered := true;
   
   m_graph := TSimpleGraph.Create(dataView);

   //initialize the value of label
   fm1_Label.Color := m_graph.GetPlotColor(0);
   fm1_Label.Caption := '0.0';
   fm2_label.Color := m_graph.GetPlotColor(1);
   fm2_label.Caption := '0.0';

   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := false;

   InitializeGraph;
end;

procedure TMainForm.SetFormTitle;
var
   devNum1 : Longint;
   devNum2 : Longint;
   devDesc1 : WideString;
   devDesc2 : WideString;
   devMode : AccessMode;
   modIndex : Longint;
begin
   FreqMeterCtrl1.getSelectedDevice(devNum1, devDesc1, devMode, modIndex);
   FreqMeterCtrl2.getSelectedDevice(devNum2, devDesc2, devMode, modIndex);

   if not VarIsNull(devDesc1) And VarIsNull(devDesc2) Then
        self.Caption := 'Frequency Measurement(' + devDesc1 + ')'
    Else
        if VarIsNull(devDesc1) And not VarIsNull(devDesc2) Then
            self.Caption := 'Frequency Measurement(' + devDesc2 + ')'
        Else
            If devNum1 = devNum2 Then
               self.Caption := 'Frequency Measurement(' + devDesc1 + ')'
            Else
               self.Caption := 'Frequency Measurement(' + devDesc1 + ',' + devDesc2 + ')';
end;

procedure TMainForm.timerTrackBarChange(Sender: TObject);
begin
   Timer1.Interval := timerTrackBar.Position;
   timerValueLabel.Caption := IntToStr(timerTrackBar.Position) + 'ms';
   m_graph.Clear;
end;

procedure TMainForm.InitializeGraph;
begin
   m_graph.XCordTimeDiv := 1000;
   InitializeYAxis;
   m_graph.Clear;
end;

procedure TMainForm.InitializeYAxis;
begin
   m_graph.YCordMax := m_yaxisMax;
   m_graph.YCordMin := 0;
   yTLabel.Caption := FormatFreqString(m_yaxisMax);
   yMLabel.Caption := FormatFreqString(m_yaxisMax / 2);
end;

function TMainForm.FormatFreqString(freqHz : Double) : string;
const
   freqUnits : array[0..3] of string = ('Hz', 'KHz', 'MHz', 'GHz');
var
   i : Integer;
begin
   for i := 0 to 2 do
      if freqHz < 1000 then
         break
      else
         freqHz := freqHz / 1000;

   Result := FloatToStr(freqHz) + freqUnits[i];
end;

procedure TMainForm.EnlargeClick(Sender: TObject);
begin
   if m_yaxisMax < 10000000 then
   begin
      m_graph.Clear;
      m_yaxisMax := m_yaxisMax * 10;
      InitializeYAxis;
   end;
end;

procedure TMainForm.ShortenClick(Sender: TObject);
begin
   if m_yaxisMax > 1 then
   begin
      m_graph.Clear;
      m_yaxisMax := m_yaxisMax / 10;
      InitializeYAxis;
   end;
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   if isCounterReseted = True then
   begin
      if FreqMeterCtrl1.Initialized and not (FreqMeterCtrl1.Channel = -1) then
         FreqMeterCtrl1.Enabled := true;

      if FreqMeterCtrl2.Initialized and not (FreqMeterCtrl2.Channel = -1) then
         FreqMeterCtrl2.Enabled := true;

      BtnStop.Enabled := true;
   end;

   Timer1.Enabled := true;
   BtnPause.Enabled := true;
   BtnStart.Enabled := false;
end;

procedure TMainForm.BtnPauseClick(Sender: TObject);
begin
   Timer1.Enabled := false;
   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := true;
   isCounterReseted := false;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   if FreqMeterCtrl1.Enabled = true then
      FreqMeterCtrl1.Enabled := false;

   if FreqMeterCtrl2.Enabled = true then
      FreqMeterCtrl2.Enabled := false;

   Timer1.Enabled := false;
   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := false;
   isCounterReseted := true;
   m_graph.Clear;
end;

procedure TMainForm.Timer1Timer(Sender: TObject);
begin
   if FreqMeterCtrl1.Initialized and not (FreqMeterCtrl1.Channel = -1) then
      frequency[0] := FreqMeterCtrl1.Value
   else
      frequency[0] := 0.0;

   if FreqMeterCtrl2.Initialized and not (FreqMeterCtrl2.Channel = -1) then
      frequency[1] := FreqMeterCtrl2.Value
   else
      frequency[1] := 0.0;

   fm1_Label.Caption := Format('%.1f', [frequency[0]]);
   fm2_Label.Caption := Format('%.1f', [frequency[1]]);

   m_graph.Chart(frequency, 2, 1, Timer1.Interval / 1000); 

end;

end.
