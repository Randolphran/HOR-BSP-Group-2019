unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, ImgList, OleCtrls, BDaqOcxLib_TLB, StrUtils;
const
   StartPort = 0;
   PortCountShow = 4;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    PortNum0: TEdit;
    PortNum1: TEdit;
    PortNum2: TEdit;
    PortNum3: TEdit;
    PortHex0: TEdit;
    PortHex1: TEdit;
    PortHex2: TEdit;
    PortHex3: TEdit;
    GroupBox2: TGroupBox;
    Image04: TImage;
    Image05: TImage;
    Image06: TImage;
    Image07: TImage;
    GroupBox3: TGroupBox;
    Image00: TImage;
    Image01: TImage;
    Image02: TImage;
    Image03: TImage;
    GroupBox4: TGroupBox;
    GroupBox5: TGroupBox;
    GroupBox6: TGroupBox;
    GroupBox7: TGroupBox;
    GroupBox8: TGroupBox;
    GroupBox9: TGroupBox;
    Image10: TImage;
    Image11: TImage;
    Image12: TImage;
    Image13: TImage;
    Image14: TImage;
    Image15: TImage;
    Image16: TImage;
    Image17: TImage;
    Image20: TImage;
    Image21: TImage;
    Image22: TImage;
    Image23: TImage;
    Image24: TImage;
    Image25: TImage;
    Image26: TImage;
    Image27: TImage;
    Image30: TImage;
    Image31: TImage;
    Image32: TImage;
    Image33: TImage;
    Image34: TImage;
    Image35: TImage;
    Image36: TImage;
    Image37: TImage;
    ImageList1: TImageList;
    InstantDoCtrl1: TInstantDoCtrl;
    procedure FormCreate(Sender: TObject);
    procedure Image0Click(Sender: TObject);
    procedure Image1Click(Sender: TObject);
    procedure Image2Click(Sender: TObject);
    procedure Image3Click(Sender: TObject);
  private
    { Private declarations }
    m_portNum : array[0..3] of TEdit;
    m_portHex : array[0..3] of TEdit;
    m_image : array[0..3, 0..7] of TImage;
    portDatas : array[0..3] of Byte;
    m_bitmap : array[0..2] of TBitmap;
    procedure HandleError(err : ErrorCode);
    procedure InitializePortState;
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
   if not InstantDoCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'StaticDO', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   InstantDoCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Static DO(' + devDesc + ')';

   m_portNum[0] := PortNum0;
   m_portNum[1] := PortNum1;
   m_portNum[2] := PortNum2;
   m_portNum[3] := PortNum3;

   m_portHex[0] := PortHex0;
   m_portHex[1] := PortHex1;
   m_portHex[2] := PortHex2;
   m_portHex[3] := PortHex3;

   m_image[0, 0] := Image00;
   m_image[0, 1] := Image01;
   m_image[0, 2] := Image02;
   m_image[0, 3] := Image03;
   m_image[0, 4] := Image04;
   m_image[0, 5] := Image05;
   m_image[0, 6] := Image06;
   m_image[0, 7] := Image07;

   m_image[1, 0] := Image10;
   m_image[1, 1] := Image11;
   m_image[1, 2] := Image12;
   m_image[1, 3] := Image13;
   m_image[1, 4] := Image14;
   m_image[1, 5] := Image15;
   m_image[1, 6] := Image16;
   m_image[1, 7] := Image17;

   m_image[2, 0] := Image20;
   m_image[2, 1] := Image21;
   m_image[2, 2] := Image22;
   m_image[2, 3] := Image23;
   m_image[2, 4] := Image24;
   m_image[2, 5] := Image25;
   m_image[2, 6] := Image26;
   m_image[2, 7] := Image27;

   m_image[3, 0] := Image30;
   m_image[3, 1] := Image31;
   m_image[3, 2] := Image32;
   m_image[3, 3] := Image33;
   m_image[3, 4] := Image34;
   m_image[3, 5] := Image35;
   m_image[3, 6] := Image36;
   m_image[3, 7] := Image37;

   m_bitmap[0] := TBitmap.Create;
   ImageList1.GetBitmap(0, m_bitmap[0]);

   m_bitmap[1] := TBitmap.Create;
   ImageList1.GetBitmap(1, m_bitmap[1]);

   m_bitmap[2] := TBitmap.Create;
   ImageList1.GetBitmap(2, m_bitmap[2]);

   InitializePortState;
end;

procedure TMainForm.InitializePortState;
var
   i, j, index : Integer;
   portData : Byte;
   portDir : Byte;
   err : ErrorCode;
   portDirs : array of IPortDirection;
begin
   i := 0;
   portData := 0;
   portDir := $FF;
   err := Success;
   
  while (i < PortCountShow) and ((i + StartPort) <  InstantDoCtrl1.Features.PortCount) do
   begin
      err := InstantDoCtrl1.ReadPort(i + StartPort, portData); 
      if err <> Success then
      begin
         HandleError(err);
         exit;
      end;

      m_portNum[i].Text := IntToStr(i + StartPort);
      m_portHex[i].Text := Format('%.2X', [portData]);
      portDatas[i] := portData;

      //set the port direction
      if InstantDoCtrl1.Features.PortProgrammable then
      begin
         portDirs := InstantDoCtrl1.PortDirection;
         portDir := portDirs[i].Direction;
      end;

      //Set image state
      for j := 0 to 7 do
      if (portDir shr j) and 1 = 0 then  //Bit direction is input.
      begin
         m_image[i, j].Picture.Bitmap := m_bitmap[2]
      end
      else
      begin
         index := (portData shr j) and 1;
         m_image[i, j].Picture.Bitmap := m_bitmap[index];
         m_image[i, j].Tag := (portData shr j) and 1;
         m_image[i, j].Enabled := true;
      end;
      
      i := i + 1;
   end;
