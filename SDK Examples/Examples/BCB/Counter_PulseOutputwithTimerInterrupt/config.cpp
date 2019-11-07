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
        TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = timerPulseCtrl->getSupportedDevices();

        if (supportedDevice->getCount() == 0) {
                MessageBox(this->WindowHandle, "No device to support the currently demonstrated function!", "Warning Information", MB_ICONWARNING);
                exit(0);
        } else {
                for (int i = 0; i < supportedDevice->getCount(); i++) {
                cmbDevice->AddItem(supportedDevice->getItem(i).Description, this);
        }
                cmbDevice->ItemIndex = 0;
        }

        timerPulseCtrl->Dispose();
        supportedDevice->Dispose();
        
        this->cmbDeviceChange(this);
}

void __fastcall TConfigForm::cmbDeviceChange(TObject *Sender)
{
        cmbCounterChannel->Clear();
        cmbModuleIndex->Clear();

        TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = timerPulseCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        DeviceInformation devInfo(deviceDescription);

        // Set ModulesIndex combo box
        DeviceTreeNode devNode = supportedDevice->getItem(cmbDevice->ItemIndex);
        int index = 0;
        for (int j = 0; j < 8; j++) {
                index = devNode.ModulesIndex[j];
                if (index != -1) {
                        this->cmbModuleIndex->AddItem(index, this);
                } else {
                        break;
                }
        }
        cmbModuleIndex->ItemIndex = 0;

        ErrorCode ret = Success;
        devInfo.ModuleIndex = cmbModuleIndex->ItemIndex;
        ret = timerPulseCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        // Set channel start combo box
        int channelCountMax = timerPulseCtrl->getFeatures()->getChannelCountMax();
        Array<CounterCapability> * counterCap;
        int itemCount;
        for (int i = 0; i < channelCountMax; i++) {
                itemCount = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
                counterCap = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i);
                for (int j = 0; j < itemCount; j++) {
                        if (TimerPulse == counterCap->getItem(j)) {
                                cmbCounterChannel->AddItem(i, this);
                        }
                }
        }
        cmbCounterChannel->ItemIndex = 0;

        timerPulseCtrl->Dispose();
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

        TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = timerPulseCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = timerPulseCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }
        WideString wstr = txtProfilePath->Text;
        configure.profilePath = wstr.c_bstr();

        configure.deviceName = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        configure.channel = cmbCounterChannel->Text.ToInt();
        configure.moduleIndex = cmbModuleIndex->Text.ToInt();


        MainForm->SetConfigureParameter(GetConfigureParameter());
        MainForm->Initialization();

        this->isBtnOkClicked = true;
        ModalResult = mrOk;

        timerPulseCtrl->Dispose();
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

void __fastcall TConfigForm::cmbModuleIndexChange(TObject *Sender)
{
        cmbCounterChannel->Clear();

        TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = timerPulseCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        devInfo.ModuleIndex = cmbModuleIndex->ItemIndex;
        ret = timerPulseCtrl->setSelectedDevice(devInfo);
        CheckError(ret);

        // Set channel start combo box
        int channelCountMax = timerPulseCtrl->getFeatures()->getChannelCountMax();
        Array<CounterCapability> * counterCap;
        int itemCount;
        for (int i = 0; i < channelCountMax; i++) {
                itemCount = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
                counterCap = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i);
                for (int j = 0; j < itemCount; j++) {
                        if (TimerPulse == counterCap->getItem(j)) {
                                cmbCounterChannel->AddItem(i, this);
                        }
                }
        }
        cmbCounterChannel->ItemIndex = 0;
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

