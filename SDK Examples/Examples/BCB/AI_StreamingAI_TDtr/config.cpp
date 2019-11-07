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

        if (supportedDevice->getCount() == 0) {
                MessageBox(this->WindowHandle, "No device to support the currently demonstrated function!", "Warning Information", MB_ICONWARNING);
                exit(0);
        } else {
                for (int i = 0; i < supportedDevice->getCount(); i++) {
                cmbDevice->AddItem(supportedDevice->getItem(i).Description, this);
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

        if (txtClockRate->Text.Trim() == "") {
                MessageBox(this->WindowHandle, "Please enter a number!", "Warning Information", MB_ICONWARNING);
                txtClockRate->Text = 1000;
                return;
        } 

        if (txtClockRate->Text.ToInt() <= 0 || txtClockRate->Text.ToInt() > 500000000) {
                txtClockRate->Text = 1000;
        }

        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        WideString wstring = cmbDevice->Text;
        wchar_t *deviceDescription = wstring.c_bstr();
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = wfAiCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }
        
        Array<ValueRange>* valueRanges = wfAiCtrl->getFeatures()->getValueRanges();

        configure.deviceName = deviceDescription;
        configure.channelStart = cmbChannelStart->ItemIndex;
        configure.channelCount = cmbChannelCount->ItemIndex + 1;
        configure.valueRange = valueRanges->getItem(cmbValueRange->ItemIndex);
        configure.clockRate = txtClockRate->Text.ToDouble();
        configure.sectionLength = txtSectionLength->Text.ToInt();

        if (isTriggerSupported) {
                AnsiString source = cmbTriggerSource->Text;
                if (txtTriggerLevel->Text.ToInt() > 10 || txtTriggerLevel->Text.ToInt() < -10) {
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
        WideString wstr = txtProfilePath->Text;
        configure.profilePath = wstr.c_bstr();

        MainForm->SetConfigureParameter(GetConfigureParameter());
        MainForm->Initialization();

        this->isBtnOkClicked = true;
        ModalResult = mrOk;

        wfAiCtrl->Dispose();
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

        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        WideString wstr = cmbDevice->Text;
        wchar_t *deviceDescription = wstr.c_bstr(); 
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = wfAiCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
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
        isTriggerSupported = (features->getTriggerCount() > 0 )? true : false;
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

        //Set default parameters
        cmbChannelStart->ItemIndex = 0;
        cmbChannelCount->ItemIndex = 1;
        cmbValueRange->ItemIndex = 0;

        wfAiCtrl->Dispose();
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