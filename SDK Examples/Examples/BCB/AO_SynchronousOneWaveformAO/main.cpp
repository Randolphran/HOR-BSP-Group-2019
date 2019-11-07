//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        bfdAoCtrl = BufferedAoCtrl::Create();
        dataScaled = NULL;
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Synchronous One Waveform AO - Run("  + deviceName + ")";
        this->Caption = caption;

        if (dataScaled != NULL) {
                delete[] dataScaled;
                dataScaled = NULL;
        }

        //initialize these variables
        m_waveButton[0] = BtnSineA;
        m_waveButton[1] = BtnTriangleA;
        m_waveButton[2] = BtnSquareA;
        m_waveButton[3] = BtnSineB;
        m_waveButton[4] = BtnTriangleB;
        m_waveButton[5] = BtnSquareB;

        InitialButtons();

        //initialize the sine as the default choice
        BtnSineA->Down = true;
        bitmap = new Graphics::TBitmap();
        ImageList1->GetBitmap(1, bitmap);
        BtnSineA->Glyph = bitmap;
        m_waveSeled[0] = true;
        m_waveParam[0].Style = Sine;

        if (configure.channelCount > 1) {
                BtnSineB->Down = true;
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(1, bitmap);
                BtnSineB->Glyph = bitmap;
                m_waveSeled[1] = true;
                m_waveParam[1].Style = Sine;
        }
        
        ConfigureDevice();

        //set the ChannelCount
        if (bfdAoCtrl->getScanChannel()->getChannelCount() > 1) {
                bfdAoCtrl->getScanChannel()->setChannelCount(2);
        }

        ConfigurePanel();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = bfdAoCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = bfdAoCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        ScanChannel* scanChannel = bfdAoCtrl->getScanChannel();
        ret = scanChannel->setChannelStart(configure.channelStart);
        CheckError(ret);
        ret = scanChannel->setChannelCount(configure.channelCount);
        CheckError(ret);
        ret = scanChannel->setSamples(configure.pointCountPerWave);
        CheckError(ret);
        ret = bfdAoCtrl->getConvertClock()->setRate(configure.clockRate);
        CheckError(ret);

        for (int i = 0; i < bfdAoCtrl->getChannels()->getCount(); i++) {
            ret = bfdAoCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
            CheckError(ret);
        }
}
//---------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnConfigClick(TObject *Sender)
{
        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }
}
//---------------------------------------------------------------------------

void TMainForm::ConfigurePanel() {
        if (configure.channelCount == 1) {
                BtnSineB->Enabled = false;
                BtnSquareB->Enabled = false;
                BtnTriangleB->Enabled = false;
                txtboxHiLevelB->Enabled = false;
                txtboxLoLevelB->Enabled = false;
                chLabelB->Caption = "";
        } else {
                BtnSineB->Enabled = true;
                BtnSquareB->Enabled = true;
                BtnTriangleB->Enabled = true;
                txtboxHiLevelB->Enabled = true;
                txtboxLoLevelB->Enabled = true;
                chLabelB->Caption = String((configure.channelStart + 1) % bfdAoCtrl->getChannelCount());
        }
        chLabelA->Caption = String(configure.channelStart);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::WaveButtonClick(TObject *Sender)
{
        int seledCH, baseIdx, imgIdx;

        TSpeedButton *button = (TSpeedButton*)Sender;
        seledCH = button->Tag / 3;
        baseIdx = seledCH * 3;

        for (int i = baseIdx; i < baseIdx + 3; i++) {
                imgIdx = (i - baseIdx) * 2;
                if (m_waveButton[i]->Down) {
                        imgIdx = imgIdx + 1;
                }

                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(imgIdx, bitmap);
                m_waveButton[i]->Glyph = bitmap;
        }

        m_waveSeled[seledCH] = button->Down;

        if (button->Down) {
                m_waveParam[seledCH].Style = button->Tag % 3;
        } else {
                m_waveParam[seledCH].Style = 2;
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnStartClick(TObject *Sender)
{
        int dataCount;
        ErrorCode ret = Success;

        if ((m_waveSeled[0] == false) && (m_waveSeled[1] == false)) {
                ShowMessage("Please select a waveform!");
                return;
        }

        //prepare the AO
        ret = bfdAoCtrl->Prepare();
        CheckError(ret);

        ScanChannel* scanChannel = bfdAoCtrl->getScanChannel();
        dataCount = scanChannel->getChannelCount() * scanChannel->getSamples();
        m_waveParam[0].PtsPerPeriod = scanChannel->getSamples();
        m_waveParam[1].PtsPerPeriod = scanChannel->getSamples();
        dataScaled = new double[dataCount];

        if ((m_waveSeled[0] == true) && (m_waveSeled[1] == false)) {
                m_waveParam[0].HiLevel = txtboxHiLevelA->Text.ToDouble();
                m_waveParam[1].HiLevel = 0;
                m_waveParam[0].LoLevel = txtboxLoLevelA->Text.ToDouble();
                m_waveParam[1].LoLevel = 0;
        } else if ((m_waveSeled[0] == false) && (m_waveSeled[1] == true)) {
                m_waveParam[0].HiLevel = 0;
                m_waveParam[1].HiLevel = txtboxHiLevelB->Text.ToDouble();
                m_waveParam[0].LoLevel = 0;
                m_waveParam[1].LoLevel = txtboxLoLevelB->Text.ToDouble();
        } else if ((m_waveSeled[0] == true) && (m_waveSeled[1] == true)) {
                m_waveParam[0].HiLevel = txtboxHiLevelA->Text.ToDouble();
                m_waveParam[1].HiLevel = txtboxHiLevelB->Text.ToDouble();
                m_waveParam[0].LoLevel = txtboxLoLevelA->Text.ToDouble();
                m_waveParam[1].LoLevel = txtboxLoLevelB->Text.ToDouble();
        }

        //generator the wave
        TWaveGenerator::GetWaveform(NULL, scanChannel->getChannelCount(), m_waveParam, 1, dataCount, dataScaled, dataCount-1);

       //Convert scaled  data to raw data
       ret = bfdAoCtrl->SetData(dataCount, dataScaled);
       CheckError(ret);

       //Start buffered AO in synchronous
       ret = bfdAoCtrl->RunOnce();
       CheckError(ret);
}
//---------------------------------------------------------------------------

void TMainForm::InitialButtons() {
        for (int i = 0; i < 6; i++) {
                m_waveButton[i]->Down = false;

                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap((i % 3) * 2, bitmap);
                m_waveButton[i]->Glyph = bitmap;
        }
}
//--------------------------------------------------------------------------

