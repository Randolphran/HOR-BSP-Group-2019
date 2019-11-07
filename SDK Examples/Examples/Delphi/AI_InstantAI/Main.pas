unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, DaqUtils, ExtCtrls, StdCtrls, ComCtrls, OleCtrls, BDaqOcxLib_TLB;

const
  CHANNEL_COUNT_MAX = 16;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    DataView: TPaintBox;
    yTLabel: TLabel;
    yMLabel: TLabel;
    yBLabel: TLabel;
    chanDataList: TListView;
    xLLabel: TLabel;
    xRLabel: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    timerIntvlEditor: TEdit;
    Label4: TLabel;
    timerTrackBar: TTrackBar;
    BtnStart: TButton;
    BtnPause: TButton;
    BtnStop: TButton;
    label_chanStart: TLabel;
    comboBox_chanStart: TComboBox;
    label_Count: TLabel;
    comboBox_chanCount: TComboBox;
    Timer1: TTimer;
    InstantAiCtrl1: TInstantAiCtrl;
    procedure BtnStartClick(Sender: TObject);
    procedure BtnPauseClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure timerTrackBarChange(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure comboBox_chanCountChange(Sender: TObject);
    procedure chanDataListCustomDrawSubItem(Sender: TCustomListView;
      Item: TListItem; SubItem: Integer; State: TCustomDrawState;
      var DefaultDraw: Boolean);
  private
    { Private declarations }
    m_graph : TSimpleGraph;
    chanCount : Integer;
    chanCountSet : Integer;
    chanCountMax : Integer;
    procedure HandleError(err : ErrorCode);
    procedure InitListView;
    procedure InitializeGraph;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}



procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   Timer1.Enabled := true;
   BtnStart.Enabled := false;
   BtnPause.Enabled := true;
   BtnStop.Enabled := true;
end;

procedure TMainForm.BtnPauseClick(Sender: TObject);
begin
   Timer1.Enabled := false;
   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   Timer1.Enabled := false;
   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := false;
   m_graph.Clear;
   InitListView;
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
   i, j, k : Integer;
   item : TListItem;
   devNum : Longint;
   devDesc : WideString;
   devMode : AccessMode;
   modIndex : Longint;
begin
   //The default device of project is demo device, users can choose other devices according to their needs.
   if not InstantAiCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'InstantAI', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;
   
   //set title of the form.
   InstantAiCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Instant AI(' + devDesc + ')';

   chanCountMax := InstantAiCtrl1.Features.ChannelCountMax;

   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := false;

   self.DoubleBuffered := true;

   //initialize a graph with a paint box control to draw Ai data.
   m_graph := TSimpleGraph.Create(dataView);

   //initialize a timer which drive the data acquisition.
   Timer1.Interval := timerTrackBar.Position;

   timerIntvlEditor.Text := IntToStr(timerTrackBar.Position);

   //Add combo Box  to select start channel and channel count
   if InstantAiCtrl1.ChannelCount <= CHANNEL_COUNT_MAX then
      chanCount := InstantAiCtrl1.ChannelCount
   else
      chanCount := CHANNEL_COUNT_MAX;

   for k := 0 to chanCount - 1 do
   begin
      comboBox_chanStart.AddItem(IntToStr(k), self);
      comboBox_chanCount.AddItem(IntToStr(k + 1), self);
   end;

   comboBox_chanStart.ItemIndex := 0;
   comboBox_chanCount.ItemIndex := 2;

   //initialize the chancountset
   chanCountSet := 3;


   chanDataList.SmallImages := TImageList.Create(self);
   chanDataList.SmallImages.Height := 22;
   for i := 0 to 1 do
   begin
      item := chanDataList.Items.Add;
      for j := 0 to 8 do
         item.SubItems.Add('  ');
   end;

   InitializeGraph;
   InitListView;

end;

procedure TMainForm.timerTrackBarChange(Sender: TObject);
begin
   Timer1.Interval := TTrackBar(Sender).Position;
   timerIntvlEditor.Text := IntToStr(Timer1.Interval);
   m_graph.Clear;
end;

