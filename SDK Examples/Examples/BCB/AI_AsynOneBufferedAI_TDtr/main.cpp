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
        wfAiCtrl = WaveformAiCtrl::Create();
        dataScaled = NULL;
        wfAiCtrl->addStoppedHandler(OnStoppedEvent, this);
        this->DoubleBuffered = true;

        //initialize a graph with a paint box control to draw Ai data.
        m_graph = new TSimpleGraph(DataView);

        chanDataList->SmallImages = new TImageList(this);
        chanDataList->SmallImages->Height = 20;
        for (int i = 0; i < 2; i++) {
                TListItem* item = chanDataList->Items->Add();
                for (int j = 0; j < 9; j++) {
                        item->SubItems->Add(" ");
                }
        }

        shiftTrackBar->Enabled = false;
        divTrackBar->Enabled = false;
}
//---------------------------------------------------------------------------

void TMainForm::Initialization() {
        //set the title of the form.
        AnsiString deviceName = configure.deviceName;
        AnsiString caption = "Asynchronous One Buffered AI with Trigger Delay to Start - Run("  + deviceName + ")";
        this->Caption = caption;

        if (dataScaled != NULL) {
                delete[] dataScaled;
                dataScaled = NULL;
        }
        
        ConfigureDevice();
        InitializeGraph();
        InitListView();

        ErrorCode ret = Success;
        ret = wfAiCtrl->Prepare();
        if (ret != Success) {
                CheckError(ret);
                exit(0);        
        }

        //create the array of dataScaled
        int channelCount = configure.channelCount;
        int sectionLength = configure.sectionLength;
        int sectionCount = 1;
        dataCount = channelCount * sectionLength * sectionCount;
        dataScaled = new double[dataCount];

        shiftTrackBar->Enabled = false;
        divTrackBar->Enabled = false;
}
//---------------------------------------------------------------------------

