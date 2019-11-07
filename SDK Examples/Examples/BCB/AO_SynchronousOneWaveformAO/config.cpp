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
        BufferedAoCtrl * bfdAoCtrl = BufferedAoCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = bfdAoCtrl->getSupportedDevices();

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
        bfdAoCtrl->Dispose();
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

        if (txtClockRate->Text.Trim() == "" || txtPointCount->Text.Trim() == "") {
                MessageBox(this->WindowHandle, "Please enter a number!", "Warning Information", MB_ICONWARNING);
                txtClockRate->Text = 1000;
                txtPointCount->Text = 400;
                return;
        }

        if (txtClockRate->Text.ToInt() <= 0 || txtClockRate->Text.ToInt() > 30000000) {
                txtClockRate->Text = 1000;
        }

        if (txtPointCount->Text.ToInt() < 1 ||txtPointCount->Text.ToInt() > 10000000) {
                txtPointCount->Text = 400;
        }

        BufferedAoCtrl * bfdAoCtrl = BufferedAoCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = bfdAoCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = bfdAoCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        Array<ValueRange>* valueRanges = bfdAoCtrl->getFeatures()->getValueRanges();

        configure.deviceName = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        configure.channelStart = cmbChannelStart->ItemIndex;
        configure.channelCount = cmbChannelCount->ItemIndex + 1;
        configure.valueRange = valueRanges->getItem(cmbValueRange->ItemIndex);
        configure.pointCountPerWave = txtPointCount->Text.ToInt();
        configure.clockRate = txtClockRate->Text.ToDouble();

        WideString wstr = txtProfilePath->Text;
        configure.profilePath = wstr.c_bstr();
        
        MainForm->SetConfigureParameter(GetConfigureParameter());
        MainForm->Initialization();

        this->isBtnOkClicked = true;
        ModalResult = mrOk;

        bfdAoCtrl->Dispose();
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

        BufferedAoCtrl * bfdAoCtrl = BufferedAoCtrl::Create();
        Array<DeviceTreeNode> *supportedDevice = bfdAoCtrl->getSupportedDevices();
        wchar_t *deviceDescription = supportedDevice->getItem(cmbDevice->ItemIndex).Description;
        DeviceInformation devInfo(deviceDescription);
        ErrorCode ret = Success;
        ret = bfdAoCtrl->setSelectedDevice(devInfo);
        if (ret != Success) {
                int err = ret;
                AnsiString str = "Error:the error code is: 0x" + Format("%X",ARRAYOFCONST((err))) + "\n\tThe " + cmbDevice->Text + " is busy or not exit in computer now.\n\tSelect other device please!";
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
                return;
        }

        int logicChannelCount = bfdAoCtrl->getChannelCount();
        int channelCount = (logicChannelCount < 2) ? logicChannelCount : 2;
        int chanCountMax = bfdAoCtrl->getFeatures()->getChannelCountMax();

         for (int i = 0; i < chanCountMax; i++) {
                cmbChannelStart->AddItem(i, this);
         }

        for (int j = 1; j <= channelCount; j++) {
                cmbChannelCount->AddItem(j, this);
         }

        //Set value range combo box
        Array<ValueRange>* valueRanges = bfdAoCtrl->getFeatures()->getValueRanges();
        wchar_t vrgDescription[128];
        MathInterval ranges;
        ValueUnit valueUnit;
        for(int j = 0; j < valueRanges->getCount(); j++)
        {
                if (valueRanges->getItem(j) < UserCustomizedVrgStart) {
                        ret = AdxGetValueRangeInformation(valueRanges->getItem(j) ,sizeof(vrgDescription), vrgDescription, &ranges, &valueUnit);
                        CheckError(ret);
                        cmbValueRange->AddItem(vrgDescription, this);
                }
        }

        //Set default parameters
        cmbChannelStart->ItemIndex = 0;
        cmbChannelCount->ItemIndex = 1;
        cmbValueRange->ItemIndex = 0;

        bfdAoCtrl->Dispose();
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

