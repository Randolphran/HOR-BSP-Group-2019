#include "streamingai_retrigger.h"
#include <QMessageBox>
#include <QPalette>
#include <QListWidgetItem>
#include <qmath.h>

StreamingAI_Retrigger::StreamingAI_Retrigger(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	this->setAutoFillBackground(true);
	QPixmap pixMap(":/StreamingAI_Retrigger/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(this->backgroundRole(), QBrush(pixMap));
	this->setPalette(backPalette);

	graph = new SimpleGraph(ui.graphFrame);
	graph->setFixedSize(ui.graphFrame->size());

	timeUnit = Millisecond;
	rawDataBufferLength = 0;
	scaledData = NULL;

    waveformAiCtrl = WaveformAiCtrl::Create();

    waveformAiCtrl->addDataReadyHandler(OnDataReadyEvent, this);

    connect(ui.btnConfigure, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
    connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
    connect(ui.btnPause, SIGNAL(clicked()), this, SLOT(ButtonPauseClicked()));
    connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
    connect(ui.sldDiv, SIGNAL(valueChanged(int)), this, SLOT(DivValueChanged(int)));
}

StreamingAI_Retrigger::~StreamingAI_Retrigger()
{
   if (waveformAiCtrl != NULL)
   {
      waveformAiCtrl->Dispose();
      waveformAiCtrl = NULL;
   }

	if (scaledData != NULL)
	{
		delete []scaledData;
		scaledData = NULL;
	}
}

void StreamingAI_Retrigger::Initialize()
{
	setWindowTitle(tr("Streaming AI with Retrigger - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
	ConfigureGraph();
	InitializeList();

	ui.btnConfigure->setEnabled(true);
	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(false);
	ui.sldDiv->setEnabled(true);
}

void StreamingAI_Retrigger::ConfigureDevice()
{
	ErrorCode errorCode = Success;
	if (scaledData != NULL)
	{
		delete []scaledData;
		scaledData = NULL;
	}

	rawDataBufferLength = configure.sectionLength * configure.channelCount;

	scaledData = new double[rawDataBufferLength];
	if (scaledData == NULL)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("Sorry! Error in allocating memory...."));
		return;
	}

	// Select a device with AccessWrite/AccessWriteWithReset mode with device number 
	// or device description.
	wchar_t description [MAX_DEVICE_DESC_LEN] = {0};
	QString devStr = configure.deviceName;
	devStr.toWCharArray(description);
	DeviceInformation selected(description);
	errorCode = waveformAiCtrl->setSelectedDevice(selected);
	CheckError(errorCode); 
	errorCode = waveformAiCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

	//Set the streaming mode.
    errorCode = waveformAiCtrl->getConversion()->setChannelCount(configure.channelCount);
    CheckError(errorCode);
    errorCode = waveformAiCtrl->getConversion()->setChannelStart(configure.channelStart);
    CheckError(errorCode);
    errorCode = waveformAiCtrl->getConversion()->setClockRate(configure.clockRatePerChan);
    CheckError(errorCode);
    errorCode = waveformAiCtrl->getRecord()->setSectionLength(configure.sectionLength);
    CheckError(errorCode);
    errorCode = waveformAiCtrl->getRecord()->setSectionCount(sectionCount);//The 0 means setting 'streaming' mode.
    CheckError(errorCode);
    errorCode = waveformAiCtrl->getRecord()->setCycles(configure.cycles);
    CheckError(errorCode);

   for (int i = 0; i < waveformAiCtrl->getChannels()->getCount(); i++)
   {
        errorCode = waveformAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
        CheckError(errorCode);
   }
	//trigger parameters setting
   Trigger * trigger = waveformAiCtrl->getTrigger();
    if (trigger != NULL) {
        errorCode = trigger->setAction(configure.triggerAction);
        CheckError(errorCode);
        errorCode = trigger->setSource(configure.triggerSource);
        CheckError(errorCode);
        errorCode = trigger->setDelayCount(configure.delayCount) ;
        CheckError(errorCode);
        errorCode = trigger->setEdge(configure.triggerEdge);
        CheckError(errorCode);
        errorCode = trigger->setLevel(configure.triggerLevel);
        CheckError(errorCode);
    }

    //trigger1 parameters setting
    if(waveformAiCtrl->getFeatures()->getTriggerCount() > 1)
    {
        Trigger* trigger1 = waveformAiCtrl->getTrigger1();
        errorCode = trigger1->setAction(configure.trigger1Action);
        CheckError(errorCode);
        errorCode = trigger1->setSource(configure.trigger1Source);
        CheckError(errorCode);
        errorCode = trigger1->setDelayCount(configure.delayCount1) ;
        CheckError(errorCode);
        errorCode = trigger1->setEdge(configure.trigger1Edge);
        CheckError(errorCode);
        errorCode = trigger1->setLevel(configure.trigger1Level);
        CheckError(errorCode);
    }

   errorCode = waveformAiCtrl->Prepare();
	CheckError(errorCode);
    xInc = 1.0 / waveformAiCtrl->getConversion()->getClockRate();
}

void StreamingAI_Retrigger::ConfigureGraph()
{
   double clockRate = waveformAiCtrl->getConversion()->getClockRate();
   int tUnit = (int)Millisecond;
   double timeInterval = 100.0 * graph->rect().width() / clockRate;
   while (clockRate >= 10 * 1000)
   {
       timeInterval *= 1000;
       clockRate /= 1000;
       --tUnit;
   }
   timeUnit = (TimeUnit)tUnit;

   int divValue = (int)timeInterval;
   ui.sldDiv->setMaximum(4 * divValue);
   int divMin = divValue / 10;
   if ( divMin == 0 )
   {
       divMin = 1;
   }
   ui.sldDiv->setMinimum(divMin);
   ui.sldDiv->setValue(divValue);   
   SetXCord();
	
	ValueUnit unit;
	MathInterval rangeY;
	QString yRanges[3];
	ErrorCode errorCode = AdxGetValueRangeInformation(configure.valueRange, 0, NULL, 
		&rangeY, &unit);
	CheckError(errorCode);
	
	graph->GetYCordRange(yRanges, rangeY.Max, rangeY.Min, unit);
	ui.lblYCoordinateMax->setText(yRanges[0]);
	ui.lblYCoordinateMin->setText(yRanges[1]);
	ui.lblYCoordinateMid->setText(yRanges[2]);
	if (Milliampere == unit || Millivolt == unit)
	{
		rangeY.Max /= 1000;
		rangeY.Min /= 1000;
	}

	graph->m_yCordRangeMax = rangeY.Max;
	graph->m_yCordRangeMin = rangeY.Min;
	graph->Clear();
}

void StreamingAI_Retrigger::InitializeList()
{
	ui.listWidget->clear();
	QListWidgetItem *item = NULL;
	for (int i = 0; i < configure.channelCount; i++)
	{
		item = new QListWidgetItem(tr(""), ui.listWidget);
		item->setBackgroundColor(SimpleGraph::lineColor[i]);
		item->setSizeHint(QSize(54, 21));
	}
}

void StreamingAI_Retrigger::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void StreamingAI_Retrigger::SetXCord()
{
	graph->m_xCordTimeDiv = (double)ui.sldDiv->value();
	QString xRanges[2] = {tr("")};

	double shiftMaxValue = qRound(graph->m_xCordTimeDiv * 10 + graph->m_xCordTimeOffset);
	graph->GetXCordRange(xRanges, shiftMaxValue, graph->m_xCordTimeOffset, timeUnit);
	ui.lblXCoordinateStart->setText(xRanges[1]);
	ui.lblXCoordinateEnd->setText(xRanges[0]);
}

void StreamingAI_Retrigger::DivValueChanged(int value)
{
	graph->Div(value);

	SetXCord();
}


void StreamingAI_Retrigger::ButtonConfigureClicked()
{
	configureDialog->RefreshConfigureParameter();
	int resultDialog = configureDialog->exec();
	if (resultDialog == QDialog::Accepted)
	{
		configure = configureDialog->GetConfigureParameter();
		Initialize();
	}
}

void StreamingAI_Retrigger::ButtonStartClicked()
{
	ui.btnConfigure->setEnabled(false);
	ui.btnStart->setEnabled(false);
	ui.btnPause->setEnabled(true);
	ui.btnStop->setEnabled(true);

	ErrorCode errorCode = waveformAiCtrl->Start();
	CheckError(errorCode);
}

void StreamingAI_Retrigger::ButtonPauseClicked()
{
	ErrorCode errorCode = waveformAiCtrl->Stop();
	CheckError(errorCode);

	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(true);
}

void StreamingAI_Retrigger::ButtonStopClicked()
{
	ErrorCode errorCode = waveformAiCtrl->Stop();
	CheckError(errorCode);

	graph->Clear();

	ui.btnConfigure->setEnabled(true);
	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(false);
}

void StreamingAI_Retrigger::OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
 	ErrorCode errorCode = Success;
	int32 returnedCount = 0;
	double timeStamp = 0;
	StreamingAI_Retrigger * uParam = (StreamingAI_Retrigger *)userParam;
	bool flagForRecordEnd = false;
	int32 getDataCount = ((uParam->configure.sectionLength * uParam->configure.channelCount) < args->Count)?(uParam->configure.sectionLength * uParam->configure.channelCount) : args->Count;
   errorCode = ((WaveformAiCtrl*)sender)->GetData(getDataCount, uParam->scaledData, 0, &returnedCount, &timeStamp, NULL, NULL);
	if (errorCode != Success && errorCode != WarningRecordEnd)
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8);
		QMessageBox::information(uParam, "Warning Information", message);
		return;
	}
	flagForRecordEnd = (errorCode == WarningRecordEnd)? true : false;
	returnedCount = (returnedCount < getDataCount)? returnedCount : getDataCount;
 	uParam->graph->Chart(uParam->scaledData, 
								uParam->configure.channelCount, 
								returnedCount / uParam->configure.channelCount, 
								uParam->xInc,
								flagForRecordEnd);
}
