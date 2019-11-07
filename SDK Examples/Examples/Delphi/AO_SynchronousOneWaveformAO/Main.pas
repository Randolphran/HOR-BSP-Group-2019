unit Main;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, Buttons, OleCtrls, BDaqOcxLib_TLB,
  ImgList, DaqUtils;

type
  TMainForm = class(TForm)
    bkgrndImage: TImage;
    txtboxHiLevelA: TEdit;
    txtboxLoLevelA: TEdit;
    txtboxHiLevelB: TEdit;
    txtboxLoLevelB: TEdit;
    chLabelA: TLabel;
    chLabelB: TLabel;
    BtnSineA: TSpeedButton;
    BtnTriangleA: TSpeedButton;
    BtnSquareA: TSpeedButton;
    BtnSineB: TSpeedButton;
    BtnTriangleB: TSpeedButton;
    BtnSquareB: TSpeedButton;
    BtnStart: TButton;
    ImageList1: TImageList;
    BufferedAoCtrl1: TBufferedAoCtrl;
    procedure FormCreate(Sender: TObject);
    procedure WaveButtonClick(Sender: TObject);
    procedure BtnStartClick(Sender: TObject);
  private
    { Private declarations }
    dataScaled : OleVariant;
    dataSCaledArray : array of Double;
    m_waveButton: array[0..5] of TSpeedButton;
    m_waveParam : array[0..1] of TWaveParam;
    m_waveSeled : array[0..1] of Boolean;
    bitmap : TBitmap;
    procedure ConfigurePanel;
    procedure CheckError(err : ErrorCode);
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
   if not BufferedAoCtrl1.Initialized then
   begin
      MessageBox(self.WindowHandle, 'Please select a device with DAQNavi wizard!', 'SynchronousOneWaveformAO', MB_OK or MB_ICONERROR);
      Application.Terminate;
      exit;
   end;

   //set the ChannelCount
   if BufferedAoCtrl1.ScanChannel.ChannelCount > 1 then
      BufferedAoCtrl1.ScanChannel.ChannelCount := 2;

   m_waveButton[0] := BtnSineA;
   m_waveButton[1] := BtnTriangleA;
   m_waveButton[2] := BtnSquareA;
   m_waveButton[3] := BtnSineB;
   m_waveButton[4] := BtnTriangleB;
   m_waveButton[5] := BtnSquareB;

   //initialize the sine as the default choice
   BtnSineA.Down := true;
   bitmap := TBitmap.Create;
   ImageList1.GetBitmap(1, bitmap);
   BtnSineA.Glyph := bitmap;
   m_waveSeled[0] := true;
   m_waveParam[0].Style := Sine;

   if BufferedAoCtrl1.ScanChannel.ChannelCount > 1 then
   begin
      BtnSineB.Down := true;
      bitmap := TBitmap.Create;
      ImageList1.GetBitmap(1, bitmap);
      BtnSineB.Glyph := bitmap;
      m_waveSeled[1] := true;
      m_waveParam[1].Style := Sine;
   end; 

   //set title of the form.
   BufferedAoCtrl1.getSelectedDevice(devNum, devDesc, devMode, modIndex);
   self.Caption := 'Synchronous One Waveform AO(' + devDesc + ')'; 

   ConfigurePanel;
end;

