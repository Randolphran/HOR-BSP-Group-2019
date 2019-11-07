unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, OleCtrls, BDaqOcxLib_TLB, GIFImage;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    Label1: TLabel;
    Label2: TLabel;
    hiPeriodEditor: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    loPeriodEditor: TEdit;
    Label5: TLabel;
    GroupBox1: TGroupBox;
    ExecutionStatus: TImage;
    Label6: TLabel;
    Label7: TLabel;
    actualHiPeriod: TEdit;
    Label8: TLabel;
    Label9: TLabel;
    actualLoPeriod: TEdit;
    Label10: TLabel;
    BtnStart: TButton;
    BtnStop: TButton;
    PwModulatorCtrl1: TPwModulatorCtrl;
    procedure FormCreate(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
  private
    { Private declarations }
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
   if not PwModulatorCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'PWMOutput', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   PwModulatorCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'PWM Output(' + devDesc + ')';

   gif := TGIFImage.Create;
   gif.LoadFromResourceName(HInstance, 'execStatus');
   gif.Animate := false;
   ExecutionStatus.Picture.Graphic := gif;

   hiPeriodEditor.Text := FloatToStr(PwModulatorCtrl1.getPulseWidth.HiPeriod);
   loPeriodEditor.Text := FloatToStr(PwModulatorCtrl1.getPulseWidth.LoPeriod);

   BtnStop.Enabled := false;
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   //Enable execution status
   TGIFImage(ExecutionStatus.Picture.Graphic).Animate := true;

   PwModulatorCtrl1.Enabled := true;

   actualHiPeriod.Text := FloatToStr(PwModulatorCtrl1.getPulseWidth.HiPeriod);
   actualLoPeriod.Text := FloatToStr(PwModulatorCtrl1.getPulseWidth.LoPeriod);
   
   BtnStart.Enabled := false;
   BtnStop.Enabled := true;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   //stop the PwModulator
   PwModulatorCtrl1.Enabled := false;

   //Disable execution status
   TGIFImage(ExecutionStatus.Picture.Graphic).Animate := false;

   BtnStart.Enabled := true;
   BtnStop.Enabled := false;
end;

end.
