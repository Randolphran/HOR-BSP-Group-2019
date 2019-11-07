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
        timerPulseCtrl = TimerPulseCtrl::Create();
        timerPulseCtrl->addTimerTickHandler(OnCounterEvent, this);

        gif = new TGIFImage;
        gif->LoadFromResourceName(0, "execStatus");
        gif->Animate = false;
        ExecutionStatus->Picture->Graphic = gif;
        
        eventCount = 0;
        userFreqEditor->Text = String(50);

        btnStop->Enabled = false;
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Pulse Output with Timer Interrupt - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        devInfo.ModuleIndex = configure.moduleIndex;
        ret = timerPulseCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = timerPulseCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        ret = timerPulseCtrl->setChannelStart(configure.channel);
        CheckError(ret);
        ret = timerPulseCtrl->setChannelCount(1);
        CheckError(ret);
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
void BDAQCALL TMainForm::OnCounterEvent(void *sender, CntrEventArgs *args, void *userParam)
{
        TMainForm *uParam = (TMainForm *) userParam;
        uParam->eventCount++;
        uParam->evtCountEditor->Text = uParam->eventCount;

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
        this->eventCount = 0;
        this->evtCountEditor->Text = "";

        double frequence = userFreqEditor->Text.ToDouble();

        ErrorCode ret = Success;
        ret = timerPulseCtrl->setFrequency(frequence);
        CheckError(ret);
        ret = timerPulseCtrl->setEnabled(true);
        CheckError(ret);
        
        devFreqEditor->Text = timerPulseCtrl->getFrequency();

        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = true;

        userFreqEditor->Enabled = false;
        btnStart->Enabled = false;
        btnStop->Enabled = true;
        btnConfig->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        //stop TimerPulse.
        ErrorCode ret = Success;
        ret = timerPulseCtrl->setEnabled(false);
        CheckError(ret);

        btnStop->Enabled = false;
        btnStart->Enabled = true;
        btnConfig->Enabled = true;
        userFreqEditor->Enabled = true;

        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = false;
}
//---------------------------------------------------------------------------
