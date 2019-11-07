unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, ComCtrls, DaqUtils, OleCtrls, BDaqOcxLib_TLB, Math;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    DataView: TPaintBox;
    yTLabel: TLabel;
    yMLabel: TLabel;
    yBLabel: TLabel;
    xLLabel: TLabel;
    xRLabel: TLabel;
    Label1: TLabel;
    chanDataList: TListView;
    Label2: TLabel;
    shiftTimeEditor: TEdit;
    shiftTimeLabel: TLabel;
    shiftTrackBar: TTrackBar;
    Label3: TLabel;
    divTimeEditor: TEdit;
    divTimeLabel: TLabel;
    divTrackBar: TTrackBar;
    BtnStart: TButton;
    BufferedAiCtrl1: TBufferedAiCtrl;
    procedure FormCreate(Sender: TObject);
    procedure chanDataListCustomDrawSubItem(Sender: TCustomListView;
      Item: TListItem; SubItem: Integer; State: TCustomDrawState;
      var DefaultDraw: Boolean);
    procedure BtnStartClick(Sender: TObject);
    procedure shiftTrackBarChange(Sender: TObject);
    procedure divTrackBarChange(Sender: TObject);
    procedure BufferedAiCtrl1Stopped(Sender: TObject; Offset,
      Count: Integer);
  private
    { Private declarations }
    m_graph : TSimpleGraph;
    dataScaledArray : array of Double;
    dataScaled : OleVariant;
    procedure HandleError(err : ErrorCode);
    procedure InitializeGraph;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

 

procedure TMainForm.FormCreate(Sender: TObject);
var
   i, j : Integer;
   item : TListItem;
   devNum : Longint;
   devDesc : WideString;
   devMode : AccessMode;
   modIndex : Longint;
   err : ErrorCode;
begin
   //The default device of project is demo device, users can choose other devices according to their needs.
   if not BufferedAiCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'AsynOneBufferedAI_TDtr', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   BufferedAiCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Asynchronous One Buffered AI with Trigger Delay to Start(' + devDesc + ')';

   self.DoubleBuffered := true;

   BufferedAiCtrl1.Streaming := false;  //specify the running mode: One-buffered

   err := Success;
   err := BufferedAiCtrl1.Prepare;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   //create the array of dataScaled
   dataScaled := VarArrayCreate([0, BufferedAiCtrl1.BufferCapacity - 1], varDouble);

   //initialize a graph with a paint box control to draw Ai data.
   m_graph := TSimpleGraph.Create(dataView);

   chanDataList.SmallImages := TImageList.Create(self);
   chanDataList.SmallImages.Height := 20;
   for i := 0 to 1 do
   begin
      item := chanDataList.Items.Add;
      for j := 0 to 8 do
         item.SubItems.Add('  ');
   end;
   
   shiftTrackBar.Enabled := false;
   divTrackBar.Enabled := false;

   InitializeGraph;
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

procedure TMainForm.chanDataListCustomDrawSubItem(Sender: TCustomListView;
  Item: TListItem; SubItem: Integer; State: TCustomDrawState;
  var DefaultDraw: Boolean);
var
   plot : Integer;
   clr : TColor;
begin
   plot := Item.Index * 8 + SubItem - 1;

   if plot < BufferedAiCtrl1.ScanChannel.ChannelCount then
      clr := m_graph.GetPlotColor(plot)
   else
      clr := clWhite;

   Sender.Canvas.Brush.Color := clr;
end;

procedure TMainForm.InitializeGraph;
var
   vrgUnit : ValueUnit;
   vrgRange : MathInterval;
   ustr : string;
   xmax,xmin: Double;
