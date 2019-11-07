#include "asynchronousonebufferedai.h"
#include <QPalette>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QMessageBox>
#include <qmath.h>


AI_AsynchronousOneBufferedAi::AI_AsynchronousOneBufferedAi(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	this->setAutoFillBackground(true);
	QPixmap pixMap(":/AI_AsynchronousOneBufferedAi/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(this->backgroundRole(), QBrush(pixMap));
	this->setPalette(backPalette);

	graph = new SimpleGraph(ui.graphFrame);
	graph->setFixedSize(ui.graphFrame->size());

	timeUnit = Millisecond;
	scaledData = NULL;

   waveformAiCtrl = WaveformAiCtrl::Create();
   waveformAiCtrl->addStoppedHandler(OnStoppedEvent, this);

	connect(ui.btnConfigure, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
	connect(ui.btnGetData, SIGNAL(clicked()), this, SLOT(ButtonGetDataClicked()));
	connect(ui.sldShift, SIGNAL(valueChanged(int)), this, SLOT(ShiftValueChanged(int)));
	connect(ui.sldDiv, SIGNAL(valueChanged(int)), this, SLOT(DivValueChanged(int)));
	
	//connect the signal 'UpdateButton' the the slot 'ButtonEnable'.
	connect(this, SIGNAL(UpdateButton()), this, SLOT(ButtonEnable()));
}

AI_AsynchronousOneBufferedAi::~AI_AsynchronousOneBufferedAi()
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

void AI_AsynchronousOneBufferedAi::Initialize()
{
	setWindowTitle(tr("Asynchronous One Buffered AI - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
	ConfigureGraph();
	InitializeList();

	ui.btnConfigure->setEnabled(true);
	ui.btnGetData->setEnabled(true);
	ui.sldShift->setEnabled(true);
	ui.sldDiv->setEnabled(true);
}

void AI_AsynchronousOneBufferedAi::ConfigureDevice()
{
	ErrorCode errorCode = Success;
	if (scaledData != NULL)
	{
		delete []scaledData;
		scaledData = NULL;
	}
	int32 rawDataBufferLength = configure.channelCount * configure.sectionLength;
	scaledData = new double[rawDataBufferLength];
	if (scaledData == NULL)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("Sorry! Error in allocating memory...."));
		return;
	}
	
	// Select a device with AccessWrite/AccessWriteWithReset mode with device number 
	// or device description.
    QString deviceDesc = configure.deviceName;
    const wchar_t * description = reinterpret_cast<const wchar_t *>(deviceDesc.utf16());
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
   errorCode = waveformAiCtrl->getRecord()->setSectionCount(sectionCount);//The nonzero value means "One Buffered" mode.
   CheckError(errorCode);
   for (int i = 0; i < waveformAiCtrl->getChannels()->getCount(); i++)
   {
      errorCode = waveformAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
      CheckError(errorCode);
   }

   errorCode = waveformAiCtrl->Prepare();
	CheckError(errorCode);
}

void AI_AsynchronousOneBufferedAi::ConfigureGraph()
{	
   double clockRate = waveformAiCtrl->getConversion()->getClockRate();
   int tUnit = (int)Millisecond;
   double shiftMax = 1000.0 * configure.sectionLength / clockRate;
   double timeInterval = 100.0 * graph->rect().width() / clockRate;
   while (clockRate >= 10 * 1000)
   {
       timeInterval *= 1000;
       clockRate /= 1000;
       shiftMax *= 1000;
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
   ui.edtDivValue->setText(QString("%1").arg(divValue));

   ui.sldShift->setMaximum((int)shiftMax);
   ui.sldShift->setMinimum(0);
   ui.sldShift->setValue(0);
   int shiftTime = ui.sldShift->value();
   ui.edtShiftValue->setText(QString("%1").arg(shiftTime));

   QString spted_unit[] = {tr("ns"), tr("us"), tr("ms"), tr("Sec")};
   ui.lblShiftUnit->setText(spted_unit[tUnit]);
   ui.lblDivUnit->setText(spted_unit[tUnit]);

   SetXCord();

	ValueUnit unit;
	MathInterval rangeY;
	QString yRanges[3] = {tr("")};
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

void AI_AsynchronousOneBufferedAi::InitializeList()
{
	ui.listWidget->clear();
	QListWidgetItem *item = NULL;
	for (int i = 0; i < configure.channelCount; i++)
	{
		item = new QListWidgetItem(tr(""), ui.listWidget);
		item->setBackgroundColor(SimpleGraph::lineColor[i]);
		item->setSizeHint(QSize(66, 18));
	}
}

void AI_AsynchronousOneBufferedAi::SetXCord()
{
	graph->m_xCordTimeDiv = (double)ui.sldDiv->value();
	graph->m_xCordTimeOffset = (double)ui.sldShift->value();
	QString xRanges[2];

	double shiftMaxValue = qRound(graph->m_xCordTimeDiv * 10 + graph->m_xCordTimeOffset);
	graph->GetXCordRange(xRanges, shiftMaxValue, graph->m_xCordTimeOffset, timeUnit);
	ui.lblXCoordinateStart->setText(xRanges[1]);
	ui.lblXCoordinateEnd->setText(xRanges[0]);
}

void AI_AsynchronousOneBufferedAi::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}
//////////////////////////////////////////////////////////////////////////
//These function is used to enable the button 
//////////////////////////////////////////////////////////////////////////
void AI_AsynchronousOneBufferedAi::ButtonEnable()
{
	ui.btnConfigure->setEnabled(true);
	ui.btnGetData->setEnabled(true);
}

void AI_AsynchronousOneBufferedAi::ButtonConfigureClicked()
{
	graph->Clear();

	configureDialog->RefreshConfigureParameter();
	int resultDialog = configureDialog->exec();
	if (resultDialog == QDialog::Accepted)
	{
		configure = configureDialog->GetConfigureParameter();
		Initialize();
	}
}

void AI_AsynchronousOneBufferedAi::ButtonGetDataClicked()
{
   ErrorCode errorCode = waveformAiCtrl->Start();
	CheckError(errorCode);

	ui.btnConfigure->setEnabled(false);
	ui.btnGetData->setEnabled(false);
	ui.sldDiv->setEnabled(true);
	ui.sldShift->setEnabled(true);
}

void AI_AsynchronousOneBufferedAi::ShiftValueChanged(int value)
{
	ui.edtShiftValue->setText(QString("%1").arg(value));
	graph->Shift(value);
	
	SetXCord();
}

void AI_AsynchronousOneBufferedAi::DivValueChanged(int value)
{
	ui.edtDivValue->setText(QString("%1").arg(value));
	graph->Div(value);
	
	SetXCord();
}

void AI_AsynchronousOneBufferedAi::OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   AI_AsynchronousOneBufferedAi * uParam = (AI_AsynchronousOneBufferedAi *)userParam;
	((WaveformAiCtrl*)sender)->GetData(args->Count, uParam->scaledData, 0, NULL, NULL, NULL, NULL);
	uParam->graph->Chart(uParam->scaledData, uParam->configure.channelCount, 
      args->Count / uParam->configure.channelCount, 1.0 / uParam->configure.clockRatePerChan);

	//Emit the signal 'uptateButton' to enable the main frame's button.
	emit uParam->UpdateButton();

}
