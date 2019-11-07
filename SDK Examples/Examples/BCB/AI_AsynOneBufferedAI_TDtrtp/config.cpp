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
void __fastcall TConfigForm::btnCancelClick(TObject *Sender)
{
        this->Close();        
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
        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = wfAiCtrl->getSupportedDevices();
        DeviceInformation devInfo;

        if (supportedDevice->getCount() == 0) {
                MessageBox(this->WindowHandle, "No device to support the currently demonstrated function!", "Warning Information", MB_ICONWARNING);
                exit(0);
        } else {
                for (int i = 0; i < supportedDevice->getCount(); i++) {
                    DeviceTreeNode const & node = supportedDevice->getItem(i);
                    devInfo.DeviceNumber = node.DeviceNumber;
                    wfAiCtrl->setSelectedDevice(devInfo);
                    if(wfAiCtrl->getFeatures()->getTriggerCount() > 1)
                    {
                      cmbDevice->AddItem(supportedDevice->getItem(i).Description, this);
                    }
               }
                    cmbDevice->ItemIndex = 0;
        }
        configure.profilePath = L"";
        wfAiCtrl->Dispose();
        supportedDevice->Dispose();

        cmbDeviceChange(this);
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

        if (txtSectionLength->Text.Trim() == "" || txtClockRate->Text.Trim() == "") {
                MessageBox(this->WindowHandle, "Please enter a number!", "Warning Information", MB_ICONWARNING);
                txtSectionLength->Text = 1024;
                txtClockRate->Text = 1000;
                return;
        }

        if (txtClockRate->Text.ToInt() <= 0 || txtClockRate->Text.ToInt() > 500000000) {
                txtClockRate->Text = 1000;
        }

        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = wfAiCtrl->getSupportedDevices();
        wchar_t deviceDescription [64];
        cmbDevice->Text.WideChar(deviceDescription, 64);
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = wfAiCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" +  Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        Array<ValueRange>* valueRanges = wfAiCtrl->getFeatures()->getValueRanges();

        configure.deviceName = deviceDescription;
        configure.channelStart = cmbChannelStart->ItemIndex;
        configure.channelCount = cmbChannelCount->ItemIndex + 1;
        configure.valueRange = valueRanges->getItem(cmbValueRange->ItemIndex);
        configure.sectionLength = txtSectionLength->Text.ToInt();
        configure.clockRate = txtClockRate->Text.ToDouble();

        if (isTriggerSupported) {
                AnsiString source = cmbTriggerSource->Text;
                if (txtDelayCount->Text.ToInt() > txtSectionLength->Text.ToInt()) {
                        MessageBox(this->WindowHandle, "Error : 'trigger delayCount' must be smaller than 'samples'!", "Error", MB_ICONERROR);
                        txtDelayCount->Text = String(500);
                        return;
                }

                if (txtTriggerLevel->Text.ToDouble() > 10 || txtTriggerLevel->Text.ToDouble() < -10) {
                        MessageBox(this->WindowHandle, "'trigger level' is out of range \"-10v ~ 10v \"", "Error", MB_ICONERROR);
                        txtTriggerLevel->Text = String(3);
                        return;
                }

                configure.triggerAction = DelayToStart;
                Array<SignalDrop>*  sources = wfAiCtrl->getFeatures()->getTriggerSources();
                configure.triggerSource = sources->getItem(cmbTriggerSource->ItemIndex);
                if (cmbTriggerEdge->ItemIndex == 0) {
                        configure.triggerEdge = RisingEdge;
                } else {
                        configure.triggerEdge = FallingEdge;
                }
                configure.delayCount = txtDelayCount->Text.ToInt();
                configure.triggerLevel = txtTriggerLevel->Text.ToDouble();
        }

       if (isTrigger1Supported) {
                AnsiString source1 = cmbTrigger1Source->Text;
                if (txtDelayCount1->Text.ToInt() > txtSectionLength->Text.ToInt()){
                        MessageBox(this->WindowHandle, "Error : 'trigger delayCount' must be smaller than 'samples'!", "Error", MB_ICONERROR);
                        txtDelayCount->Text = String(500);
                        return;
                }

                if (txtTrigger1Level->Text.ToInt() > 10 || txtTrigger1Level->Text.ToInt() < -10) {
                        MessageBox(this->WindowHandle, "'trigger level' is out of range \"-10v ~ 10v \"", "Error", MB_ICONERROR);
                        txtTriggerLevel->Text = String(3);
                        return;
                }

                configure.trigger1Action = DelayToStop;
                Array<SignalDrop>*  sources1 = wfAiCtrl->getFeatures()->getTrigger1Sources();
                configure.trigger1Source = sources1->getItem(cmbTriggerSource->ItemIndex);

                if (cmbTrigger1Edge->ItemIndex == 0) {
                        configure.trigger1Edge = RisingEdge;
                } else {
                        configure.trigger1Edge = FallingEdge;
                }
                configure.delayCount1 = txtDelayCount1->Text.ToInt();
                configure.trigger1Level = txtTrigger1Level->Text.ToDouble();
        }
        WideString wstr = txtProfilePath->Text;
        configure.profilePath = wstr.c_bstr();

        MainForm->SetConfigureParameter(GetConfigureParameter());
        MainForm->Initialization();

        this->isBtnOkClicked = true;
        ModalResult = mrOk;

        wfAiCtrl->Dispose();
        supportedDevice->Dispose();
}
//---------------------------------------------------------------------------

