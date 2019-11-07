unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, OleCtrls, BDaqOcxLib_TLB;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    GroupBox1: TGroupBox;
    curValueEditor: TEdit;
    cntrValueList: TListBox;
    BtnStart: TButton;
    BtnStop: TButton;
    Timer1: TTimer;
    EventCounterCtrl1: TEventCounterCtrl;
    procedure FormCreate(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
    ECisRunning : Boolean;
    isEventCountingReset : Boolean;
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
   //The default device of project is demo device, users can choose other devices according to their needs.
   if not EventCounterCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'EventCounter', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   EventCounterCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Event Counter(' + devDesc + ')';

   //initialize ECisRunning and  isEventCountingReset
   ECisRunning := true;
   isEventCountingReset := true;

   Timer1.Enabled := false;
   BtnStop.Enabled := false;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
begin
   //Stop event counting
   EventCounterCtrl1.Enabled := false;
   ECisRunning := false;

   isEventCountingReset := true;
   BtnStart.Enabled := true;
   BtnStart.Caption := 'Start';
   BtnStop.Enabled := false;

   //stop the timer
   if ECisRunning = false then
      Timer1.Enabled := false;
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
begin
   if isEventCountingReset = true then
   begin
      cntrValueList.Items.Clear;

      EventCounterCtrl1.Enabled := true;
      ECisRunning := true;

      if Timer1.Enabled = false then
         Timer1.Enabled := true;

      BtnStop.Enabled := true;
      BtnStart.Caption := 'Latch';
      isEventCountingReset := false;
   end
   else
   begin
      if cntrValueList.Items.Count >= 5 then
         cntrValueList.Items.Delete(0);
      cntrValueList.Items.Add(curValueEditor.Text);
   end;
end;

procedure TMainForm.Timer1Timer(Sender: TObject);
begin
   if ECisRunning then
      //Show event counting value
      curValueEditor.Text := IntToStr(EventCounterCtrl1.Value);
end;

end.
