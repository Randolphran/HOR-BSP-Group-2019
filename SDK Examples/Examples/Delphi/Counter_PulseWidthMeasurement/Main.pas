unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, OleCtrls, BDaqOcxLib_TLB;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    hiPeriodEditor: TEdit;
    loPeriodEditor: TEdit;
    cntrValueList: TListBox;
    BtnStart: TButton;
    BtnStop: TButton;
    Timer1: TTimer;
    PwMeterCtrl1: TPwMeterCtrl;
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
  private
    { Private declarations }
    ECisRunning : Boolean;
    isPwMeterReset : Boolean;
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
begin
   //The default device of project is demo device, users can choose other devices according to their needs
   if not PwMeterCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'PulseWidthMeasurement', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   PwMeterCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Pulse Width Measurement(' + devDesc + ')';

   ECisRunning := True;
   isPwMeterReset := True;
   Timer1.Enabled := false;
   BtnStop.Enabled := false;
end;

procedure TMainForm.Timer1Timer(Sender: TObject);
begin
   if ECisRunning then
   begin
      //Show event counting value
      hiPeriodEditor.Text := FloatToStr(PwMeterCtrl1.getValue.HiPeriod);
      loPeriodEditor.Text := FloatToStr(PwMeterCtrl1.getValue.LoPeriod);
   end;
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   if isPwMeterReset = true then
   begin
      cntrValueList.Items.Clear;

      //start PwMeter
      PwMeterCtrl1.Enabled := true;
      ECisRunning := True;

      if Timer1.Enabled = false then
         Timer1.Enabled := true;

      BtnStop.Enabled := true;
      BtnStart.Caption := 'Latch';
      isPwMeterReset := False;
   end
   else
   begin
      //latch data
      if cntrValueList.Items.Count >= 6 then cntrValueList.Items.Delete(0);
      cntrValueList.Items.Add('High:' + hiPeriodEditor.Text + '  Low:' + loPeriodEditor.Text);
   end;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   //Stop event counting
   PwMeterCtrl1.Enabled := false;
   ECisRunning := False;
   isPwMeterReset := True;

   BtnStart.Enabled := true;
   BtnStart.Caption := 'Start';
   BtnStop.Enabled := false;

   //stop the timer
   if ECisRunning = False then
      Timer1.Enabled := false;
end;

end.
