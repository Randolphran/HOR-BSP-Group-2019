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
        pwMeterCtrl = PwMeterCtrl::Create();
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Pulse Width Measurement - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();

        btnStart->Enabled = true;
        btnStop->Enabled = false;
        btnConfig->Enabled = true;

        Timer1->Enabled = false;

        //initialize ECisRunning and  isPwMeterReset
        ECisRunning = true;
        isPwMeterReset = true;
}
//----------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = pwMeterCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = pwMeterCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        ret = pwMeterCtrl->setChannelStart(configure.channel);
        CheckError(ret);
        ret = pwMeterCtrl->setChannelCount(1);
        CheckError(ret);
}
//----------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//-----------------------------------------------------------------------------
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
        if (ECisRunning == true) {
                //Show event counting value
                PulseWidth pulseWidth;
                pwMeterCtrl->Read(1, &pulseWidth);

                hiPeriodEditor->Text = FormatFloat("0.000000", pulseWidth.HiPeriod);
                loPeriodEditor->Text = FormatFloat("0.000000", pulseWidth.LoPeriod);
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        if (isPwMeterReset == true) {
                cntrValueList->Clear();

                //start PwMeter
                ErrorCode ret = Success;
                ret = pwMeterCtrl->setEnabled(true);
                CheckError(ret);

                ECisRunning = true;

                if (Timer1->Enabled == false) {
                        Timer1->Enabled = true;
                }

                btnStop->Enabled = true;
                btnStart->Caption = "Latch";
                isPwMeterReset = false;
        } else {
                if (cntrValueList->Items->Count >= 7) {
                        cntrValueList->Items->Delete(0);
                }

                cntrValueList->Items->Add("High:" + hiPeriodEditor->Text + "  Low:" + loPeriodEditor->Text);
        }
        btnConfig->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        //Stop event counting
        ErrorCode ret = Success;
        ret = pwMeterCtrl->setEnabled(false);
        CheckError(ret);

        ECisRunning = false;
        isPwMeterReset = true;

        btnStart->Enabled = true;
        btnStart->Caption = "Start";
        btnStop->Enabled = false;

        //stop the timer
        if (ECisRunning == false) {
                Timer1->Enabled = false;
        }
        
        btnConfig->Enabled = true;
}
//---------------------------------------------------------------------------

