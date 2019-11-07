unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, ComCtrls, StdCtrls, OleCtrls, BDaqOcxLib_TLB, GIFImage;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    eventDataList: TListView;
    gifViewer: TImage;
    BtnStart: TButton;
    BtnStop: TButton;
    InstantDiCtrl1: TInstantDiCtrl;
    procedure FormCreate(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
    procedure BtnStopClick(Sender: TObject);
    procedure InstantDiCtrl1PatternMatch(Sender: TObject; SrcNum: Integer;
      var PortData: OleVariant);
  private
    { Private declarations }
    matchedNum : Integer;
    procedure HandleError(err : ErrorCode);
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
   //The default device of project is demo device, users can choose other devices according to their needs.
   if not InstantDiCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'DIPatternMatch', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   InstantDiCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'DI Pattern Match Interrupt(' + devDesc + ')';

   gif := TGIFImage.Create;
   gif.LoadFromResourceName(HInstance, 'tambour');
   gif.Animate := false;
   gifViewer.Picture.Graphic := gif;

   eventDataList.Columns[1].Caption :=  'DI ports value (Port 0~' + IntToStr(InstantDiCtrl1.Features.PortCount - 1) + ')';

   BtnStop.Enabled := false;
end;

procedure TMainForm.HandleError(err : ErrorCode);
var
   utility : IBDaqUtility;
   errorMessage : WideString;
begin
   utility := CoBDaqUtility.Create();
   utility.EnumToString('ErrorCode', err, errorMessage);

   if err <> Success then
      MessageBox(0, PChar(Format('Read DI Ports failed with error: %s!', [errorMessage])), 'Error', MB_OK or MB_ICONERROR);
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
var
   err : ErrorCode;
begin
   err := Success;
   matchedNum := 0;
   eventDataList.Items.Clear;

   err := InStantDiCtrl1.SnapStart;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   BtnStart.Enabled := false;
   BtnStop.Enabled := true;
   TGIFImage(gifViewer.Picture.Graphic).Animate := true;
end;

procedure TMainForm.BtnStopClick(Sender: TObject);
var
   err : ErrorCode;
begin
   err := Success;

   err := InStantDiCtrl1.SnapStop;
   if err <> Success then
   begin
      HandleError(err);
      exit;
   end;

   BtnStart.Enabled := true;
   BtnStop.Enabled := false;
   TGIFImage(gifViewer.Picture.Graphic).Animate := false;
end;

procedure TMainForm.InstantDiCtrl1PatternMatch(Sender: TObject;
  SrcNum: Integer; var PortData: OleVariant);
var
   i : Integer;
   item : TListItem;
   valueString : ShortString;
   Data : array of Byte;
begin
   if eventDataList.Items.Count = 10 then
      eventDataList.Items.Delete(0);

   item := eventDataList.Items.Add;
   matchedNum := matchedNum + 1;
   item.Caption := '         ' + IntToStr(matchedNum);

   valueString := '';
   Data := PortData;
   for i := 0 to Length(Data) - 1 do
   begin
      valueString := valueString + Format('%.2X', [Data[i]]);
      if i < Length(Data) - 1 then
         valueString := valueString + ', ';
   end;

   item.SubItems.Add(valueString);
end;

end.
