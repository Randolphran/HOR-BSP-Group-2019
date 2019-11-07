unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, OleCtrls, BDaqOcxLib_TLB, GIFImage;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    GroupBox1: TGroupBox;
    ExecutionStatus: TImage;
    Label1: TLabel;
    clockCountEditor: TEdit;
    label_shotCount: TLabel;
    shotCountEditor: TEdit;
    BtnStart: TButton;
    BtnStop: TButton;
    OneShotCtrl1: TOneShotCtrl;
    procedure FormCreate(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure OneShotCtrl1OneShot(Sender: TObject; Channel: Integer);
  private
    { Private declarations }
    DelayedPulseCount : Integer;
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
   if not OneShotCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'DelayedPulseGeneration', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   OneShotCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Delayed Pulse Generation(' + devDesc + ')';

   gif := TGIFImage.Create;
   gif.LoadFromResourceName(HInstance, 'execStatus');
   gif.Animate := false;
   ExecutionStatus.Picture.Graphic := gif;

   clockCountEditor.Text := IntToStr(OneShotCtrl1.DelayCount);
   label_shotCount.Enabled := false;
   BtnStop.Enabled := false;
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   DelayedPulseCount := 0;

   shotCountEditor.Text := ' ';
   TGIFImage(ExecutionStatus.Picture.Graphic).Animate := true;

   //start oneShot
   OneShotCtrl1.Enabled := true;

   BtnStop.Enabled := true;
   BtnStart.Enabled := false;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   //stop oneShot
   OneShotCtrl1.Enabled := false;

   BtnStop.Enabled := false;
   BtnStart.Enabled := true;
   TGIFImage(ExecutionStatus.Picture.Graphic).Animate := false;
end;

procedure TMainForm.OneShotCtrl1OneShot(Sender: TObject; Channel: Integer);
begin
   DelayedPulseCount := DelayedPulseCount + 1;
   label_shotCount.Enabled := true;
   shotCountEditor.Text := IntToStr(DelayedPulseCount);
end;

end.
