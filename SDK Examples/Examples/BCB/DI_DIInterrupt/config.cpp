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

        m_stateImage[0] = LoadJPEGFromResource(0, "buttonUp");
        m_stateImage[1] = LoadJPEGFromResource(0, "buttonDown");
        m_stateImage[2] = LoadJPEGFromResource(0, "buttonDisabled");

        Initialization();
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::btnCancelClick(TObject *Sender)
{
        this ->Close();        
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
        InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = instantDiCtrl->getSupportedDevices();

        if (supportedDevice->getCount() == 0) {
                MessageBox(this->WindowHandle, "No device to support the currently demonstrated function!", "Warning Information", MB_ICONWARNING);
                exit(0);
        } else {
                deviceIndex = new int[supportedDevice->getCount()];
                int j = 0;

                for (int i = 0; i < supportedDevice->getCount(); i++) {
                        DeviceTreeNode node = supportedDevice->getItem(i);
                        DeviceInformation devInfo(node.Description, ModeRead);
                        instantDiCtrl->setSelectedDevice(devInfo);

                        Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
                        if (interruptChans == NULL) {
                                continue;
                        }

                        cmbDevice->AddItem(supportedDevice->getItem(i).Description, this);
                        deviceIndex[j++] = i;
                }
                cmbDevice->ItemIndex = 0;
        }
        configure.profilePath = L"";
        instantDiCtrl->Dispose();
        supportedDevice->Dispose();

        this->cmbDeviceChange(this);
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

        bool selectedChannel = false;
        for (int i = 0; i < enablePortCount; i++) {
                if (m_portPanel[i]->State != 0) {
                        selectedChannel = true;
                        break;
                }
        }

        if (!selectedChannel) {
                MessageBox(this->WindowHandle, "Please enable one bit at lest!", "Error", MB_ICONERROR);
                return;
        }

        InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = instantDiCtrl->getSupportedDevices();

        configure.selectedPortIndex = new int[enablePortCount];
        configure.enableChannel = new int[enablePortCount];
        configure.deviceName = supportedDevice->getItem(deviceIndex[cmbDevice->ItemIndex]).Description;
        for (int i = 0; i < enablePortCount; i++) {
                configure.selectedPortIndex[i] = m_portPanel[i]->Port;
                configure.enableChannel[i] = m_portPanel[i]->State;
        }
        WideString wstr = txtProfilePath->Text;
        configure.profilePath = wstr.c_bstr();

        MainForm->SetConfigureParameter(GetConfigureParameter());
        MainForm->Initialization();

        this->isBtnOkClicked = true;
        ModalResult = mrOk;

        instantDiCtrl->Dispose();
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
        if (m_portPanel != NULL) {
                for (int i = 0; i < enablePortCount; i++) {
                        ScrollBox1->RemoveControl(m_portPanel[i]);
                        m_portPanel[i] = NULL;
                }
                m_portPanel = NULL;
        }

        InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = instantDiCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(deviceIndex[cmbDevice->ItemIndex]).Description;
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = instantDiCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
        int intPortCount = interruptChans->getCount();
        byte* ports = new byte[instantDiCtrl->getFeatures()->getPortCount()];
        for (int i = 0; i < instantDiCtrl->getFeatures()->getPortCount(); i++) {
                ports[i] = 0;
        }

        for (int i = 0; i < intPortCount; i++) {
                int portIndex = interruptChans->getItem(i).getChannel() / 8;
                int chIndex = interruptChans->getItem(i).getChannel() % 8;
                ports[portIndex] |= 0x1 << chIndex;
        }

        enablePortCount = 0;
        for (int i = 0; i < instantDiCtrl->getFeatures()->getPortCount(); i++) {
                if (ports[i] != 0){
                        enablePortCount++;
                }
        }

        int* portIndexes = new int[enablePortCount];
        int j = 0;
        for (int i = 0; i < instantDiCtrl->getFeatures()->getPortCount(); i++) {
                if (ports[i] != 0) {
                        portIndexes[j++] = i;
                }
        }

        m_portPanel = new TPortPanel*[enablePortCount];

        for (int i = 0; i < enablePortCount; i++) {
                m_portPanel[i] = new TPortPanel(ScrollBox1);
                m_portPanel[i]->SetBounds(20, 10 + i * 38, 280, 38);
                m_portPanel[i]->Initialize(portIndexes[i], m_stateImage, 3);
                m_portPanel[i]->Editable = true;
                m_portPanel[i]->Mask = ports[portIndexes[i]];
                m_portPanel[i]->State = 1;
                m_portPanel[i]->ShowHexEditor(false);
                ScrollBox1->InsertControl(m_portPanel[i]);
        }

        instantDiCtrl->Dispose();
        supportedDevice->Dispose();
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