void TMainForm::ConfigureDevice() {
        ErrorCode   ret = Success;
        DeviceInformation devInfo(configure.deviceName);
        ret = wfAiCtrl->setSelectedDevice(devInfo);
        CheckError(ret);
        ret = wfAiCtrl->LoadProfile(configure.profilePath);
        CheckError(ret);

        Conversion * conversion = wfAiCtrl->getConversion();
        Record * record = wfAiCtrl->getRecord();
        ret = conversion->setChannelStart(configure.channelStart);
        CheckError(ret);
        ret = conversion->setChannelCount(configure.channelCount);
        CheckError(ret);
        ret = record->setSectionLength(configure.sectionLength);
        CheckError(ret);
        ret = record->setSectionCount(1);// The nonzero value means one buffered mode.
        CheckError(ret);
        ret = wfAiCtrl->getConversion()->setClockRate(configure.clockRate);
        CheckError(ret);

        for (int i = 0; i < wfAiCtrl->getChannels()->getCount(); i++) {
            ret = wfAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
            CheckError(ret);
        }

        // trigger parameters setting
        Trigger* trigger = wfAiCtrl->getTrigger();
        if (trigger != NULL) {
                trigger->setAction(configure.triggerAction);
                trigger->setSource(configure.triggerSource);
                trigger->setDelayCount(configure.delayCount) ;
                trigger->setEdge(configure.triggerEdge);
                trigger->setLevel(configure.triggerLevel);
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
        double xmax,xmin;
        AnsiString units[9] = {"kV", "V", "mV", "uV", "kA", "A", "mA", "uA", "C"};
        AnsiString tunits[4] = {"ns", "us", "ms", "s"};

        double convertRate = wfAiCtrl->getConversion()->getClockRate();
        int timeUnit = 2;

        double timeInterval = 100.0 * DataView->Width / convertRate;
        double shiftMax = 1000.0 * configure.sectionLength / wfAiCtrl->getConversion()->getClockRate();
        while (convertRate >= 10 * 1000)
        {
         timeInterval *= 1000;
         shiftMax *= 1000;
         convertRate /= 1000;
         --timeUnit;
        }

        int divValue = (int)timeInterval;
        int divMin = divValue / 10;
        if ( divMin == 0 )
         divMin = 1;

        divTrackBar->Max = 4 * divValue; //the max vaule of int.
        divTrackBar->Min = divMin;
        divTrackBar->Position = divValue;
        divTimeLabel->Caption = tunits[timeUnit];

        shiftTrackBar->Max = (int)shiftMax;
        shiftTrackBar->Min = 0;
        shiftTrackBar->Position = 0;
        shiftTimeEditor->Text = "0";
        shiftTimeLabel->Caption = tunits[timeUnit];

	//set parameters for plot.simple graph init
        m_graph->OverOneScreenMode = EndScreen;
        m_graph->XCordTimeDiv = divTrackBar->Position;
        m_graph->XCordOffset = shiftTrackBar->Position;

        //X-Axis
        xmin= m_graph->XCordOffset;
        xmax = m_graph->XCordTimeDiv * 10 + xmin;
        int tm_unit_idx;
        for (tm_unit_idx = timeUnit; tm_unit_idx < 3 && xmax > 1000; ++tm_unit_idx)
	{
		xmax /= 1000;
		xmin /= 1000;
	}
        xLLabel->Caption = String(xmin) + tunits[tm_unit_idx];
        xRLabel->Caption = String(xmax) + tunits[tm_unit_idx];

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

        m_graph->YCordMax = vrgRange.Max;
        m_graph->YCordMin = vrgRange.Min;

        yTLabel->Caption = String(vrgRange.Max) + ustr;
        yMLabel->Caption = String((vrgRange.Max + vrgRange.Min) / 2) + ustr;
        yBLabel->Caption = String(vrgRange.Min) + ustr;

        m_graph->Clear();
}
//--------------------------------------------------------------------------
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

void __fastcall TMainForm::BtnStartClick(TObject *Sender)
{
        ErrorCode ret = Success;
        ret = wfAiCtrl->Start();
        if (ret != Success) {
                CheckError(ret);
                return;
        }

        shiftTrackBar->Enabled = true;
        divTrackBar->Enabled = true;
        BtnStart->Enabled = false;
        BtnConfig->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::shiftTrackBarChange(TObject *Sender)
{
        AnsiString ustr;
        double xmax,xmin;

        if (shiftTrackBar->Enabled == false) {
                return;
        }

        xmin= shiftTrackBar->Position;
        xmax = m_graph->XCordTimeDiv * 10 + xmin;
        if (xmax >= 1000) {
                if (divTimeLabel->Caption == "us") {
                        ustr = "ms";
                } else {
                        ustr = "Sec";
                }

                xmin /= 1000;
                xmax /= 1000;
        } else {
                ustr = divTimeLabel->Caption;
        }

        xLLabel->Caption = String(xmin) + ustr;
        xRLabel->Caption = String(xmax) + ustr;
        shiftTimeEditor->Text = shiftTrackBar->Position;
        
        m_graph->Shift(shiftTrackBar->Position);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::divTrackBarChange(TObject *Sender)
{
        if (divTrackBar->Enabled == false) {
                return;
        }

        m_graph->ScaleXCord(divTrackBar->Position);
        divTimeEditor->Text = divTrackBar->Position;
        shiftTrackBarChange(shiftTrackBar);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BtnConfigClick(TObject *Sender)
{
        ConfigForm->isFirstLoad = false;
        ConfigForm->isBtnOkClicked = false;

        ConfigForm->RefreshConfigureParameter();
        if (!ConfigForm->Showing) {
                ConfigForm->ShowModal();
        }
}
//-----------------------------------------------------------------------------
void BDAQCALL TMainForm::OnStoppedEvent(void *sender, BfdAiEventArgs * args, void * userParam)
{
        TMainForm * uParam = (TMainForm *)userParam;
        //get data
        ErrorCode ret = Success;
        WaveformAiCtrl * wfAiCtrl = (WaveformAiCtrl*)sender;

        //The WavformAiCtrl has been disposed.
        if (wfAiCtrl->getState() == Idle) {
                return;
        }
        int getDataCount = Min(uParam->dataCount, args->Count);
        ret = wfAiCtrl->GetData(getDataCount, uParam->dataScaled, 0, NULL, NULL, NULL, NULL);
        if ((ret >= ErrorHandleNotValid) && (ret != Success)) {
                uParam->BtnStart->Enabled = true;
                uParam->BtnConfig->Enabled = true;
                uParam->CheckError(ret);
        }

        //draw the data to the PaintBox
        uParam->m_graph->Chart(uParam->dataScaled, getDataCount, uParam->configure.channelCount, uParam->configure.sectionLength, 1.0 / wfAiCtrl->getConversion()->getClockRate());

        uParam->BtnStart->Enabled = true;
        uParam->BtnConfig->Enabled = true;
}
//-----------------------------------------------------------------------------

void TMainForm::InitListView() {
        TListItems* items = chanDataList->Items;
        for (int i = 0; i < 16; i++) {
                items->Item[i / 8]->SubItems->Strings[i % 8] = " ";
        }
}
//----------------------------------------------------------------------------


