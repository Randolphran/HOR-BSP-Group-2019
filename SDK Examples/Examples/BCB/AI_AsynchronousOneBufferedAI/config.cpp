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
        WideString wideDeviceDescription = cmbDevice->Text;
        wchar_t *deviceDescription = wideDeviceDescription.c_bstr();
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

        WaveformAiCtrl * wfAiCtrl = WaveformAiCtrl::Create();
        WideString wstr = cmbDevice->Text;
        wchar_t *deviceDescription = wstr.c_bstr();
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

        //Set default parameters
        cmbChannelStart->ItemIndex = 0;
        cmbChannelCount->ItemIndex = 1;
        cmbValueRange->ItemIndex = 0;

        wfAiCtrl->Dispose();
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
