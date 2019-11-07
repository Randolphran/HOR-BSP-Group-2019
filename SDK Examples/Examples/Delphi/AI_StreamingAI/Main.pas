unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, DaqUtils, ExtCtrls, StdCtrls, ComCtrls, OleCtrls, BDaqOcxLib_TLB, Math;

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
    divTrackBar: TTrackBar;
    BtnStart: TButton;
    BtnPause: TButton;
    BtnStop: TButton;
    BufferedAiCtrl1: TBufferedAiCtrl;
    divTimeLabel: TLabel;
    procedure BtnStartClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure divTrackBarChange(Sender: TObject);
    procedure chanDataListCustomDrawSubItem(Sender: TCustomListView;
      Item: TListItem; SubItem: Integer; State: TCustomDrawState;
      var DefaultDraw: Boolean);
    procedure BufferedAiCtrl1CacheOverflow(Sender: TObject;
      Offset: Integer; Count: Integer);
    procedure BufferedAiCtrl1DataReady(Sender: TObject;
      Offset: Integer; Count: Integer);
    procedure BufferedAiCtrl1Overrun(Sender: TObject;
      Offset: Integer; Count: Integer);
    procedure BtnPauseClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
  private
    { Private declarations }
    m_graph : TSimpleGraph;
    isFirstOverRun : Boolean;
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

procedure TMainForm.BtnStartClick(Sender: TObject);
var
   err : ErrorCode;
begin
   err := Success;
   InitializeGraph;

   err := BufferedAiCtrl1.Start;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   divTrackBar.Enabled := true;
   BtnStart.Enabled := false;
   BtnPause.Enabled := true;
   BtnStop.Enabled := true;
end;

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
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'StreamingAI', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   BufferedAiCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Streaming AI(' + devDesc + ')';

   //initialize the isFirstOverRun
   isFirstOverRun := true;

   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := false;

   self.DoubleBuffered := true;

   BufferedAiCtrl1.Streaming := true;  //specify the running mode: streaming-buffered

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

procedure TMainForm.divTrackBarChange(Sender: TObject);
var
   xmax, xmin : Double;
   ustr : string;
begin
   if not divTrackBar.Enabled then exit;

   m_graph.ScaleXCord(divTrackBar.Position);

   xmin := 0;
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

procedure TMainForm.BufferedAiCtrl1CacheOverflow(Sender: TObject;
  Offset: Integer; Count: Integer);
begin
   MessageBox(0, 'BufferedAiCacheOverflow', 'StreamingAI', MB_OK or MB_ICONERROR);
end;

procedure TMainForm.BufferedAiCtrl1DataReady(Sender: TObject;
  Offset: Integer; Count: Integer);
var
   err : ErrorCode;
   dataPerPlot : Integer;
begin
   err := Success;

   //The BufferedAiCtrl has been disposed.
   if BufferedAiCtrl1.State = Idle then exit;

   //get data
   err := BufferedAiCtrl1.GetData(Count, dataScaled);
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   //draw the data to the PaintBox
   dataPerPlot := Count div BufferedAiCtrl1.ScanChannel.ChannelCount;
   dataScaledArray := dataScaled;
   m_graph.Chart(dataScaledArray, BufferedAiCtrl1.ScanChannel.ChannelCount, dataPerPlot, 1.0 / BufferedAiCtrl1.ConvertClock.Rate);

end;

procedure TMainForm.BufferedAiCtrl1Overrun(Sender: TObject;
  Offset: Integer; Count: Integer);
begin
   if isFirstOverRun then
   begin
      MessageBox(0, 'BufferedAiOverrun', 'StreamingAI', MB_OK or MB_ICONERROR);
      isFirstOverRun := false;
   end;
end;

procedure TMainForm.InitializeGraph;
var
   vrgUnit : ValueUnit;
   vrgRange : MathInterval;
   ustr : string;
   xmax,xmin: Double;
begin
   //time track bar
   divTrackBar.Max        := MaxInt;
   divTrackBar.Min        := 0;
   divTrackBar.Position   := Trunc(100 * dataView.Width / BufferedAiCtrl1.ConvertClock.Rate);
   divTimeLabel.Caption   := 'ms';

   //need use 'us'
   if not (BufferedAiCtrl1.ConvertClock.Rate < 10000) then
   begin
      divTrackBar.Position   := Trunc(100 * dataView.Width / (BufferedAiCtrl1.ConvertClock.Rate / 1000));
      divTimeLabel.Caption   := 'us';
   end;

   divTrackBar.Max    := 4 * divTrackBar.Position;
   divTrackBar.Min    := Max(divTrackBar.Position div 10, 1);

   //simple graph init
   m_graph.OverOneScreenMode := EndScreen;
   m_graph.XCordTimeDiv := divTrackBar.Position;
   m_graph.XCordOffset  := 0;

   //X-Axis
   xmin := m_graph.XCordOffset;
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
   begin
      ustr := divTimeLabel.Caption;
   end;
   
   xLLabel.Caption := FloatToStr(xmin) + ustr;
   xRLabel.Caption := FloatToStr(xmax) + ustr;

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

procedure TMainForm.BtnPauseClick(Sender: TObject);
var
   err : ErrorCode;
begin
   err := Success;
   err := BufferedAiCtrl1.Stop;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
var
   err : ErrorCode;
begin
   err := Success;
   err := BufferedAiCtrl1.Stop;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   BtnStart.Enabled := true;
   BtnPause.Enabled := false;
   BtnStop.Enabled := false;

   m_graph.Clear;
end;

end.
