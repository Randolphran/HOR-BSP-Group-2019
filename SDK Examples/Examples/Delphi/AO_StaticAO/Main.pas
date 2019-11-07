unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, Buttons, ImgList, ComCtrls, OleCtrls,
  BDaqOcxLib_TLB, DaqUtils;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    txtboxHiLevelA: TEdit;
    txtboxLoLevelA: TEdit;
    txtboxValueA: TEdit;
    txtboxHiLevelB: TEdit;
    txtboxLoLevelB: TEdit;
    BtnSineA: TSpeedButton;
    ImageList1: TImageList;
    BtnTriangleA: TSpeedButton;
    BtnSquareA: TSpeedButton;
    BtnManualA: TBitBtn;
    Timer1: TTimer;
    timerTrackBar: TTrackBar;
    timerFreqLabel: TLabel;
    BtnSineB: TSpeedButton;
    BtnTriangleB: TSpeedButton;
    BtnSquareB: TSpeedButton;
    BtnManualB: TBitBtn;
    txtboxValueB: TEdit;
    chLabelA: TLabel;
    chLabelB: TLabel;
    InstantAoCtrl1: TInstantAoCtrl;
    procedure FormCreate(Sender: TObject);
    procedure timerTrackBarChange(Sender: TObject);
    procedure ManualOutClick(Sender: TObject);
    procedure WaveButtonClick(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
    channelStart : Integer;
    channelCount : Integer;
    dataScaled : OleVariant;
    m_waveParam : array[0..1] of TWaveParam;
    m_waveButton : array[0..5] of TSpeedButton;
    m_wavePtIdx : array[0..1] of Integer;
    m_waveSeled : array[0..1] of Boolean;
    bitmap : TBitmap;
    procedure ConfigurePanel;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.dfm}

procedure TMainForm.FormCreate(Sender: TObject);
var
   i : Integer;
   devNum : Longint;
   devDesc : WideString;
   devMode : AccessMode;
   modIndex : Longint;
begin
   //initialize these variables
   channelStart := 0;
   channelCount := 0;
   for i := 0 to 1 do
      m_waveParam[i].PtsPerPeriod := 400;

   dataScaled := VarArrayCreate([0, 1], varDouble);

   m_waveButton[0] := BtnSineA;
   m_waveButton[1] := BtnTriangleA;
   m_waveButton[2] := BtnSquareA;
   m_waveButton[3] := BtnSineB;
   m_waveButton[4] := BtnTriangleB;
   m_waveButton[5] := BtnSquareB;

   //initialize a timer which drive the data acquisition.
   Timer1.Interval := 50;

   //The default device of project is demo device, users can choose other devices according to their needs.
   if not InstantAoCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'StaticAO', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set title of the form.
   InstantAoCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Static AO(' + devDesc + ')';

   ConfigurePanel;
   Timer1.Enabled := true;
end;

procedure TMainForm.ConfigurePanel;
begin
   if InstantAoCtrl1.ChannelCount = 1 then
   begin
      channelStart := 0;
      channelCount := 1;

      BtnSineB.Enabled := false;
      BtnSquareB.Enabled := false;
      BtnTriangleB.Enabled := false;
      BtnManualB.Enabled := false;
      txtboxHiLevelB.Enabled := false;
      txtboxLoLevelB.Enabled := false;
      txtboxValueB.Enabled := false;
      chLabelB.Caption := '';
   end
   else
   begin
      channelStart := 0;
      channelCount := 2;

      BtnSineB.Enabled := true;
      BtnSquareB.Enabled := true;
      BtnTriangleB.Enabled := true;
      BtnManualB.Enabled := true;
      txtboxHiLevelB.Enabled := true;
      txtboxLoLevelB.Enabled := true;
      txtboxValueB.Enabled := true;
      chLabelB.Caption := IntToStr(channelStart + 1);
   end;

   chLabelA.Caption := IntToStr(channelStart);
end;

procedure TMainForm.timerTrackBarChange(Sender: TObject);
begin
   Timer1.Interval := timerTrackBar.Position;
   timerFreqLabel.Caption := IntToStr(timerTrackBar.Position) + 'ms';
end;

procedure TMainForm.ManualOutClick(Sender: TObject);
var
   ch, baseIdx, i : Integer;
begin
   //manual ouput button click
   ch := TButton(Sender).Tag;
   baseIdx := ch * 3;
   for i := 0 to 3 - 1 do
      if m_waveButton[i + baseIdx].Down then
      begin
         m_waveButton[i + baseIdx].Down  := false;
         bitmap := TBitmap.Create;
         ImageList1.GetBitmap(i * 2, bitmap);
         m_waveButton[i + baseIdx].Glyph := bitmap;
      end; 

   m_waveSeled[ch] := false;
   if ch = 0 then
      dataScaled[ch] := StrToFloat(txtboxValueA.Text)
   else
      dataScaled[ch] := StrToFloat(txtboxValueB.Text);
end;

procedure TMainForm.WaveButtonClick(Sender: TObject);
var
   seledCH, baseIdx, imgIdx, i : Integer;
begin
   seledCH := TSpeedButton(Sender).Tag div 3;
   baseIdx := seledCH * 3;

   for i := baseIdx to baseIdx + 3 - 1 do
   begin
      imgIdx := (i - baseIdx) * 2;
      if m_waveButton[i].Down then
         imgIdx := imgIdx + 1;

      bitmap := TBitmap.Create;
      ImageList1.GetBitmap(imgIdx, bitmap);
      m_waveButton[i].Glyph := bitmap;
   end;

   m_waveSeled[seledCH]       := TSpeedButton(Sender).Down;
   m_waveParam[seledCH].Style := TWaveStyle(TSpeedButton(Sender).Tag mod 3);

   if seledCH = 0 then
   begin
      m_waveParam[seledCH].HiLevel := StrToFloat(txtboxHiLevelA.Text);
      m_waveParam[seledCH].LoLevel := StrToFloat(txtboxLoLevelA.Text);
   end
   else
   begin
      m_waveParam[seledCH].HiLevel := StrToFloat(txtboxHiLevelB.Text);
      m_waveParam[seledCH].LoLevel := StrToFloat(txtboxLoLevelB.Text);
   end;

   m_wavePtIdx[seledCH] := 0;
end;

procedure TMainForm.Timer1Timer(Sender: TObject);
var
   i   : Integer;
   err : ErrorCode;
   dataScaledArray : array of Double;
   utility : IBDaqUtility;
   errorMessage : WideString;
begin
   err := Success;
   dataScaledArray := dataScaled;
   for i := 0 to 2 - 1 do
      if m_waveSeled[i] then
      begin
         dataScaledArray[i]  := TWaveGenerator.GetOnePoint(m_waveParam[i], m_wavePtIdx[i]);
         m_wavePtIdx[i] := (m_wavePtIdx[i] + 1) mod m_waveParam[i].PtsPerPeriod;
      end;

   dataScaled := dataScaledArray;
   err := InstantAoCtrl1.WriteChannels(channelStart, channelCount, dataScaled);

   utility := CoBDaqUtility.Create();
   utility.EnumToString('ErrorCode', err, errorMessage);
   if err <> Success then
   begin
      Timer1.Enabled := false;
      MessageBox(self.WindowHandle, PChar(Format('Write AO channel failed with error: %s!', [errorMessage])), 'Error', MB_OK or MB_ICONERROR);
   end;
end;

end.
