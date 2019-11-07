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
        eventCounterCtrl = EventCounterCtrl::Create();
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Event Counter - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();

        btnStart -> Enabled = true;
        btnStop -> Enabled = false;
        btnConfig -> Enabled = true;

        Timer1 ->Enabled = false;

        //initialize ECisRunning and  isEventCountingReset
        ECisRunning = true;
        isEventCountingReset = true;
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

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
        ErrorCode   ret = Success;
        int32 value = 0;
        ret = eventCounterCtrl->Read(1, &value);
        CheckError(ret);
        curValueEditor->Text = value;
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = eventCounterCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = eventCounterCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);
        ret = eventCounterCtrl->setChannelStart(configure.channel);
        CheckError(ret);
        ret = eventCounterCtrl->setChannelCount(1);
        CheckError(ret);
}

void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        //Stop event counting
        ErrorCode ret = Success;
        ret = eventCounterCtrl->setEnabled(false);
        CheckError(ret);
        ECisRunning = false;

        isEventCountingReset = true;
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

void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        ErrorCode ret = Success;
        if (isEventCountingReset == true) {
                cntrValueList->Items->Clear();

                ret = eventCounterCtrl->setEnabled(true);
                ECisRunning = true;

                if (Timer1->Enabled == false) {
                        Timer1->Enabled = true;
                }

                btnStop->Enabled = true;
                btnStart->Caption = "Latch";
                isEventCountingReset = false;
        } else {
                if (cntrValueList->Items->Count >= 5) {
                        cntrValueList->Items->Delete(0);
                }
                cntrValueList->Items->Add(curValueEditor->Text);
        }
        btnConfig->Enabled = false;
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

