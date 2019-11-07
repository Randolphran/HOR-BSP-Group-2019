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
        instantDoCtrl = InstantDoCtrl::Create();
        m_portPanel = NULL;
        portPanelLength = 0;

        m_stateImage[0] = LoadJPEGFromResource(0, "buttonUp");
        m_stateImage[1] = LoadJPEGFromResource(0, "buttonDown");
        m_stateImage[2] = LoadJPEGFromResource(0, "buttonDisabled");
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Static DO - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();
        InitializePortPanel();
}
//--------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = instantDoCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = instantDoCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        portCount = instantDoCtrl->getPortCount();
}
//--------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
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

void TMainForm::InitializePortPanel() {
        //remove the old state panel
        if (m_portPanel != NULL) {
                for (int i = 0; i < portPanelLength; i++) {
                        ScrollBox1->RemoveControl(m_portPanel[i]);
                        m_portPanel[i] = NULL;
                }
                m_portPanel = NULL;
        }

        DioFeatures * features = instantDoCtrl->getFeatures();
        Array<uint8>* portMasks = features->getDoDataMask();
        byte *portStates = new byte[portCount];
        ErrorCode ret = Success;
        ret = instantDoCtrl->Read(0, portCount, portStates);
        CheckError(ret);

        m_portPanel = new TPortPanel*[portCount];
        portPanelLength = portCount;
        for (int i = 0; i < portCount; i++) {
                        m_portPanel[i] = new TPortPanel(ScrollBox1);
                        m_portPanel[i]->SetBounds(20, 10 + i * 38, 300, 38);
                        m_portPanel[i]->Initialize(i, m_stateImage, 3);
                        m_portPanel[i]->Editable = true;
                        m_portPanel[i]->Mask = portMasks->getItem(i);
                        m_portPanel[i]->State = portStates[i];
                        m_portPanel[i]->OnChange = PortChanged;
                        ScrollBox1->InsertControl(m_portPanel[i]);
        }
}
//----------------------------------------------------------------------------

void __fastcall TMainForm::PortChanged(TObject *Sender) {
        TPortPanel* panel = (TPortPanel*)Sender;
        ErrorCode ret = Success;
        byte stateForRead;
        byte stateForWrite;
        stateForWrite = panel->State;
        ret = instantDoCtrl->Write(panel->Port, 1, &stateForWrite);
        CheckError(ret);
        ret = instantDoCtrl->Read(panel->Port, 1, &stateForRead);
        CheckError(ret);
        panel->State = stateForRead;
}
//----------------------------------------------------------------------------

