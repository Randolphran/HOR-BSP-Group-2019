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
        instantAoCtrl = InstantAoCtrl::Create();
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Static AO - Run("  + deviceName + ")";
        this->Caption = caption;

        //initialize these variables
        channelStart = 0;
        channelCount = 0;

        for (int i = 0; i < 2; i++) {
                m_waveParam[i].PtsPerPeriod = configure.pointCountPerWave;
        }

        m_waveButton[0] = BtnSineA;
        m_waveButton[1] = BtnTriangleA;
        m_waveButton[2] = BtnSquareA;
        m_waveButton[3] = BtnSineB;
        m_waveButton[4] = BtnTriangleB;
        m_waveButton[5] = BtnSquareB;

        //initialize a timer which drive the data acquisition.
        Timer1->Interval = 50;

        ConfigureDevice();
        ConfigurePanel();

        Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = instantAoCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = instantAoCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        for (int i = 0; i < instantAoCtrl->getChannels()->getCount(); i++) {
            ret = instantAoCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
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


void __fastcall TMainForm::btnConfigureClick(TObject *Sender)
{
        Timer1->Enabled = false;

        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }
}
//---------------------------------------------------------------------------

void TMainForm::ConfigurePanel() {
        if (configure.channelCount == 1) {
                channelStart = configure.channelStart;
                channelCount = 1;

                BtnSineB->Enabled = false;
                BtnSquareB->Enabled = false;
                BtnTriangleB->Enabled = false;
                BtnManualB->Enabled = false;
                txtboxHiLevelB->Enabled = false;
                txtboxLoLevelB->Enabled = false;
                txtboxValueB->Enabled = false;
                chLabelB->Caption = "";
        } else {
                channelStart = configure.channelStart;
                channelCount = 2;

                BtnSineB->Enabled = true;
                BtnSquareB->Enabled = true;
                BtnTriangleB->Enabled = true;
                BtnManualB->Enabled = true;
                txtboxHiLevelB->Enabled = true;
                txtboxLoLevelB->Enabled = true;
                txtboxValueB->Enabled = true;
                chLabelB->Caption = String((channelStart + 1) % instantAoCtrl->getChannelCount());
        }

        chLabelA->Caption = String(channelStart);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::timerTrackBarChange(TObject *Sender)
{
        Timer1->Interval = timerTrackBar->Position;
        timerFreqLabel->Caption = String(timerTrackBar->Position) + "ms";        
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ManualOutClick(TObject *Sender)
{
        int ch, baseIdx;

        //manual ouput button click
        TButton *button = (TButton*)Sender;
        ch = button->Tag;
        baseIdx = ch * 3;

        for (int i = 0; i < 3; i++) {
                if (m_waveButton[i + baseIdx]->Down) {
                        m_waveButton[i + baseIdx]->Down = false;
                        bitmap = new Graphics::TBitmap();
                        ImageList1->GetBitmap(i * 2, bitmap);
                        m_waveButton[i + baseIdx]->Glyph = bitmap;
                }
        }

        m_waveSeled[ch] = false;

        if (ch == 0) {
                dataScaled[ch] = txtboxValueA->Text.ToDouble();
        } else {
                dataScaled[ch] = txtboxValueB->Text.ToDouble();
        }
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
        m_waveParam[seledCH].Style = button->Tag % 3;

        if (seledCH == 0) {
                m_waveParam[seledCH].HiLevel = txtboxHiLevelA->Text.ToDouble();
                m_waveParam[seledCH].LoLevel = txtboxLoLevelA->Text.ToDouble();
        } else {
                m_waveParam[seledCH].HiLevel = txtboxHiLevelB->Text.ToDouble();
                m_waveParam[seledCH].LoLevel = txtboxLoLevelB->Text.ToDouble();
        }

        m_wavePtIdx[seledCH] = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
        ErrorCode ret = Success;

        for (int i = 0; i < 2; i++) {
                if (m_waveSeled[i]) {
                        dataScaled[i] = TWaveGenerator::GetOnePoint(NULL, m_waveParam[i], m_wavePtIdx[i]);
                        m_wavePtIdx[i] = (m_wavePtIdx[i] + 1) % m_waveParam[i].PtsPerPeriod;
                }
        }

        ret = instantAoCtrl->WriteAny(channelStart, channelCount, NULL, dataScaled);
        if (ret != Success) {
                Timer1->Enabled = false;
                CheckError(ret);
        }
}
//---------------------------------------------------------------------------


