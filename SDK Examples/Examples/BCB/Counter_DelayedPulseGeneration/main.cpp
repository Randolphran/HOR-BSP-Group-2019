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
        oneShotCtrl = OneShotCtrl::Create();
        oneShotCtrl->addOneShotHandler(OnCounterEvent, this);

        gif = new TGIFImage;
        gif->LoadFromResourceName(0, "execStatus");
        gif->Animate = false;
        ExecutionStatus->Picture->Graphic = gif;

        DelayedPulseCount = 1000;
        countOfValue = 0;

        clockCountEditor->Text = this->DelayedPulseCount;
        label_shotCount->Enabled = false;
        btnStop->Enabled = false;
}
//---------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//-----------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Delayed Pulse Generation - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();
}
//----------------------------------------------------------------------------
void BDAQCALL TMainForm::OnCounterEvent(void* sender, CntrEventArgs* args, void* userParam)
{
        TMainForm* uParam = (TMainForm*) userParam;
        uParam->countOfValue++;
        uParam->label_shotCount->Enabled = true;
        uParam->shotCountEditor->Text = uParam->countOfValue;
}
//----------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = oneShotCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = oneShotCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        ret = oneShotCtrl->setChannel(configure.channel);
        CheckError(ret);
        ret = oneShotCtrl->setChannelStart(configure.channel);
        CheckError(ret);
        ret = oneShotCtrl->setChannelCount(1);
        CheckError(ret);
}

void __fastcall TMainForm::btnConfigClick(TObject *Sender)
{
        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        //stop oneShot
        ErrorCode ret = Success;
        ret = oneShotCtrl->setEnabled(false);
        CheckError(ret);

        btnStop->Enabled = false;
        btnStart->Enabled = true;
        btnConfig->Enabled = true;
        clockCountEditor->Enabled = true;

        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = false;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        this->countOfValue = 0;
        this->shotCountEditor->Text = "";

        DelayedPulseCount = clockCountEditor->Text.ToInt();
        
        ErrorCode ret = Success;
        Array<OsChannel>*osChannel = oneShotCtrl->getChannels();
        for(int32 i = configure.channel; i < configure.channel + 1; i++)
        {
            ret = osChannel->getItem(i).setDelayCount(DelayedPulseCount);
            CheckError(ret);
        }
        ret = oneShotCtrl->setEnabled(true);
        CheckError(ret);

        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = true;

        clockCountEditor->Enabled = false;
        btnStart->Enabled = false;
        btnStop->Enabled = true;
        btnConfig->Enabled = false;
}
//---------------------------------------------------------------------------

