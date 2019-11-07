//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "config.h"
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm(TComponent* Owner)
        : TForm(Owner)
{
        isFirstLoad = true;
        isBtnOkClicked = false;
        Initialization();
}
//---------------------------------------------------------------------------
__fastcall TConfigForm::~TConfigForm()
{
       if(m_bfdPwMeterCtrl != NULL){
                m_bfdPwMeterCtrl->Dispose();
                m_bfdPwMeterCtrl= NULL;
        }
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::btnCancelClick(TObject *Sender)
{
        this->Close();        
}
//---------------------------------------------------------------------------
void TConfigForm::InitialChkBox()
{
        chkListBox->Clear();
        chkListBox->Columns = 2;
        for(int i =0; i < channelCountMax; i++){
                AnsiString str = "CH" + IntToStr(i);
                chkListBox->Items->Add(str.c_str());
        }
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        if (isFirstLoad && !isBtnOkClicked) {
                exit(0);
        }
        Action = caHide;
}
//---------------------------------------------------------------------------

void TConfigForm::Initialization()
{
        m_bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = m_bfdPwMeterCtrl->getSupportedDevices();

        if (supportedDevice->getCount() == 0) {
                MessageBox(this->WindowHandle, "No device to support the currently demonstrated function!", "Warning Information", MB_ICONWARNING);
                exit(0);
        } else {
                for (int i = 0; i < supportedDevice->getCount(); i++) {
                cmbDevice->AddItem(supportedDevice->getItem(i).Description, this);
        }
                cmbDevice->ItemIndex = 0;
        }
        supportedDevice->Dispose();

        this->cmbDeviceChange(this);
}

void __fastcall TConfigForm::cmbDeviceChange(TObject *Sender)
{
        cbxTrgSource->Clear();
        cbxTrgEdge->Clear();
        cbxTrgAction->Clear();
        cbxSampleClkSrc->Clear();

        Array<DeviceTreeNode> *supportedDevice = m_bfdPwMeterCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = m_bfdPwMeterCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

         //Default using Manual Configure
         radioBtnClick(this);

         channelCountMax = m_bfdPwMeterCtrl->getFeatures()->getChannelCountMax();

         //initial channel enable
        configure.channelEnable = new int8[channelCountMax];
        memset(configure.channelEnable, 0, sizeof(int8) * channelCountMax);

        InitialChkBox();

        // Set Sample Clock Source combo box
        CounterClockSourceIndexer* indexer = m_bfdPwMeterCtrl->getFeatures()->getPiSampleClockSources();
        for(int i = 0; i < indexer->getItem(0)->getCount(); i++){
                SignalDrop clkSrc = indexer->getItem(0)->getItem(i);
                wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
                ret = AdxEnumToString(L"SignalDrop", clkSrc, MAX_SIG_DROP_DESC_LEN, enumStr);
                CheckError(ret);
                cbxSampleClkSrc->AddItem(enumStr, this);
        }
        cbxSampleClkSrc->ItemIndex = 0;;

        // Set Trigger Source combo box
        Array<SignalDrop>* trgSrc = m_bfdPwMeterCtrl->getFeatures()->getTriggerSources();
        for(int i = 0; i< trgSrc->getCount(); i++){
                wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
                ret = AdxEnumToString(L"SignalDrop", trgSrc->getItem(i), MAX_SIG_DROP_DESC_LEN, enumStr);
                CheckError(ret);
                cbxTrgSource->AddItem(enumStr, this);
        }
        cbxTrgSource->ItemIndex = 0;
        cbxTrgSourceChange(this);

        // Set Trigger Action combo box
        Array<TriggerAction>* trgAct = m_bfdPwMeterCtrl->getFeatures()->getTriggerActions();
        for(int i = 0; i < trgAct->getCount(); i++){
                wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
                ret = AdxEnumToString(L"TriggerAction", trgAct->getItem(i), MAX_SIG_DROP_DESC_LEN, enumStr);
                CheckError(ret);
                cbxTrgAction->AddItem(enumStr, this);
        }
        cbxTrgAction->ItemIndex = 0;

        // Set Trigger Edge combo box
        cbxTrgEdge->AddItem("RisingEdge", this);
        cbxTrgEdge->AddItem("FallingEdge", this);
        cbxTrgEdge->ItemIndex = 0;

        supportedDevice->Dispose();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::FormCreate(TObject *Sender)
{
        this->ShowModal();        
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::btnOkClick(TObject *Sender)
{
        if (cmbDevice->Items->Count == 0) {
                exit(0);
        }

        if (txtSectionLength->Text.Trim() == "") {
                MessageBox(this->WindowHandle, "Please enter a number!", "Warning Information", MB_ICONWARNING);
                txtSectionLength->Text = 1024;
                return;
        }

        if(radProfile->Checked){
                if(txtProfilePath->Text == ""){
                        MessageBox(this->WindowHandle, "Sorry, profile path is null, please select the device's profile", "Warning Information", MB_ICONWARNING);
                }else{
                        WideString wstr = txtProfilePath->Text;
                        configure.profilePath = wstr.c_bstr();
                        configure.configureMode = Profile_Confiugre;

                        WideString wstring = cmbDevice->Text;
                        wchar_t *deviceDescription = wstring.c_bstr();
                        configure.deviceName = deviceDescription;

                        MainForm->SetConfigureParameter(GetConfigureParameter());
                        MainForm->Initialization();

                        this->isBtnOkClicked = true;
                        ModalResult = mrOk;
                }
        }else{
                Array<DeviceTreeNode> *supportedDevice = m_bfdPwMeterCtrl->getSupportedDevices();
                WideString wstring = cmbDevice->Text;
                wchar_t *deviceDescription = wstring.c_bstr();

                configure.deviceName = deviceDescription;
                configure.deviceNumber = supportedDevice->getItem(cmbDevice->ItemIndex).DeviceNumber;
                configure.sectionLength = txtSectionLength->Text.ToInt();
                configure.sectionCount = txtSectionCount->Text.ToInt();

                Array<SignalDrop>*  sources = m_bfdPwMeterCtrl->getFeatures()->getTriggerSources();
                configure.trgSource = sources->getItem(cbxTrgSource->ItemIndex);

                if(cbxTrgEdge->ItemIndex == 0){
                        configure.trgEdge = RisingEdge;
                } else {
                        configure.trgEdge = FallingEdge;
                }

                Array<TriggerAction>* trgAct = m_bfdPwMeterCtrl->getFeatures()->getTriggerActions();
                configure.trgAction = trgAct->getItem(cbxTrgAction->ItemIndex);

                configure.trgLevel = txtTrgLevel->Text.ToDouble();
                supportedDevice->Dispose();

                int sum = 0;
                 for(int i = 0; i < channelCountMax; i++){
                         sum += configure.channelEnable[i];
                 }
                 if(sum){
                         MainForm->SetConfigureParameter(GetConfigureParameter());
                         MainForm->Initialization();

                         this->isBtnOkClicked = true;
                         ModalResult = mrOk;
                 }else{
                         MessageBox(this->WindowHandle, "Please enable at least one channel!", "Warning Information", MB_ICONWARNING);
                 }
        }
}
//---------------------------------------------------------------------------

void TConfigForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}

//----------------------------------------------------------------------------

void __fastcall TConfigForm::btnBrowseClick(TObject *Sender)
{
        TOpenDialog *test = new TOpenDialog(this);
        AnsiString string;
        test->Title = "Select Profile";
        test->InitialDir = "..\..\profile";
        test->Filter="txt files (*.xml)|*.xml";

        if(test->Execute())
        {
                txtProfilePath->Text = test->FileName;
        }
        delete test;           
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::cbxTrgSourceChange(TObject *Sender)
{
        Array<SignalDrop>*  sources = m_bfdPwMeterCtrl->getFeatures()->getTriggerSources();
        SignalDrop trgSource = sources->getItem(cbxTrgSource->ItemIndex);
        switch(trgSource)
        {
         case SignalNone:
                cbxTrgAction->Enabled = false;
                cbxTrgEdge->Enabled = false;
                txtTrgLevel->Enabled = false;
                break;
         case SigDiPatternMatch:
         case SigDiStatusChange:
                cbxTrgAction->Enabled = true;
                cbxTrgEdge->Enabled = false;
                txtTrgLevel->Enabled = false;
                break;
         default:
                cbxTrgAction->Enabled = true;
                cbxTrgEdge->Enabled = true;
                txtTrgLevel->Enabled = true;
                break;
         }
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::radioBtnClick(TObject *Sender)
{
        if(radProfile->Checked){
                configure.configureMode = 1;
        }
        if(radManual->Checked){
                configure.configureMode = 0;
        }
        ComponentEnabled(configure.configureMode);
}

//---------------------------------------------------------------------------

void __fastcall TConfigForm::checkBoxClick(TObject *Sender)
{
        int index = dynamic_cast <TCheckListBox *> (Sender)->ItemIndex;
        if(chkListBox->Checked[index]){
                configure.channelEnable[index] = 1;
        }else{
                configure.channelEnable[index] = 0;
        }
}
//---------------------------------------------------------------------------

void TConfigForm::ComponentEnabled(bool flag)
{
        if(flag == 1){
                txtProfilePath->Enabled = true;
                btnBrowse->Enabled = true;
                chkListBox->Enabled = false;
                txtSectionCount->Enabled = false;
                txtSectionLength->Enabled = false;
                cbxSampleClkSrc->Enabled = false;
                cbxTrgSource->Enabled = false;
        }else{
                txtProfilePath->Enabled = false;
                btnBrowse->Enabled = false;
                chkListBox->Enabled = true;
                txtSectionCount->Enabled = true;
                txtSectionLength->Enabled = true;
                cbxSampleClkSrc->Enabled = true;
                cbxTrgSource->Enabled = true;
        }
}
//---------------------------------------------------------------------------
void  TConfigForm::RefreshConfigureParameter()
{
        BufferedPwMeterCtrl* bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();
        WideString wstr = cmbDevice->Text;
        wchar_t *deviceDescription = wstr.c_bstr();
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = bfdPwMeterCtrl->setSelectedDevice(devInfo);
        CheckError(ret);

        txtSectionLength->Text = bfdPwMeterCtrl->getRecord()->getSectionLength();
        txtSectionCount->Text = bfdPwMeterCtrl->getRecord()->getSectionCount();

        SignalDrop clkSrc = bfdPwMeterCtrl->getSampleClkSrc();
        CounterClockSourceIndexer* indexer = bfdPwMeterCtrl->getFeatures()->getPiSampleClockSources();
        for(int i = 0; i < indexer->getItem(0)->getCount(); i++){
                if(clkSrc == indexer->getItem(0)->getItem(i)){
                        cbxSampleClkSrc->ItemIndex = i;
                        break;
                }
        }

        SignalDrop trgSrc = bfdPwMeterCtrl->getTrigger()->getSource();
        Array<SignalDrop>*  sources = bfdPwMeterCtrl->getFeatures()->getTriggerSources();
        for(int i = 0; i < sources->getCount(); i++){
                if(trgSrc == sources->getItem(i)){
                        cbxTrgSource->ItemIndex = i;
                        break;
                }
        }

        TriggerAction trgAction = bfdPwMeterCtrl->getTrigger()->getAction();
        Array<TriggerAction>* action = bfdPwMeterCtrl->getFeatures()->getTriggerActions();
        for(int i = 0; i < action->getCount(); i++){
                if(trgAction == action->getItem(i)){
                cbxTrgAction->ItemIndex = i;
                break;
                }
        }

        ActiveSignal trgEdge = bfdPwMeterCtrl->getTrigger()->getEdge();
        int index = -1;
        trgEdge == RisingEdge ? (index = 0) : (index = 1);
        cbxTrgEdge->ItemIndex = index;

        txtTrgLevel->Text = bfdPwMeterCtrl->getTrigger()->getLevel();

        bfdPwMeterCtrl->getChannelMap(channelCountMax, configure.channelEnable);
        for(int i = 0; i < channelCountMax; i++){
                if(configure.channelEnable[i]){
                        chkListBox->Checked[i] = true;
                }else{
                        chkListBox->Checked[i] = false;
                }
        }
        bfdPwMeterCtrl->Dispose();
}

