unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, OleCtrls, BDaqOcxLib_TLB, GIFImage;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    Label1: TLabel;
    userFreqEditor: TEdit;
    Label2: TLabel;
    GroupBox1: TGroupBox;
    ExecutionStatus: TImage;
    Label3: TLabel;
    devFreqEditor: TEdit;
    Label4: TLabel;
    label_eventCount: TLabel;
    evtCountEditor: TEdit;
    BtnStart: TButton;
    BtnStop: TButton;
    TimerPulseCtrl1: TTimerPulseCtrl;
    procedure FormCreate(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure TimerPulseCtrl1TimerTick(Sender: TObject; Channel: Integer);
  private
    { Private declarations }
    TPevtCount : Integer;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

procedure TMainForm.FormCreate(Sender: TObject);
var
   devNum : Longint;
   devDesc : WideString;
   devMode : AccessMode;
   modIndex : Longint;
   gif : TGIFImage;
begin
   //The default device of project is demo device, users can choose other devices according to their needs
   if not TimerPulseCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'PulseOutputwithTimerInterrupt', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   TimerPulseCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Pulse Output with Timer Interrupt(' + devDesc + ')';

   gif := TGIFImage.Create;
   gif.LoadFromResourceName(HInstance, 'execStatus');
   gif.Animate := false;
   ExecutionStatus.Picture.Graphic := gif;

   userFreqEditor.Text := FloatToStr(TimerPulseCtrl1.Frequency);
   label_eventCount.Enabled := false;
   BtnStop.Enabled := false;
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   //TimerPulse event count
   TPevtCount := 0;
   evtCountEditor.Text := ' ';

   //Enable execution status
   TGIFImage(ExecutionStatus.Picture.Graphic).Animate := true;

   //start the timer pulse
   TimerPulseCtrl1.Enabled := true;
   devFreqEditor.Text := FloatToStr(TimerPulseCtrl1.Frequency);

   BtnStart.Enabled := false;
   BtnStop.Enabled := true;     
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   //stop the timer pulse
   TimerPulseCtrl1.Enabled := false;

   //Disable execution status
   TGIFImage(ExecutionStatus.Picture.Graphic).Animate := false;

   BtnStart.Enabled := true;
   BtnStop.Enabled := false;
end;

procedure TMainForm.TimerPulseCtrl1TimerTick(Sender: TObject;
  Channel: Integer);
begin
   TPevtCount := TPevtCount + 1;
   label_eventCount.Enabled := true;
   evtCountEditor.Text := IntToStr(TPevtCount);
end;

end.
