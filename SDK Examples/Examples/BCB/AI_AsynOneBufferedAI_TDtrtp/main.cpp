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
        AnsiString caption = "Asynchronous One Buffered AI with Trigger Delay to Stop and Trigger Delay to Stop - Run("  + deviceName + ")";
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

        triggerPointFlag->Left = 52;
        label_triggerPoint->Left = 68;
        if (isTriggerSupported && !isSourceNone) {
                label_triggerPoint->Visible = true;
                label_triggerPoint->Caption = "0 ms Triggered.";
                triggerPointFlag->Visible = true;
        } else {
                label_triggerPoint->Visible = false;
                triggerPointFlag->Visible = false;
        }
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
        ret = record->setSectionCount(1); //The nonzero value means one buffered mode.
        CheckError(ret);
        ret = wfAiCtrl->getConversion()->setClockRate(configure.clockRate);
        CheckError(ret);

        for (int i = 0; i < wfAiCtrl -> getChannels() -> getCount(); i++) {
            ret = wfAiCtrl -> getChannels() -> getItem(i).setValueRange(configure.valueRange);
            CheckError(ret);
        }

        this->isTriggerSupported = (wfAiCtrl->getFeatures()->getTriggerSupported() > 0) ? TRUE : FALSE;
        
        // trigger parameters setting
        Trigger* trigger = wfAiCtrl->getTrigger();
        if (trigger != NULL) {
                trigger->setAction(configure.triggerAction);
                trigger->setSource(configure.triggerSource);
                trigger->setDelayCount(configure.delayCount) ;
                trigger->setEdge(configure.triggerEdge);
                trigger->setLevel(configure.triggerLevel);
        }

        if (wfAiCtrl->getFeatures()->getTriggerCount() > 1) {
                Trigger* trigger1 = wfAiCtrl->getTrigger1();
                trigger1->setAction(configure.trigger1Action);
                trigger1->setSource(configure.trigger1Source);
                trigger1->setDelayCount(configure.delayCount1);
                trigger1->setEdge(configure.trigger1Edge);
                trigger1->setLevel(configure.trigger1Level);
        }

        SignalDrop triggerSource = wfAiCtrl->getTrigger()->getSource();
        if (triggerSource != 0) {
		this->isSourceNone = false;
	} else {
		this->isSourceNone = true;
	}
}
//---------------------------------------------------------------------------

void TMainForm::CheckError(ErrorCode errorCode) {
        if (BioFailed(errorCode)) {
                int err = errorCode;
                AnsiString str = "Sorry, there are some errors occurred, Error Code: 0x" + Format("%X",ARRAYOFCONST((err)));
                MessageBox(this -> WindowHandle, str.c_str(), "Error", MB_ICONERROR);
        }
}
//---------------------------------------------------------------------------