end;

procedure TMainForm.HandleError(err : ErrorCode);
var
   utility : IBDaqUtility;
   errorMessage : WideString;
begin
   utility := CoBDaqUtility.Create();
   utility.EnumToString('ErrorCode', err, errorMessage);
   
   if err <> Success then
      MessageBox(0, PChar(Format('Write DO Ports failed with error: %s!', [errorMessage])), 'Error', MB_OK or MB_ICONERROR);
end;

procedure TMainForm.Image0Click(Sender: TObject);
var
   i , data : Integer;
   bitValue : Integer;
   err : ErrorCode;
   index : Integer;
begin
   i := 0;
   err := Success;
   data := 1;
   bitValue := TImage(Sender).Tag;
   index := StrToInt(TImage(Sender).HelpKeyword);

   while i < index do
   begin
      data := data * 2;
      i := i + 1;
   end;

   if bitValue = 0 then
   begin
      portDatas[0] := portDatas[0] + data;
      TImage(Sender).Picture.Bitmap := m_bitmap[1];
      TImage(Sender).Tag := 1;
   end
   else if bitValue = 1 then
   begin
      portDatas[0] := portDatas[0] - data;
      TImage(Sender).Picture.Bitmap := m_bitmap[0];
      TImage(Sender).Tag := 0;
   end;

   m_portHex[0].Text := Format('%.2X', [portDatas[0]]);
   err := InstantDoCtrl1.WritePort(0 + StartPort, portDatas[0]);
   if err <> Success then
      HandleError(err);
end;

procedure TMainForm.Image1Click(Sender: TObject);
var
   i , data : Integer;
   bitValue : Integer;
   err : ErrorCode;
   index : Integer;
begin
   i := 0;
   err := Success;
   data := 1;
   bitValue := TImage(Sender).Tag;
   index := StrToInt(TImage(Sender).HelpKeyword);

   while i < index do
   begin
      data := data * 2;
      i := i + 1;
   end;

   if bitValue = 0 then
   begin
      portDatas[1] := portDatas[1] + data;
      TImage(Sender).Picture.Bitmap := m_bitmap[1];
      TImage(Sender).Tag := 1;
   end
   else if bitValue = 1 then
   begin
      portDatas[1] := portDatas[1] - data;
      TImage(Sender).Picture.Bitmap := m_bitmap[0];
      TImage(Sender).Tag := 0;
   end;

   m_portHex[1].Text := Format('%.2X', [portDatas[1]]);
   err := InstantDoCtrl1.WritePort(1 + StartPort, portDatas[1]);
   if err <> Success then
      HandleError(err);
end;

procedure TMainForm.Image2Click(Sender: TObject);
var
   i , data : Integer;
   bitValue : Integer;
   err : ErrorCode;
   index : Integer;
begin
   i := 0;
   err := Success;
   data := 1;
   bitValue := TImage(Sender).Tag;
   index := StrToInt(TImage(Sender).HelpKeyword);

   while i < index do
   begin
      data := data * 2;
      i := i + 1;
   end;

   if bitValue = 0 then
   begin
      portDatas[2] := portDatas[2] + data;
     TImage(Sender).Picture.Bitmap := m_bitmap[1];
      TImage(Sender).Tag := 1;
   end
   else if bitValue = 1 then
   begin
      portDatas[2] := portDatas[2] - data;
      TImage(Sender).Picture.Bitmap := m_bitmap[0];
      TImage(Sender).Tag := 0;
   end;

   m_portHex[2].Text := Format('%.2X', [portDatas[2]]);
   err := InstantDoCtrl1.WritePort(2 + StartPort, portDatas[2]);
   if err <> Success then
      HandleError(err);
end;


procedure TMainForm.Image3Click(Sender: TObject);
var
   i , data : Integer;
   bitValue : Integer;
   err : ErrorCode;
   index : Integer;
begin
   i := 0;
   err := Success;
   data := 1;
   bitValue := TImage(Sender).Tag;
   index := StrToInt(TImage(Sender).HelpKeyword);

   while i < index do
   begin
      data := data * 2;
      i := i + 1;
   end;

   if bitValue = 0 then
   begin
      portDatas[3] := portDatas[3] + data;
      TImage(Sender).Picture.Bitmap := m_bitmap[1];
      TImage(Sender).Tag := 1;
   end
   else if bitValue = 1 then
   begin
      portDatas[3] := portDatas[3] - data;
      TImage(Sender).Picture.Bitmap := m_bitmap[0];
      TImage(Sender).Tag := 0;
   end;

   m_portHex[3].Text := Format('%.2X', [portDatas[3]]);
   err := InstantDoCtrl1.WritePort(3 + StartPort, portDatas[3]);
   if err <> Success then
      HandleError(err);
end;

end.
