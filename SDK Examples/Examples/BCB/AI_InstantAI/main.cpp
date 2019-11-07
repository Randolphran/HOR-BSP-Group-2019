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
        instantAiCtrl = InstantAiCtrl::Create();

        this->DoubleBuffered = true;

        //initialize a graph with a paint box control to draw Ai data.
        m_graph = new TSimpleGraph(DataView);

        chanDataList->SmallImages = new TImageList(this);
        chanDataList->SmallImages->Height = 22;
        for (int i = 0; i < 2; i++) {
                TListItem* item = chanDataList->Items->Add();
                for (int j = 0; j < 9; j++) {
                        item->SubItems->Add(" ");
                }
        }
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Instant AI - Run("  + deviceName + ")";
        this->Caption = caption;

        BtnStart->Enabled = true;
        BtnPause->Enabled = false;
        BtnStop->Enabled = false;
        BtnConfig->Enabled = true;

        //initialize a timer which drive the data acquisition.
        Timer1->Interval = timerTrackBar->Position;

        timerIntvlEditor->Text = timerTrackBar->Position;
        
        ConfigureDevice();
        InitializeGraph();
        InitListView();
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = instantAiCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = instantAiCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        // set value range for every channel.
        for (int i = 0; i < instantAiCtrl->getChannels()->getCount(); i++) {
            ret = instantAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
            CheckError(ret);
        }
}
//---------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this->WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void TMainForm::InitializeGraph() {
        ValueUnit unit;
        MathInterval vrgRange;
        AnsiString ustr;
        AnsiString units[9] = {"kV", "V", "mV", "uV", "kA", "A", "mA", "uA", "C"};

        //get the value range of each channel.
        ErrorCode ret = AdxGetValueRangeInformation(configure.valueRange, 0, NULL, &vrgRange, &unit);
	CheckError(ret);

        int index = (int)unit;
        if(index == 2 || index == 6)
        {
            index -= 1;
        }
        ustr = units[index];

        if (Milliampere == unit || Millivolt == unit) {
                vrgRange.Max /= 1000;
                vrgRange.Min /= 1000;
        }

        m_graph->XCordTimeDiv = 1000;
        m_graph->YCordMax = vrgRange.Max;
        m_graph->YCordMin = vrgRange.Min;

        this->yTLabel->Caption = String(vrgRange.Max) + ustr;
        this->yMLabel->Caption = String((vrgRange.Max + vrgRange.Min) / 2) + ustr;
        this->yBLabel->Caption = String(vrgRange.Min) + ustr;

        m_graph->Clear();
}
//---------------------------------------------------------------------------

void TMainForm::InitListView() {
        TListItems* items = chanDataList->Items;
        for (int i = 0; i < 16; i++) {
                if ( i < configure.channelCount) {
                        items->Item[i / 8]->SubItems->Strings[i % 8] = Format("%.4f",ARRAYOFCONST((0.0)));
                } else {
                        items->Item[i / 8]->SubItems->Strings[i % 8] = " ";        
                }
        }
}
//----------------------------------------------------------------------------


void __fastcall TMainForm::chanDataListCustomDrawSubItem(
      TCustomListView *Sender, TListItem *Item, int SubItem,
      TCustomDrawState State, bool &DefaultDraw)
{
        TColor clr;

        int plot = Item->Index * 8 + SubItem - 1;

        if (plot < configure.channelCount) {
                clr = m_graph->GetPlotColor(plot);
        } else {
                clr = clWhite;
        }

        Sender->Canvas->Brush->Color = clr;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::timerTrackBarChange(TObject *Sender)
{
        Timer1->Interval = timerTrackBar->Position;
        timerIntvlEditor->Text = Timer1->Interval;
        m_graph->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
        double dataScaled[16];
        ErrorCode ret = Success;

        //read data.
        ret = instantAiCtrl->Read(configure.channelStart, configure.channelCount, dataScaled);
        if (ret != Success) {
                Timer1->Enabled = false;
                CheckError(ret);
        }

        //draw the data to the PaintBox
        m_graph->Chart(dataScaled, 15, configure.channelCount, 1, timerTrackBar->Position / 1000.0);

        TListItems* items = chanDataList->Items;
        for (int i = 0; i < configure.channelCount; i++) {
                items->Item[i / 8]->SubItems->Strings[i % 8] = Format("%.4f",ARRAYOFCONST((dataScaled[i])));
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnStartClick(TObject *Sender)
{
        Timer1->Enabled = true;
        BtnStart->Enabled = false;
        BtnPause->Enabled = true;
        BtnStop->Enabled = true;
        BtnConfig->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnPauseClick(TObject *Sender)
{
        Timer1->Enabled = false;
        BtnStart->Enabled = true;
        BtnPause->Enabled = false;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnStopClick(TObject *Sender)
{
        Timer1->Enabled = false;
        BtnStart->Enabled = true;
        BtnPause->Enabled = false;
        BtnStop->Enabled = false;
        BtnConfig->Enabled = true;

        m_graph->Clear();
        InitListView();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnConfigClick(TObject *Sender)
{
        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }
}
//---------------------------------------------------------------------------