procedure TMainForm.ConfigurePanel;
begin
    if BufferedAoCtrl1.ScanChannel.ChannelCount = 1 then
   begin
      BtnSineB.Enabled := false;
      BtnSquareB.Enabled := false;
      BtnTriangleB.Enabled := false;
      txtboxHiLevelB.Enabled := false;
      txtboxLoLevelB.Enabled := false;
      chLabelB.Caption := '';
   end
   else
   begin
      BtnSineB.Enabled := true;
      BtnSquareB.Enabled := true;
      BtnTriangleB.Enabled := true;
      txtboxHiLevelB.Enabled := true;
      txtboxLoLevelB.Enabled := true;
      chLabelB.Caption := IntToStr((BufferedAoCtrl1.ScanChannel.ChannelStart + 1) mod BufferedAoCtrl1.ChannelCount);
   end;

   chLabelA.Caption := IntToStr(BufferedAoCtrl1.ScanChannel.ChannelStart);
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

   m_waveSeled[seledCH] := TSpeedButton(Sender).Down;

   if TSpeedButton(Sender).Down then
      m_waveParam[seledCH].Style := TWaveStyle(TSpeedButton(Sender).Tag mod 3)
   else
      m_waveParam[seledCH].Style := TWaveStyle(2);
end;

procedure TMainForm.BtnStartClick(Sender: TObject);
var
   err : ErrorCode;
   dataCount : Integer;
begin
   if (m_waveSeled[0] = false) and (m_waveSeled[1] = false) then
   begin
      MessageBox(self.WindowHandle, 'Please select a waveform!', 'SynchronousOneWaveformAO', MB_OK or MB_ICONERROR);
      exit;
   end;
      
   //prepare the AO
   err := Success;
   err := BufferedAoCtrl1.Prepare;
   CheckError(err);

   dataCount := BufferedAoCtrl1.ScanChannel.ChannelCount * BufferedAoCtrl1.ScanChannel.Samples;
   m_waveParam[0].PtsPerPeriod := BufferedAoCtrl1.ScanChannel.Samples;
   m_waveParam[1].PtsPerPeriod := BufferedAoCtrl1.ScanChannel.Samples;
   dataSCaled := VarArrayCreate([0, dataCount - 1], varDouble);

   if (m_waveSeled[0] = true) and (m_waveSeled[1] = false) then
   begin
      m_waveParam[0].HiLevel := StrToFloat(txtboxHiLevelA.Text);
      m_waveParam[1].HiLevel := 0;
      m_waveParam[0].LoLevel := StrToFloat(txtboxLoLevelA.Text);
      m_waveParam[1].LoLevel := 0;
   end
   else if (m_waveSeled[0] = false) and (m_waveSeled[1] = true) then
   begin
      m_waveParam[0].HiLevel := 0;
      m_waveParam[1].HiLevel := StrToFloat(txtboxHiLevelB.Text);
      m_waveParam[0].LoLevel := 0;
      m_waveParam[1].LoLevel := StrToFloat(txtboxLoLevelB.Text);
   end
   else if (m_waveSeled[0] = true) and (m_waveSeled[1] = true) then
   begin
      m_waveParam[0].HiLevel := StrToFloat(txtboxHiLevelA.Text);
      m_waveParam[1].HiLevel := StrToFloat(txtboxHiLevelB.Text);
      m_waveParam[0].LoLevel := StrToFloat(txtboxLoLevelA.Text);
      m_waveParam[1].LoLevel := StrToFloat(txtboxLoLevelB.Text);
   end;

   //generator the wave
   dataScaledArray := dataScaled;
   TWaveGenerator.GetWaveform(BufferedAoCtrl1.ScanChannel.ChannelCount, m_waveParam, dataCount, dataScaledArray);

   //Convert scaled  data to raw data
   dataScaled := dataScaledArray;
   err := BufferedAoCtrl1.SetData(dataCount, dataScaled);
   CheckError(err);

   //Start buffered AO in synchronous
   err := BufferedAoCtrl1.RunOnce;
   CheckError(err);
end;

procedure TMainForm.CheckError(err : ErrorCode);
var
   utility : IBDaqUtility;
   errorMessage : WideString;
begin
   utility := CoBDaqUtility.Create();
   utility.EnumToString('ErrorCode', err, errorMessage);

   if err <> Success then
         MessageBox(0, PChar(Format('Initialize buffered AO failed with error: %s!', [errorMessage])), 'Error', MB_OK or MB_ICONERROR);
end;

end.