void TMainForm::InitializeGraph() {
        ValueUnit unit;
        MathInterval vrgRange;
        AnsiString ustr;
        double xmax,xmin;
        AnsiString units[9] = {"kV", "V", "mV", "uV", "kA", "A", "mA", "uA", "C"};

        //time track bar
        shiftTrackBar->Max = (int)(1000.0 * configure.sectionLength);
        shiftTrackBar->Min = 0;
        shiftTrackBar->Position = 0;
        shiftTimeEditor->Text = "0";
        shiftTimeLabel->Caption = "ms";

        divTrackBar->Max = 100000000; //the max vaule of int.
        divTrackBar->Min = 0;
        divTrackBar->Position = (int)(100.0 * DataView->Width / wfAiCtrl->getConversion()->getClockRate());
        divTimeLabel->Caption = "ms";

        //need use 'us'
        if (wfAiCtrl->getConversion()->getClockRate() >= 10000) {
                shiftTrackBar->Max = shiftTrackBar->Max * 1000;
                shiftTimeLabel->Caption = "us";
                divTrackBar->Position = (int)(100.0 * 1000 * DataView->Width / wfAiCtrl->getConversion()->getClockRate());
                divTimeLabel->Caption = "us";
        }

        divTimeEditor->Text = divTrackBar->Position;
        divTrackBar->Max = 4 * divTrackBar->Position;
        divTrackBar->Min = (divTrackBar->Position / 10 > 1) ? divTrackBar->Position / 10 : 1;

        //simple graph init
        m_graph->XCordTimeDiv = divTrackBar->Position;
        m_graph->XCordOffset = shiftTrackBar->Position;

        //X-Axis
        xmin= m_graph->XCordOffset;
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

void TMainForm::InitializeGraph(int samplesCountPerChan) {
        ValueUnit unit;
        MathInterval vrgRange;
        AnsiString ustr;
        double xmax,xmin;
        AnsiString units[9] = {"kV", "V", "mV", "uV", "kA", "A", "mA", "uA", "C"};

        //time track bar
        shiftTrackBar->Max = (int)(1000.0 * samplesCountPerChan / wfAiCtrl->getConversion()->getClockRate());
        shiftTrackBar->Min = 0;
        shiftTrackBar->Position = 0;
        shiftTimeEditor->Text = "0";
        shiftTimeLabel->Caption = "ms";

        divTrackBar->Max = 100000000; //the max vaule of int.
        divTrackBar->Min = 0;
        divTrackBar->Position = (int)(100.0 * DataView->Width / wfAiCtrl->getConversion()->getClockRate());
        divTimeLabel->Caption = "ms";

        //need use 'us'
        if (wfAiCtrl->getConversion()->getClockRate() >= 10000) {
                shiftTrackBar->Max = shiftTrackBar->Max * 1000;
                shiftTimeLabel->Caption = "us";
                divTrackBar->Position = (int)(100.0 * 1000 * DataView->Width / wfAiCtrl->getConversion()->getClockRate());
                divTimeLabel->Caption = "us";
        }

        divTimeEditor->Text = divTrackBar->Position;
        divTrackBar->Max = 4 * divTrackBar->Position;
        divTrackBar->Min = (divTrackBar->Position / 10 > 1) ? divTrackBar->Position / 10 : 1;

        //simple graph init
        m_graph->XCordTimeDiv = divTrackBar->Position;
        m_graph->XCordOffset = shiftTrackBar->Position;

        //X-Axis
        xmin= m_graph->XCordOffset;
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

        //get the value range of each channel.
        ErrorCode ret = AdxGetValueRangeInformation(configure.valueRange, 0, NULL, &vrgRange, &unit);
	CheckError(ret);

        int index = (int)unit;
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

        if (isTriggerSupported && !isSourceNone) {
                triggerPointFlag->Left = 52;
                label_triggerPoint->Left = 68;
                label_triggerPoint->Visible = false;
                triggerPointFlag->Visible = false;
                label_triggerPoint->Caption = "";
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

        if (isTriggerSupported && !isSourceNone) {
                triggerPointFlag->Left = 52;
                label_triggerPoint->Left = 68;
                label_triggerPoint->Visible = false;
                triggerPointFlag->Visible = false;
                SetTriggerPointFlagLoacation(wfAiCtrl->getTrigger()->getDelayCount());
        }
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
        WaveformAiCtrl* wfAiCtrl = (WaveformAiCtrl*)sender;

        //The waveformAiCtrl has been disposed.
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

        uParam->InitializeGraph(uParam->configure.sectionLength);

        //draw the data to the PaintBox
        uParam->m_graph->Chart(uParam->dataScaled, getDataCount, uParam->configure.channelCount, uParam->configure.sectionLength, 1.0 / wfAiCtrl->getConversion()->getClockRate());

        uParam->BtnStart->Enabled = true;
        uParam->BtnConfig->Enabled = true;

        if (uParam->isTriggerSupported && !(uParam->isSourceNone)) {
                uParam->triggerPointFlag->Left = 52;
                uParam->label_triggerPoint->Left = 68;
                uParam->label_triggerPoint->Visible = false;
                uParam->triggerPointFlag->Visible = false;

                int totalDataCountPerChan = uParam->configure.sectionLength;
                int delayCount = wfAiCtrl->getTrigger()->getDelayCount();
                double rate = wfAiCtrl->getConversion()->getClockRate();

                // set the trigger time
                AnsiString timeUnit = "ms";
                double timeFactor = 1000;

                if (rate > 1000 * 1000) {
                        timeUnit = "us";
                        timeFactor = 1000 * 1000;
                }

                double triggerTime = timeFactor * (totalDataCountPerChan - delayCount) / rate;

                if (triggerTime > 1000 && timeUnit == "us") {
                        triggerTime = triggerTime / 1000;
                        timeUnit = "ms";
                }

                 if (triggerTime < 1 && timeUnit == "ms") {
                        triggerTime = triggerTime * 1000;
                        timeUnit = "us";
                }

                uParam->label_triggerPoint->Caption = Format("%.2f",ARRAYOFCONST((triggerTime))) + " " + timeUnit + " Triggered.";

                int relativeWidth = uParam->GetArrowXCordRelativeWidth(uParam->configure.sectionLength, wfAiCtrl->getTrigger()->getDelayCount(), uParam->DataView->Width);
                if (relativeWidth == 0) {
                        uParam->label_triggerPoint->Visible = false;
                        uParam->triggerPointFlag->Visible = false;
                } else {
                        uParam->triggerPointFlag->Left = uParam->triggerPointFlag->Left + relativeWidth;
                        uParam->triggerPointFlag->Visible = true;
                        uParam->label_triggerPoint->Left = uParam->label_triggerPoint->Left + relativeWidth;
                        uParam->label_triggerPoint->Visible = true;
                }
        }

}
//-----------------------------------------------------------------------------

void TMainForm::InitListView() {
        TListItems* items = chanDataList->Items;
        for (int i = 0; i < 16; i++) {
                items->Item[i / 8]->SubItems->Strings[i % 8] = " ";
        }
}
//----------------------------------------------------------------------------

int  TMainForm::GetArrowXCordRelativeWidth(int dataCount, int delayCount, int pixelCount) {
        int relativePixelWidth = 0;
        int shift = shiftTrackBar->Position;
        int divide = divTrackBar->Position;
        double rate = wfAiCtrl->getConversion()->getClockRate();

        if (rate > 10000) {
                rate /= 1000;
        }

        int screenCount = (int)(divide * 10 * rate / 1000);
        int shiftCount = (int)(shift * rate / 1000);

        if ((dataCount - delayCount - shiftCount > 0) && (dataCount - delayCount - shiftCount < screenCount)) {
                relativePixelWidth = pixelCount * (dataCount - delayCount - shiftCount) / screenCount;
        } else {
                relativePixelWidth = 0;
        }

        return relativePixelWidth;
}
//----------------------------------------------------------------------------

void TMainForm::SetTriggerPointFlagLoacation(int delayCount) {
        int dataCount = configure.sectionLength;
        int relativeWidth = GetArrowXCordRelativeWidth(dataCount, delayCount, DataView->Width);

        if (relativeWidth == 0) {
                label_triggerPoint->Visible = false;
                triggerPointFlag->Visible = false;
        } else {
                triggerPointFlag->Left = triggerPointFlag->Left + relativeWidth;
                triggerPointFlag->Visible = true;
                label_triggerPoint->Left = label_triggerPoint->Left + relativeWidth;
                label_triggerPoint->Visible = true;
        }

        if (triggerPointFlag->Left < 52) {
                label_triggerPoint->Visible = false;
                triggerPointFlag->Visible = false;
        }
}
//-----------------------------------------------------------------------------