void TConfigForm::CheckError(ErrorCode errorCode) {
        if (errorCode != Success) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//----------------------------------------------------------------------------

void __fastcall TConfigForm::cmbDeviceChange(TObject *Sender)
{

        cmbChannelStart->Clear();
        cmbChannelCount->Clear();
        cmbValueRange->Clear();
        cmbTriggerSource->Clear();
        cmbTriggerEdge->Clear();
        cmbTrigger1Source->Clear();
        cmbTrigger1Edge->Clear();

        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = wfAiCtrl->getSupportedDevices();

        wchar_t deviceDescription[64];
        cmbDevice->Text.WideChar(deviceDescription, 64);

        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = wfAiCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" +  Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        int logicChannelCount = wfAiCtrl->getChannelCount();
        int channelCount = (logicChannelCount < 16) ? logicChannelCount : 16;
        int chanCountMax = wfAiCtrl->getFeatures()->getChannelCountMax();

        for (int i = 0; i < chanCountMax; i++) {
                cmbChannelStart->AddItem(i, this);
        }

        for (int j = 1; j <= channelCount; j++) {
                cmbChannelCount->AddItem(j, this);
        }

        //Set value range combo box
        Array<ValueRange>* valueRanges = wfAiCtrl->getFeatures()->getValueRanges();
        wchar_t vrgDescription[128];
        MathInterval ranges;
        ValueUnit valueUnit;
        for(int j = 0; j < valueRanges->getCount(); j++)
        {
                ret = AdxGetValueRangeInformation(valueRanges->getItem(j) ,sizeof(vrgDescription), vrgDescription, &ranges, &valueUnit);
                CheckError(ret);

                //we filter the Celsius degree for the buffered AI which do not support this function.
                if (valueUnit == CelsiusUnit) {
                        continue;
                }

                cmbValueRange->AddItem(vrgDescription, this);
        }

        AiFeatures* features = wfAiCtrl->getFeatures();
        
        isTriggerSupported = (features->getTriggerCount() > 0)? true : false;
        cmbTriggerSource->Enabled = isTriggerSupported;
        cmbTriggerEdge->Enabled = isTriggerSupported;
        txtDelayCount->Enabled = isTriggerSupported;
        txtTriggerLevel->Enabled = isTriggerSupported;
        if (isTriggerSupported) {
                // Initialize trigger parameter: trigger source.
                wchar_t signalDes[128];
                SignalPosition sigPos;
                ErrorCode ret = Success;
                Array<SignalDrop>*  sources = features->getTriggerSources();
                if (sources != NULL) {
                        for (int i = 0; i < sources->getCount(); i++) {
                                ret = AdxGetSignalConnectionInformation(sources->getItem(i),sizeof(signalDes) ,signalDes, &sigPos);
                                CheckError(ret);

                                cmbTriggerSource->AddItem(signalDes, this);
                        }
                }

                // Initialize trigger parameter: trigger edge.
                cmbTriggerEdge->AddItem("RisingEdge", this);
                cmbTriggerEdge->AddItem("FallingEdge", this);

                cmbTriggerSource->ItemIndex = 0;
                cmbTriggerEdge->ItemIndex = 0;
        }

        isTrigger1Supported = (wfAiCtrl->getFeatures()->getTriggerCount() > 1)? true : false;
        cmbTrigger1Source->Enabled = isTrigger1Supported;
        cmbTrigger1Edge->Enabled = isTrigger1Supported;
        txtDelayCount1->Enabled = isTrigger1Supported;
        txtTrigger1Level->Enabled = isTrigger1Supported;
        if (isTrigger1Supported) {
                // Initialize trigger1 parameter: trigger source.
                wchar_t signalDes[128];
                SignalPosition sigPos;
                ErrorCode ret = Success;
                Array<SignalDrop>*  sources = features->getTrigger1Sources();
                if (sources != NULL) {
                        for (int i = 0; i < sources->getCount(); i++) {
                                ret = AdxGetSignalConnectionInformation(sources->getItem(i),sizeof(signalDes) ,signalDes, &sigPos);
                                CheckError(ret);

                                cmbTrigger1Source->AddItem(signalDes, this);
                        }
                }

                // Initialize trigger1 parameter: trigger edge.
                cmbTrigger1Edge->AddItem("RisingEdge", this);
                cmbTrigger1Edge->AddItem("FallingEdge", this);

                cmbTrigger1Source->ItemIndex = 0;
                cmbTrigger1Edge->ItemIndex = 0;
        }

        //Set default parameters
        cmbChannelStart->ItemIndex = 0;
        cmbChannelCount->ItemIndex = 1;
        cmbValueRange->ItemIndex = 0;

        wfAiCtrl->Dispose();
        supportedDevice->Dispose();

        cmbTriggerSourceChange(this);
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::cmbTriggerSourceChange(TObject *Sender)
{
        AnsiString source = cmbTriggerSource->Text;
        if (source == "None" || !isTriggerSupported) {
                cmbTriggerEdge->Enabled = false;
                txtDelayCount->Enabled = false;
                txtTriggerLevel->Enabled = false;
        } else {
                cmbTriggerEdge->Enabled = true;
                txtDelayCount->Enabled = true;

                int isExtDig = source.Pos("External Digital");
                if (isExtDig) {
                        txtTriggerLevel->Enabled = false;
                } else {
                        txtTriggerLevel->Enabled = true;
                }
        }

         AnsiString source1 = cmbTrigger1Source->Text;
        if (source1 == "None" || !isTrigger1Supported) {
                cmbTrigger1Edge->Enabled = false;
                txtDelayCount1->Enabled = false;
                txtTrigger1Level->Enabled = false;
        } else {
                cmbTrigger1Edge->Enabled = true;
                txtDelayCount1->Enabled = true;

                int isExtDig = source1.Pos("External Digital");
                if (isExtDig) {
                        txtTrigger1Level->Enabled = false;
                } else {
                        txtTrigger1Level->Enabled = true;
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TConfigForm::btnBrowseClick(TObject *Sender)
{
        TOpenDialog *test = new TOpenDialog(this);

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

void  TConfigForm::RefreshConfigureParameter()
{
        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        WideString wstr = cmbDevice->Text;
        wchar_t *deviceDescription = wstr.c_bstr();                
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = wfAiCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        
        txtSectionLength->Text = wfAiCtrl->getRecord()->getSectionLength();
        txtClockRate->Text = wfAiCtrl->getConversion()->getClockRate();
}
