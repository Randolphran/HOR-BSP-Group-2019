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
        bfdPwModulatorCtrl = BufferedPwModulatorCtrl::Create();
        bfdPwModulatorCtrl->addTransitStoppedHandler(OnDataTransmittedEvent, this);

        gif = new TGIFImage;
        gif->LoadFromResourceName(0, "execStatus");
        gif->Animate = false;
        ExecutionStatus->Picture->Graphic = gif;

        this->data1_hiPeriod->Text = String(0.08);
        this->data1_loPeriod->Text = String(0.02);
        this->data2_hiPeriod->Text = String(0.05);
        this->data2_loPeriod->Text = String(0.05);

        btnStop->Enabled = false;
}
//---------------------------------------------------------------------------
__fastcall TMainForm::~TMainForm()
{
        if (pulseWidth != NULL) {
                delete[] pulseWidth;
                pulseWidth = NULL;
        }
        if(channelEnable != NULL){
                delete[] channelEnable;
                channelEnable = NULL;
        }
        if(bfdPwModulatorCtrl != NULL){
                bfdPwModulatorCtrl->Dispose();
                bfdPwModulatorCtrl= NULL;
        }
}
//---------------------------------------------------------------------------
void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Buffered PWM Output - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = bfdPwModulatorCtrl->setSelectedDevice(devInfo);
        CheckError(ret);

        channelCountMax = bfdPwModulatorCtrl->getFeatures()->getChannelCountMax();
        channelEnable = new int8[channelCountMax];
        memset(channelEnable, 0, sizeof(int8)* channelCountMax);

        //configure parameters mode (Profile configure/Manual configure)
        if(configure.configureMode == Profile_Confiugre){
                ret = bfdPwModulatorCtrl->LoadProfile(configure.profilePath);
                CheckError(ret);
                bfdPwModulatorCtrl->getChannelMap(channelCountMax, channelEnable);
                samplesCount = bfdPwModulatorCtrl->getSamples();
        }else{
                memcpy(channelEnable, configure.channelEnable, sizeof(int8) * channelCountMax);

                ret = bfdPwModulatorCtrl->setChannelMap(channelCountMax, configure.channelEnable);
                CheckError(ret);
                ret = bfdPwModulatorCtrl->setIntervalCount(configure.intervalCount);
                CheckError(ret);
                samplesCount = 2 * configure.intervalCount;
                ret = bfdPwModulatorCtrl->setSamples(samplesCount);
                CheckError(ret);
                ret = bfdPwModulatorCtrl->setStreaming(true);
                CheckError(ret);
                ret = bfdPwModulatorCtrl->setSampleClkSrc(configure.clkSource);
                CheckError(ret);

                // For trigger
                Trigger* trig = bfdPwModulatorCtrl->getTrigger();
                if (trig){
                        ret = trig->setSource(configure.trgSource);
                        CheckError(ret);
                        ret = trig->setAction(configure.trgAction);
                        CheckError(ret);
                        ret = trig->setEdge(configure.trgEdge);
                        CheckError(ret);
                        ret = trig->setLevel(configure.trgLevel);
                        CheckError(ret);
                }
        }
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

        ConfigForm->RefreshConfigureParameter();
        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }        
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        ErrorCode ret = Success;
        pulseWidth = new PulseWidth[samplesCount];

        ret = bfdPwModulatorCtrl->Prepare();
        CheckError(ret);

        for(int i = 0; i < samplesCount; i++){
                if((i & 0x1) == 0){
                        pulseWidth[i].HiPeriod = data1_hiPeriod->Text.ToDouble();
                        pulseWidth[i].LoPeriod = data1_loPeriod->Text.ToDouble();
                }else{
                        pulseWidth[i].HiPeriod = data2_hiPeriod->Text.ToDouble();
                        pulseWidth[i].LoPeriod = data2_loPeriod->Text.ToDouble();
                }
        }

        for(int i = 0; i < channelCountMax; i++){
                if(channelEnable[i]){
                        ret = bfdPwModulatorCtrl->SetData(i, samplesCount, pulseWidth);
                }
        }

        ret = bfdPwModulatorCtrl->setEnabled(true);
        CheckError(ret);

        //Enable execution status
        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = true;

        data1_hiPeriod->Enabled = false;
        data1_loPeriod->Enabled = false;
        data2_hiPeriod->Enabled = false;
        data2_loPeriod->Enabled = false;
        btnStart->Enabled = false;
        btnStop->Enabled = true;
        btnConfig->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
        //stop the BufferedPwModulator
        ErrorCode ret = Success;
        ret = bfdPwModulatorCtrl->setEnabled(false);
        CheckError(ret);

        //Disable execution status
        TGraphic * graphic = ExecutionStatus->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = false;

        btnStop->Enabled = false;
        btnStart->Enabled = true;
        btnConfig->Enabled = true;

        data1_hiPeriod->Enabled = true;
        data1_loPeriod->Enabled = true;
        data2_hiPeriod->Enabled = true;
        data2_loPeriod->Enabled = true;
}
//---------------------------------------------------------------------------
void BDAQCALL TMainForm::OnDataTransmittedEvent(void *sender, BfdCntrEventArgs * args, void * userParam)
{
    // Nothing to do 
}





