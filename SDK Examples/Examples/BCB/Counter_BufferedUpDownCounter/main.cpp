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
        bfdUdCounterCtrl = BufferedUdCounterCtrl::Create();
        dataBuf = NULL;
        chs_dataBuf = NULL;
        channelEnable = NULL;
        chs_Status = NULL;
        bfdUdCounterCtrl->addDataReadyHandler(OnDataReadyEvent, this);
        bfdUdCounterCtrl->addStoppedHandler(OnStoppedEvent, this);
}
//---------------------------------------------------------------------------

__fastcall TMainForm::~TMainForm()
{
        if (dataBuf != NULL) {
                delete[] dataBuf;
                dataBuf = NULL;
        }
        if(channelEnable != NULL){
                delete[] channelEnable;
                channelEnable = NULL;
        }
        if(chs_Status != NULL){
                delete []chs_Status;
                chs_Status = NULL;
        }
        if(chs_dataBuf != NULL){
                for(int i = 0; i < channelCountMax; i++){
                        if(chs_dataBuf[i] != NULL)
                        delete []chs_dataBuf[i];
                }
                chs_dataBuf = NULL;
        }
        if(bfdUdCounterCtrl != NULL){
                bfdUdCounterCtrl->Dispose();
                bfdUdCounterCtrl= NULL;
        }
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Buffered Up Down Counter - Run("  + deviceName + ")";
        this->Caption = caption;
        txtChannelStatus->Clear();
        cntrValueList->Clear();
        
        ConfigureDevice();
        btnStart->Enabled = true;
        btnStop->Enabled = false;
        btnConfig->Enabled = true;
        txtChannelStatus->Enabled = true;
        cntrValueList->Enabled = true;

        //initialize
        isRunning = false;
        haveData = false;
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

void TMainForm::ConfigureDevice() {
        ErrorCode ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = bfdUdCounterCtrl->setSelectedDevice(devInfo);
        CheckError(ret);

        channelCountMax = bfdUdCounterCtrl->getFeatures()->getChannelCountMax();
        channelEnable = new int8[channelCountMax];
        memset(channelEnable, 0, sizeof(int8)* channelCountMax);

        chs_Status = new AnsiString[channelCountMax];
        
        //configure parameters mode (Profile configure/Manual configure)
        if(configure.configureMode == Profile_Confiugre){
                ret = bfdUdCounterCtrl->LoadProfile(configure.profilePath);
                CheckError(ret);
                bfdUdCounterCtrl->getChannelMap(channelCountMax, channelEnable);
                sectionLength = bfdUdCounterCtrl->getRecord()->getSectionLength();
                sectionCount = bfdUdCounterCtrl->getRecord()->getSectionCount();
        }else{
                memcpy(channelEnable, configure.channelEnable, sizeof(int8) * channelCountMax);
                sectionLength = configure.sectionLength;
                sectionCount = configure.sectionCount;
                
                ret = bfdUdCounterCtrl->setChannelMap(channelCountMax, configure.channelEnable);
                CheckError(ret);
                ret = bfdUdCounterCtrl->setSampleClkSrc(configure.clkSource);
                CheckError(ret);

                for (int i = 0; i < channelCountMax; i++)
                {
                        if(configure.channelEnable[i]){
                                ret = bfdUdCounterCtrl->getChannels()->getItem(i).setCountingType(configure.cntType);
                                CheckError(ret);
                        }
                }
                Record* record = bfdUdCounterCtrl->getRecord();
                ret = record->setSectionLength(configure.sectionLength);
                CheckError(ret);
                ret = record->setSectionCount(configure.sectionCount);
                CheckError(ret);

                Trigger* trg = bfdUdCounterCtrl->getTrigger();
                if(trg){
                        ret = trg->setSource(configure.trgSource);
                        CheckError(ret);
                        ret = trg->setAction(configure.trgAction);
                        CheckError(ret);
                        ret = trg->setEdge(configure.trgEdge);
                        CheckError(ret);
                        ret = trg->setLevel(configure.trgLevel);
                        CheckError(ret);
                }
        }

        samplesCount = sectionLength;
        if(sectionCount){
                samplesCount *=  sectionCount;
        }

        if(samplesCount <= 1){
                samplesCount = 2;
        }
        dataBuf = new int32[samplesCount];
        memset(dataBuf, 0, sizeof(int32) * samplesCount);

        chs_dataBuf = new int32*[channelCountMax];
        for(int i = 0; i < channelCountMax; i++){
                chs_dataBuf[i] = new int32[samplesCount];
                memset(chs_dataBuf[i], 0, sizeof(int32) * samplesCount);
        }

        if ((dataBuf == NULL) || (chs_dataBuf == NULL)) {
                AnsiString str = "Sorry! Error in allocating memory....";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        
        cbxDisplayChannel->Clear();
         // Set displayChannel combo box
        for(int i = 0; i < channelCountMax; i++){
                if(channelEnable[i]){
                        cbxDisplayChannel->AddItem(i, this);
                }
        }
        cbxDisplayChannel->ItemIndex = 0;

        // Setting Status is Ready.
        for(int i = 0; i < channelCountMax; i++){
                if(channelEnable[i]){
                        ChannelStatusChange(i, "Ready");
                }
         }

         displayChannel = cbxDisplayChannel->Text.ToInt();
         DisplayChannelStatus(displayChannel);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnStopClick(TObject *Sender)
{
       ErrorCode ret = Success;
        ret = bfdUdCounterCtrl->setEnabled(false);
        CheckError(ret);
        isRunning = false;

        btnStart->Enabled = true;
        btnStop->Enabled = false;
        btnConfig->Enabled = true;

        for(int i = 0; i < channelCountMax; i++){
        if(channelEnable[i] == 1){
                ChannelStatusChange(i, "Stopped");
                }
        }
        DisplayChannelStatus(displayChannel);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnStartClick(TObject *Sender)
{
        ErrorCode ret = Success;
        for(int i = 0; i < channelCountMax; i++){
        if(channelEnable[i] == 1){
                ChannelStatusChange(i, "Running");
                }
        }
        DisplayChannelStatus(displayChannel);

        cntrValueList->Items->Clear();
        ret = bfdUdCounterCtrl->Prepare();
        CheckError(ret);
        ret = bfdUdCounterCtrl->setEnabled(true);
        CheckError(ret);
        isRunning = true;
        haveData = true;
        btnStart->Enabled = false;
        btnStop->Enabled = true;

        btnConfig->Enabled = false;
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
        haveData = false;
}
//---------------------------------------------------------------------------

void BDAQCALL TMainForm::OnDataReadyEvent(void *sender, BfdCntrEventArgs * args, void * userParam)
{
        TMainForm* uParam = (TMainForm*) userParam;
        //Get Data
        ErrorCode ret = Success;
        BufferedUdCounterCtrl*ctrl = (BufferedUdCounterCtrl*)sender;
        int32 getDataCount = Min(uParam->samplesCount, args->Count);
        uParam->eventChannel = args->Channel;
        if((getDataCount) && (args->Channel == uParam->displayChannel)){
                ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, NULL);
                if(ret == Success){
                        uParam->CopyChannelData(uParam->eventChannel);
                        uParam->DisplayChannelValue(uParam->displayChannel);
                }
        }
}
//---------------------------------------------------------------------------

void BDAQCALL TMainForm::OnStoppedEvent(void *sender, BfdCntrEventArgs * args, void * userParam)
{
        TMainForm* uParam = (TMainForm*) userParam;
        //Get Data
        ErrorCode ret = Success;
        BufferedUdCounterCtrl* Ctrl = (BufferedUdCounterCtrl*)sender;
        int32 getDataCount = Min(uParam->samplesCount, args->Count);
        uParam->eventChannel = args->Channel;
        if((getDataCount) && (args->Channel == uParam->displayChannel)){
                ret = Ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, NULL);
                if(ret == Success){
                        uParam->CopyChannelData(uParam->eventChannel);
                        uParam->DisplayChannelValue(uParam->displayChannel);
                }
        }

        if(Ctrl->getState() == Stopped){
                ErrorCode ret = Ctrl->setEnabled(false);
                uParam->CheckError(ret);
                uParam->isRunning = false;

	        uParam->btnStart->Enabled = true;
	        uParam->btnConfig->Enabled = true;
	        uParam->btnStop->Enabled = false;
        }

	uParam->ChannelStatusChange(uParam->eventChannel, "Stopped");
	uParam->DisplayChannelStatus(uParam->displayChannel);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbxDisplayChannelChange(TObject *Sender)
{
        displayChannel = cbxDisplayChannel->Text.ToInt();

        DisplayChannelStatus(displayChannel);
        DisplayChannelValue(displayChannel);        
}
//---------------------------------------------------------------------------

void TMainForm::ChannelStatusChange(int32 channel, AnsiString string)
{
    chs_Status[channel] = string;
}
//---------------------------------------------------------------------------

void TMainForm::DisplayChannelStatus(int channel)
{
       int ch = channel;
       txtChannelStatus->Text = chs_Status[ch];
}
//---------------------------------------------------------------------------

void TMainForm::DisplayChannelValue(int channel)
{
        int ch = channel;
        cntrValueList->Clear();

        int32 listCount = 0;
        if(sectionLength >= MAX_ROW_COUNT){
                listCount = MAX_ROW_COUNT;
        }else{
                listCount = sectionLength;
        }

        AnsiString str;
        if(haveData | isRunning){
                for(int i = 0; i < listCount; i++){
                        str = IntToStr(chs_dataBuf[ch][i]);
                        cntrValueList->Items->Add(str);
                }
        }
}

//---------------------------------------------------------------------------

void TMainForm::CopyChannelData(int channel)
{
        int ch = channel;
        memcpy(chs_dataBuf[ch], dataBuf, sizeof(int32)*samplesCount);
}
