#include "streamingbufferedai.h"
#include <QtWidgets/QMessageBox>
#include <QPalette>
#include <QtWidgets/QListWidgetItem>
#include <qmath.h>

AI_StreamingBufferedAi::AI_StreamingBufferedAi(QDialog *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	this->setAutoFillBackground(true);
	QPixmap pixMap(":/AI_StreamingBufferedAi/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(this->backgroundRole(), QBrush(pixMap));
	this->setPalette(backPalette);

	graph = new SimpleGraph(ui.graphFrame);
	graph->setFixedSize(ui.graphFrame->size());

	timeUnit = Millisecond;
	rawDataBufferLength = 0;
	scaledData = NULL;

    waveformAiCtrl  = WaveformAiCtrl::Create();
   
    waveformAiCtrl->addDataReadyHandler(OnDataReadyEvent, this);
    waveformAiCtrl->addOverrunHandler(OnOverRunEvent, this);
    waveformAiCtrl->addCacheOverflowHandler(OnCacheOverflowEvent, this);
    waveformAiCtrl->addStoppedHandler(OnStoppedEvent, this);

	connect(ui.btnConfigure, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnPause, SIGNAL(clicked()), this, SLOT(ButtonPauseClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.sldDiv, SIGNAL(valueChanged(int)), this, SLOT(DivValueChanged(int)));
}

AI_StreamingBufferedAi::~AI_StreamingBufferedAi()
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

void AI_StreamingBufferedAi::Initialize()
{
	setWindowTitle(tr("Streaming AI - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
	ConfigureGraph();
	InitializeList();

	ui.btnConfigure->setEnabled(true);
	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(false);
	ui.sldDiv->setEnabled(true);
}

void AI_StreamingBufferedAi::ConfigureDevice()
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
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

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

   for (int i = 0; i < waveformAiCtrl->getChannels()->getCount(); i++)
	{
		errorCode = waveformAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
		CheckError(errorCode);
	}

	errorCode = waveformAiCtrl->Prepare();
	CheckError(errorCode);
}

void AI_StreamingBufferedAi::ConfigureGraph()
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

void AI_StreamingBufferedAi::InitializeList()
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

void AI_StreamingBufferedAi::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void AI_StreamingBufferedAi::SetXCord()
{
	graph->m_xCordTimeDiv = (double)ui.sldDiv->value();
	QString xRanges[2];

	double shiftMaxValue = qRound(graph->m_xCordTimeDiv * 10 + graph->m_xCordTimeOffset);
	graph->GetXCordRange(xRanges, shiftMaxValue, graph->m_xCordTimeOffset, timeUnit);
	ui.lblXCoordinateStart->setText(xRanges[1]);
	ui.lblXCoordinateEnd->setText(xRanges[0]);
}

void AI_StreamingBufferedAi::DivValueChanged(int value)
{
	graph->Div(value);
	SetXCord();
}

void AI_StreamingBufferedAi::ButtonConfigureClicked()
{
	configureDialog->RefreshConfigureParameter();
	int resultDialog = configureDialog->exec();
	if (resultDialog == QDialog::Accepted)
	{
		configure = configureDialog->GetConfigureParameter();
		Initialize();
	}
}

void AI_StreamingBufferedAi::ButtonStartClicked()
{
	ui.btnConfigure->setEnabled(false);
	ui.btnStart->setEnabled(false);
	ui.btnPause->setEnabled(true);
	ui.btnStop->setEnabled(true);

	ErrorCode errorCode = waveformAiCtrl->Start();
	CheckError(errorCode);
	xInc = 1.0 / waveformAiCtrl->getConversion()->getClockRate();
}

void AI_StreamingBufferedAi::ButtonPauseClicked()
{
   ErrorCode errorCode = waveformAiCtrl->Stop();
	CheckError(errorCode);

	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(true);
}

void AI_StreamingBufferedAi::ButtonStopClicked()
{
   ErrorCode errorCode = waveformAiCtrl->Stop();
	CheckError(errorCode);

	graph->Clear();

	ui.btnConfigure->setEnabled(true);
	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(false);
}

void AI_StreamingBufferedAi::OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   AI_StreamingBufferedAi * uParam = (AI_StreamingBufferedAi *)userParam;
	int32 getDataCount = ((uParam->configure.sectionLength * uParam->configure.channelCount) < args->Count)?(uParam->configure.sectionLength * uParam->configure.channelCount) : args->Count;
   ErrorCode ret = ((WaveformAiCtrl*)sender)->GetData(getDataCount, uParam->scaledData, 0, NULL, NULL, NULL, NULL);
	if (ret != Success && ret != WarningRecordEnd)
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(ret, 16).right(8);
		QMessageBox::information(uParam, "Warning Information", message);
		return;
	}
	uParam->graph->Chart(uParam->scaledData, uParam->configure.channelCount, getDataCount / 
      uParam->configure.channelCount, uParam->xInc);
}

void AI_StreamingBufferedAi::OnOverRunEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   /*
   AI_StreamingBufferedAi * uParam = (AI_StreamingBufferedAi *)userParam;
   QString message = tr("The event over run has happened!");
   QMessageBox::information(uParam, "Warning Information", message);
   */
}
void AI_StreamingBufferedAi::OnCacheOverflowEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   /*
   AI_StreamingBufferedAi * uParam = (AI_StreamingBufferedAi *)userParam;
   QString message = tr("The event cache over flow has happened!");
   QMessageBox::information(uParam, "Warning Information", message);
   */
}

void AI_StreamingBufferedAi::OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   /*
   AI_StreamingBufferedAi * uParam = (AI_StreamingBufferedAi *)userParam;
   QString message = tr("The event stopped has happened!");
   QMessageBox::information(uParam, "Warning Information", message);
   */
}