begin
   //time track bar
   shiftTrackBar.Max      := Trunc( 1000 * BufferedAiCtrl1.ScanChannel.Samples / BufferedAiCtrl1.ConvertClock.Rate);
   shiftTrackBar.Min      := 0;
   shiftTrackBar.Position := 0;
   shiftTimeEditor.Text   := '0';
   shiftTimeLabel.Caption := 'ms';

   divTrackBar.Max        := MaxInt;
   divTrackBar.Min        := 0;
   divTrackBar.Position   := Trunc(100 * dataView.Width / BufferedAiCtrl1.ConvertClock.Rate);
   divTimeLabel.Caption   := 'ms';

   //need use 'us'
   if not (BufferedAiCtrl1.ConvertClock.Rate < 10000) then
   begin
      shiftTrackBar.Max      := shiftTrackBar.Max * 1000;
      shiftTimeLabel.Caption := 'us';
      divTrackBar.Position   := Trunc(100 * dataView.Width / (BufferedAiCtrl1.ConvertClock.Rate / 1000));
      divTimeLabel.Caption   := 'us';
   end;

   divTimeEditor.Text := IntToStr(divTrackBar.Position);
   divTrackBar.Max    := 4 * divTrackBar.Position;
   divTrackBar.Min    := Max(divTrackBar.Position div 10, 1);

   //simple graph init
   m_graph.XCordTimeDiv := divTrackBar.Position;
   m_graph.XCordOffset  := shiftTrackBar.Position;

   //X-Axis
   xmin :=m_graph.XCordOffset;
   xmax := m_graph.XCordTimeDiv * 10 + xmin;
   if not (xmax < 1000) then begin
      if divTimeLabel.Caption = 'us' then ustr := 'ms'
      else                                ustr := 'Sec';
      xmin := xmin / 1000;
      xmax := xmax / 1000;
   end else begin
      ustr := divTimeLabel.Caption;
   end;
   xLLabel.Caption := FloatToStr(xmin) + ustr;
   xRLabel.Caption := FloatToStr(xmax) + ustr;

   //Y-Axis
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
         //the data from device is 'Voltage'
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

procedure TMainForm.BtnStartClick(Sender: TObject);
var
   err : ErrorCode;
   delayCountPerChanMax : Integer;
   range : MathInterval;
   errMessage : String;
begin
   err := Success;
   delayCountPerChanMax := 0;

   if BufferedAiCtrl1.Features.TriggerSupported then
   begin
      range := BufferedAiCtrl1.Features.TriggerDelayRange;

      if BufferedAiCtrl1.Trigger.Source <> SignalNone then
      begin
         if BufferedAiCtrl1.Features.SamplingMethod = EqualTimeSwitch then
            delayCountPerChanMax := Trunc(range.Max / BufferedAiCtrl1.ScanChannel.ChannelCount)
         else
            delayCountPerChanMax := Trunc(range.Max);

         if (BufferedAiCtrl1.Trigger.DelayCount > delayCountPerChanMax) or (BufferedAiCtrl1.Trigger.DelayCount < range.Min) then
         begin
            errMessage := 'parameter error: DelayCount is within ' + FloatToStr(range.Min) + '-' + IntToStr(delayCountPerChanMax) + '.';
            MessageBox(self.WindowHandle, PChar(errMessage), 'AsynOneBufferedAI_TDtr', MB_OK or MB_ICONERROR);
            exit;
         end;
      end;
   end;

   InitializeGraph;

   err := BufferedAiCtrl1.Start;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   shiftTrackBar.Enabled := true;
   divTrackBar.Enabled := true;
   BtnStart.Enabled := false;
end;

procedure TMainForm.shiftTrackBarChange(Sender: TObject);
var
   xmax, xmin : Double;
   ustr : string;
begin
   if not shiftTrackBar.Enabled then exit;

   xmin := shiftTrackBar.Position;
   xmax := m_graph.XCordTimeDiv * 10 + xmin;
   if not (xmax < 1000) then
   begin
      if divTimeLabel.Caption = 'us' then
         ustr := 'ms'
      else
         ustr := 'Sec';
         
      xmin := xmin / 1000;
      xmax := xmax / 1000;
   end
   else
      ustr := divTimeLabel.Caption;

   xLLabel.Caption := FloatToStr(xmin) + ustr;
   xRLabel.Caption := FloatToStr(xmax) + ustr;
   shiftTimeEditor.Text := IntToStr(shiftTrackBar.Position);
   m_graph.Shift(shiftTrackBar.Position);
end;

procedure TMainForm.divTrackBarChange(Sender: TObject);
begin
   if not divTrackBar.Enabled then exit;

   m_graph.ScaleXCord(divTrackBar.Position);
   divTimeEditor.Text := IntToStr(divTrackBar.Position);
   shiftTrackBarChange(shiftTrackBar);
end;

procedure TMainForm.BufferedAiCtrl1Stopped(Sender: TObject; Offset,
  Count: Integer);
var
   err : ErrorCode;
begin
   err := Success;

   //The BufferedAiCtrl has been disposed.
   if BufferedAiCtrl1.State = Idle then exit;

   //get data
   err := BufferedAiCtrl1.GetData(Count, dataScaled);
   if err <> Success then
   begin
      BtnStart.Enabled := true;
      HandleError(err);
   end;

   //draw the data to the PaintBox
   dataScaledArray := dataScaled;
   m_graph.Chart(dataScaledArray, BufferedAiCtrl1.ScanChannel.ChannelCount, BufferedAiCtrl1.ScanChannel.Samples, 1.0 / BufferedAiCtrl1.ConvertClock.Rate);

   BtnStart.Enabled := true;
end;

end.
