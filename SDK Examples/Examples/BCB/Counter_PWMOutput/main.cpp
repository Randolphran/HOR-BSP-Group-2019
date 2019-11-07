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
        pwModulatorCtrl = PwModulatorCtrl::Create();

        gif = new TGIFImage;
        gif->LoadFromResourceName(0, "execStatus");
        gif->Animate = false;
        ExecutionStatus->Picture->Graphic = gif;

        this->hiPeriodEditor->Text = String(0.08);
        this->loPeriodEditor->Text = String(0.02);

        btnStop->Enabled = false;
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "PWM Output - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = pwModulatorCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = pwModulatorCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        ret = pwModulatorCtrl->setChannelCount(1);
        CheckError(ret);
        ret = pwModulatorCtrl->setChannelStart(configure.channel);
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

void __fastcall TMainForm::btnConfigClick(TObject *Sender)
{
        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }        
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        PulseWidth pulseWidth;
        pulseWidth.HiPeriod = hiPeriodEditor->Text.ToDouble();
        pulseWidth.LoPeriod = loPeriodEditor->Text.ToDouble();

        //set PulseWidth.
        ErrorCode ret = Success;
        Array<PoChannel>* poChannel = pwModulatorCtrl->getChannels();
        for(int i = configure.channel; i < configure.channel + 1; i++ )
        {
            ret = poChannel->getItem(i).setPulseWidth(pulseWidth);
            CheckError(ret);
        }

        ret = pwModulatorCtrl->setEnabled(true);
        CheckError(ret);

        //Enable execution status
        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = true;

        pwModulatorCtrl->getPulseWidth(pulseWidth);
        actualHiPeriod->Text = pulseWidth.HiPeriod;
        actualLoPeriod->Text = pulseWidth.LoPeriod;

        hiPeriodEditor->Enabled = false;
        loPeriodEditor->Enabled = false;
        btnStart->Enabled = false;
        btnStop->Enabled = true;
        btnConfig->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        //stop the PwModulator
        ErrorCode ret = Success;
        ret = pwModulatorCtrl->setEnabled(false);
        CheckError(ret);

        //Disable execution status
        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = false;

        btnStop->Enabled = false;
        btnStart->Enabled = true;
        btnConfig->Enabled = true;
        hiPeriodEditor->Enabled = true;
        loPeriodEditor->Enabled = true;
}
//---------------------------------------------------------------------------
