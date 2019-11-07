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
        instantDiCtrl = InstantDiCtrl::Create();
        m_portPanel = NULL;
        portPanelLength = 0;

        m_stateImage[0] = LoadJPEGFromResource(0, "ledLow");
        m_stateImage[1] = LoadJPEGFromResource(0, "ledHigh");

        this->ScrollBox1->DoubleBuffered;
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Static DI - Run("  + deviceName + ")";
        this->Caption = caption;

        ConfigureDevice();
        InitializePortPanel();

        //enable the timer to read DI ports status
        Timer1->Enabled = true;
}
//----------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = instantDiCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = instantDiCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        portCount = instantDiCtrl->getPortCount();
}
//---------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//----------------------------------------------------------------------------

void __fastcall TMainForm::btnConfigClick(TObject *Sender)
{
        Timer1->Enabled = false;

        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
        //read DI data
        byte *portStates = new byte[portCount];
        ErrorCode ret = Success;
        ret = instantDiCtrl->Read(0, portCount, portStates);
        CheckError(ret);

        //update the UI
        for (int i = 0; i < portCount; i++) {
                m_portPanel[i]->State = portStates[i];
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

        m_portPanel = new TPortPanel*[portCount];
        portPanelLength = portCount;
        for (int i = 0; i < portCount; i++) {
                        m_portPanel[i] = new TPortPanel(ScrollBox1);
                        m_portPanel[i]->SetBounds(20, 10 + i * 38, 300, 38);
                        m_portPanel[i]->Initialize(i, m_stateImage, 3);
                        m_portPanel[i]->Editable = false;
                        ScrollBox1->InsertControl(m_portPanel[i]);
        }
}
//----------------------------------------------------------------------------