procedure TMainForm.Timer1Timer(Sender: TObject);
var
   dataScaled : OleVariant;
   dataRaw : OleVariant;
   dataScaledArray : array of Double;
   i : Integer;
   err : ErrorCode;
begin
   //read data.
   dataScaled := VarArrayCreate([0, CHANNEL_COUNT_MAX - 1], varDouble);
   err := InstantAiCtrl1.ReadChannels(comboBox_chanStart.ItemIndex, chanCountSet, dataRaw, dataScaled);
   if err <> Success then
   begin
      HandleError(err);
      Timer1.Enabled := false;
   end;

   //draw the data to the PaintBox
   dataScaledArray := dataScaled;
   m_graph.Chart(dataScaledArray, chanCountSet, 1, timerTrackBar.Position / 1000.0);
    
   for i := 0 to chanCountSet - 1 do
      chanDataList.Items[i div 8].SubItems[i mod 8] := Format('%.4f', [Double(dataScaled[i])]);
end;

procedure TMainForm.HandleError(err : ErrorCode);
var
   utility : IBDaqUtility;
   errorMessage : WideString;
begin
   utility := CoBDaqUtility.Create();
   utility.EnumToString('ErrorCode', err, errorMessage);

   if err <> Success then
      MessageBox(0, PChar(Format('Read AI channel failed with error: %s!', [errorMessage])), 'Error', MB_OK or MB_ICONERROR);
end;

procedure TMainForm.comboBox_chanCountChange(Sender: TObject);
begin
   m_graph.Clear;
   chanCountSet := comboBox_chanCount.ItemIndex + 1;
   InitListView;
end;

procedure TmainForm.InitListView;
var
   i : Integer;
begin
   for i := 0 to 15 do
     if i < chanCountSet then
        chanDataList.Items[i div 8].SubItems[i mod 8] := Format('%.4f',[0.0])
     else
        chanDataList.Items[i div 8].SubItems[i mod 8] := '  ';
end;

procedure TMainForm.chanDataListCustomDrawSubItem(Sender: TCustomListView;
  Item: TListItem; SubItem: Integer; State: TCustomDrawState;
  var DefaultDraw: Boolean);
var
   plot : Integer;
   clr  : TColor;
begin
   plot := Item.Index * 8 + SubItem - 1;

   if plot < chanCountSet then
      clr := m_graph.GetPlotColor(plot)
   else
      clr := clWhite;
      
   Sender.Canvas.Brush.Color := clr;
end;

procedure TMainForm.InitializeGraph;
var
   vrgUnit  : ValueUnit;
   vrgRange : MathInterval;
   ustr     : string;
begin
   //X-Axis
   m_graph.XCordTimeDiv := 1000;

   // Y-Axis
   vrgRange.Max := 10;
   vrgRange.Min := -10;
   vrgUnit := Volt;
   m_graph.YCordMax := vrgRange.Max;
   m_graph.YCordMin := vrgRange.Min;
   case vrgUnit of
      Kilovolt: ustr := 'kV';
      Volt:     ustr := 'V';
      Millivolt:
      begin
         ustr := 'mV';
         // the data from device is 'Voltage'
         m_graph.YCordMax := vrgRange.Max / 1000;
         m_graph.YCordMin := vrgRange.Min / 1000;
      end;
      Microvolt:
      begin
         ustr := 'uV';
         // the data from device is 'Voltage'
         m_graph.YCordMax := vrgRange.Max / (1000 * 1000);
         m_graph.YCordMin := vrgRange.Min / (1000 * 1000);
      end;
      Kiloampere:  ustr := 'kA';
      Ampere:      ustr := 'A';
      Milliampere: ustr := 'mA';
      Microampere: ustr := 'uA';
      CelsiusUnit: ustr := 'C';
   end;

   yTLabel.Caption := FloatToStr(vrgRange.Max) + ustr;
   yMLabel.Caption := FloatToStr((vrgRange.Max + vrgRange.Min) / 2) + ustr;
   yBLabel.Caption := FloatToStr(vrgRange.Min) + ustr;

   m_graph.Clear;
end;

end.

