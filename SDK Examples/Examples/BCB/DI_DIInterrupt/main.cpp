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
        instantDiCtrl->addInterruptHandler(OnDiSnapEvent, this);

        gif = new TGIFImage;
        gif-> LoadFromResourceName(0, "tambour");
        gif-> Animate = false;
        gifViewer-> Picture-> Graphic = gif;

        BtnStop->Enabled = false;
}
//---------------------------------------------------------------------------


void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "DI Interrupt - Run("  + deviceName + ")";
        this->Caption = caption;
        
        ConfigureDevice();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = instantDiCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = instantDiCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);
        
        eventDataList->Columns->Items[1]->Caption = "DI ports value (Port 0~" + String(instantDiCtrl->getPortCount() - 1) + ")";

        Array<DiintChannel>* interruptChans = instantDiCtrl->getDiintChannels();
        for (int i = 0; i < interruptChans->getCount(); i++)
                for (int j = 0; j < ConfigForm->enablePortCount; j++)
                        for (int k = 0; k < 8; k++) {
                                if (((configure.enableChannel[j] >> k) & 0x1) == 1 &&  interruptChans->getItem(i).getChannel() == configure.selectedPortIndex[j] * 8 + k) {
                                        interruptChans->getItem(i).setEnabled(true);
                                }
                        }
}
//----------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//-------------------------------------------------------------------------------
void BDAQCALL TMainForm::OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void * userParam)
{
        TMainForm * uParam = (TMainForm *) userParam;
        TListItem *item;
        String valueString = "";

        if (uParam->eventDataList->Items->Count == 10) {
                uParam->eventDataList->Items->Delete(0);
        }

        item = uParam->eventDataList->Items->Add();

        item->Caption = "         " + String(args->SrcNum);

        for (int i = 0; i < args->Length; i++) {
                valueString = valueString + Format("%2X",ARRAYOFCONST((args->PortData[i])));

                if (i < args->Length - 1) {
                        valueString = valueString + ", ";
                }
        }
        item->SubItems->Add(valueString);
}
//-------------------------------------------------------------------------------
void __fastcall TMainForm::BtnStartClick(TObject *Sender)
{
        ErrorCode ret = Success;
        this->eventDataList->Items->Clear();

        ret = instantDiCtrl->SnapStart();
        if (ret != Success) {
                CheckError(ret);
                exit(0);
        }

        TGraphic * graphic = gifViewer->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = true;

        this->BtnStart->Enabled = false;
        this->BtnStop->Enabled = true;
        this->btnConfig->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnStopClick(TObject *Sender)
{
        TGraphic * graphic = gifViewer->Picture->Graphic;
        TGIFImage * gifTemp = (TGIFImage *)graphic;
        gifTemp->Animate = false;

        ErrorCode ret = Success;
        ret = instantDiCtrl->SnapStop();
        if (ret != Success) {
                CheckError(ret);
                exit(0);
        }

        this->BtnStart->Enabled = true;
        this->BtnStop->Enabled = false;
        this->btnConfig->Enabled = true;
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

