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
         freqMeterCtrl = FreqMeterCtrl::Create();
         
         graph = new TSimpleGraph(DataView);
         this->DoubleBuffered = true;
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Frequency Measurement - Run("  + deviceName + ")";
        this->Caption = caption;

        m_yaxisMax = 1000000;  // default is 1MHz
        isCounterReseted = true;

        ConfigureDevice();

        this->btnStart->Enabled = true;
        this->btnPause->Enabled = false;
        this->btnStop->Enabled = false;
        this->btnConfig->Enabled = true;

        InitializeGraph();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = freqMeterCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = freqMeterCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        ret = freqMeterCtrl->setChannelStart(configure.channel);
        CheckError(ret);
        ret = freqMeterCtrl->setChannelCount(1);
        CheckError(ret);
}
//---------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this -> WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void TMainForm::InitializeYAxis() {
        graph->YCordMax = m_yaxisMax;
        graph->YCordMin = 0;
        yTLabel->Caption = FormatFreqString(m_yaxisMax);
        yMLabel->Caption = FormatFreqString(m_yaxisMax / 2);
}
//---------------------------------------------------------------------------

AnsiString TMainForm::FormatFreqString(double freqHz) {
        AnsiString freqUnits[4] = {"Hz", "KHz", "MHz", "GHz"};
        AnsiString freq;
        int i;
        for (i = 0; i < 3; i++) {
                if (freqHz < 1000) {
                        break;
                } else {
                        freqHz = freqHz / 1000;
                }
        }
        
        freq = String(freqHz) + freqUnits[i];
        return freq;
}
//----------------------------------------------------------------------------

void TMainForm::InitializeGraph() {
        graph->XCordTimeDiv = 1000;
        InitializeYAxis();
        graph->Clear();
}
//-----------------------------------------------------------------------------

void __fastcall TMainForm::timerTrackBarChange(TObject *Sender)
{
        Timer1->Interval = timerTrackBar->Position;
        timerValueLabel->Caption =  String(timerTrackBar->Position) + "ms";
        graph->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::EnlargeClick(TObject *Sender)
{
        if (m_yaxisMax < 10000000) {
                graph->Clear();
                m_yaxisMax = m_yaxisMax * 10;
                InitializeYAxis();
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShortenClick(TObject *Sender)
{
        if (m_yaxisMax > 1) {
                graph->Clear();
                m_yaxisMax = m_yaxisMax / 10;
                InitializeYAxis();
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        if (isCounterReseted == true) {
                ErrorCode ret = Success;
                ret = freqMeterCtrl->setEnabled(true);
                CheckError(ret);

                btnStop->Enabled = true;
        }

        btnStart->Enabled = false;
        btnConfig->Enabled = false;
        btnPause->Enabled = true;
        Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnPauseClick(TObject *Sender)
{

        Timer1->Enabled = false;
        btnStart->Enabled = true;
        btnPause->Enabled = false;
        btnStop->Enabled = true;
        btnConfig->Enabled = false;
        isCounterReseted = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        ErrorCode ret = Success;
        ret = freqMeterCtrl->setEnabled(false);
        CheckError(ret);


        Timer1->Enabled = false;
        btnStart->Enabled = true;
        btnPause->Enabled = false;
        btnStop->Enabled = false;
        btnConfig->Enabled = true;
        isCounterReseted = true;
        graph->Clear();
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
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
        ErrorCode ret = Success;
        double value = 0.0;
        ret = freqMeterCtrl->Read(1, &value);
        CheckError(ret);
        frequency[0] = value;
        graph->Chart(frequency, 4, 1, 1, Timer1->Interval / 1000.0);
        editValue->Text = AnsiString::FormatFloat("0", frequency[0]);
}
//---------------------------------------------------------------------------
