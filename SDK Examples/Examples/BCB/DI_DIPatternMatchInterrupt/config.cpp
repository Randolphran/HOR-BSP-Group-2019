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
        images[0][0] = Image00;
        images[0][1] = Image01;
        images[0][2] = Image02;
        images[0][3] = Image03;
        images[0][4] = Image04;
        images[0][5] = Image05;
        images[0][6] = Image06;
        images[0][7] = Image07;

        images[1][0] = Image10;
        images[1][1] = Image11;
        images[1][2] = Image12;
        images[1][3] = Image13;
        images[1][4] = Image14;
        images[1][5] = Image15;
        images[1][6] = Image16;
        images[1][7] = Image17;

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

                        Array<DiPmintPort>* diPmintPorts = instantDiCtrl->getDiPmintPorts();
                        if (diPmintPorts == NULL) {
                                continue;
                        }

                        cmbDevice->AddItem(supportedDevice->getItem(i).Description, this);
                        deviceIndex[j++] = i;
                }
                cmbDevice->ItemIndex = 0;
        }

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

        if (this->enableChannels == 0) {
                ShowMessage("Please enable one bit at lest!");
                return;
        }

        InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = instantDiCtrl->getSupportedDevices();

        configure.deviceName = supportedDevice->getItem(deviceIndex[cmbDevice->ItemIndex]).Description;
        configure.selectedPort = cmbDIport->Text.ToInt();
        configure.enabledChannels = this->enableChannels;
        configure.pmValue= this->pmValue;

        DeviceInformation devInfo(configure.deviceName);
        ErrorCode ret = Success;
        ret = instantDiCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
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
        cmbDIport->Clear();

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

        Array<DiPmintPort>* diPmintPorts = instantDiCtrl->getDiPmintPorts();
        int PmPortCount = diPmintPorts->getCount();
        int portNumber = 0;
        for (int i = 0; i < PmPortCount; i++) {
                portNumber = diPmintPorts->getItem(i).getPort();
                this->cmbDIport->AddItem(portNumber, this);
        }

        this->cmbDIport->ItemIndex = 0;

        instantDiCtrl->Dispose();
        supportedDevice->Dispose();

        InitializePortState();
}
//---------------------------------------------------------------------------

void TConfigForm::InitializePortState() {
        enableChannels = 0;
        pmValue = 0xFF;
        Graphics::TBitmap* bitmap;

        enableChan->Text = Format("%2X",ARRAYOFCONST((enableChannels)));
        edtpmValue->Text = Format("%2X",ARRAYOFCONST((pmValue)));

        for (int i = 0; i < 8; i++) {
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(0, bitmap);
                images[0][i]->Picture->Bitmap = bitmap;
                images[0][i]->Tag = 0;
        }

        for (int i = 0; i < 8; i++) {
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(1, bitmap);
                images[1][i]->Picture->Bitmap = bitmap;
                images[1][i]->Tag = 1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::Image0Click(TObject *Sender)
{
        int i = 0, index, data = 1, bitValue;
        ErrorCode ret = Success;
        Graphics::TBitmap* bitmap;

        TImage *image = (TImage*)Sender;
        bitValue = image->Tag;
        index = image->HelpKeyword.ToInt();

        while (i < index) {
                data = data * 2;
                i = i + 1;
        }

        if (bitValue == 0) {
                enableChannels = enableChannels + data;
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(1, bitmap);
                image->Picture->Bitmap = bitmap;
                image->Tag = 1;
        } else {
                enableChannels = enableChannels - data;
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(0, bitmap);
                image->Picture->Bitmap = bitmap;
                image->Tag = 0;
        }

        enableChan->Text = Format("%2X",ARRAYOFCONST((enableChannels)));
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::Image1Click(TObject *Sender)
{
        int i = 0, index, data = 1, bitValue;
        ErrorCode ret = Success;
        Graphics::TBitmap* bitmap;

        TImage *image = (TImage*)Sender;
        bitValue = image->Tag;
        index = image->HelpKeyword.ToInt();

        while (i < index) {
                data = data * 2;
                i = i + 1;
        }

        if (bitValue == 0) {
                pmValue = pmValue + data;
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(1, bitmap);
                image->Picture->Bitmap = bitmap;
                image->Tag = 1;
        } else {
                pmValue = pmValue - data;
                bitmap = new Graphics::TBitmap();
                ImageList1->GetBitmap(0, bitmap);
                image->Picture->Bitmap = bitmap;
                image->Tag = 0;
        }

        edtpmValue->Text = Format("%2X",ARRAYOFCONST((pmValue)));
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::cmbDIportChange(TObject *Sender)
{
        InitializePortState();
}

//----------------------------------------------------------------------------
void __fastcall TConfigForm::butBrowseClick(TObject *Sender)
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

