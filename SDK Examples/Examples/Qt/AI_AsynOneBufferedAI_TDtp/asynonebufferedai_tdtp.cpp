#include "asynonebufferedai_tdtp.h"
#include <QPalette>
#include <QtWidgets/QListWidgetItem>
#include <QtWidgets/QMessageBox>
#include <qmath.h>

AsynOneBufferedAI_TDtp::AsynOneBufferedAI_TDtp(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	this->setAutoFillBackground(true);
	QPixmap pixMap(":/AsynOneBufferedAI_TDtp/Resources/Background.png");
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

	connect(this, SIGNAL(UpdateGraph(int)), this, SLOT(GraphInitialize(int)));
	connect(this, SIGNAL(updateTriggerFlag()), this, SLOT(TriggerFlag()));
}

AsynOneBufferedAI_TDtp::~AsynOneBufferedAI_TDtp()
{
   if (waveformAiCtrl != NULL)
   {
      waveformAiCtrl->Dispose();
      waveformAiCtrl = NULL;
   }

	if (scaledData != NULL) {
		delete []scaledData;
		scaledData = NULL;
	}
}

void AsynOneBufferedAI_TDtp::Initialize()
{
	setWindowTitle(tr("Asynchronous One Buffered AI with Trigger Delay to Stop - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
	ConfigureGraph();
	InitializeList();

	dataReadyCount = 0;
	ui.triggerPointFlag->move(46, 367);
	ui.label_triggerPoint->move(64, 373);
	if (isTriggerSupported && !isSourceNone) {
		ui.triggerPointFlag->setVisible(true);
		ui.label_triggerPoint->setText(tr("0 ms Triggered."));
		ui.label_triggerPoint->setVisible(true);
	} else {
		ui.triggerPointFlag->setVisible(false);
		ui.label_triggerPoint->setVisible(false);
	}

	ui.btnConfigure->setEnabled(true);
	ui.btnGetData->setEnabled(true);
	ui.sldShift->setEnabled(true);
	ui.sldDiv->setEnabled(true);
}

void AsynOneBufferedAI_TDtp::ConfigureDevice()
{
	ErrorCode errorCode = Success;
	
	if (scaledData != NULL) {
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
    errorCode = waveformAiCtrl->getRecord()->setSectionCount(sectionCount);//The nonzero value means "One Buffered" mode.
    CheckError(errorCode);

    for (int i = 0; i < waveformAiCtrl->getChannels()->getCount(); i++) {
       errorCode = waveformAiCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
       CheckError(errorCode);
    }

    if (configure.triggerIndex == 0)
    {
       if (waveformAiCtrl->getFeatures()->getTriggerCount() > 0)
       {
          this->isTriggerSupported = ((waveformAiCtrl->getFeatures()->getTriggerCount() > 0) ? TRUE : FALSE);
          if (waveformAiCtrl->getFeatures()->getTriggerCount() > 1)
          {
             errorCode = waveformAiCtrl->getTrigger1()->setSource(SignalNone);
             CheckError(errorCode);
          }

         //trigger parameters setting
         Trigger* trigger = waveformAiCtrl->getTrigger();
         if (trigger != NULL) {
            errorCode = trigger->setSource(configure.triggerSource);
            CheckError(errorCode);
            if (trigger->getSource() != SignalNone)
            {
               errorCode = trigger->setAction(configure.triggerAction);
               CheckError(errorCode);
               errorCode = trigger->setDelayCount(configure.delayCount) ;
               CheckError(errorCode);
               errorCode = trigger->setEdge(configure.triggerEdge);
               CheckError(errorCode);
               errorCode = trigger->setLevel(configure.triggerLevel);
               CheckError(errorCode);
            }
         }

         SignalDrop triggerSource = waveformAiCtrl->getTrigger()->getSource();
         this->isSourceNone = (triggerSource != 0)? false:true;
      }
   }else if (configure.triggerIndex == 1)
   {
      //trigger1 parameters setting
      if (waveformAiCtrl->getFeatures()->getTriggerCount() > 1)
      {
         Trigger * trigger1 = waveformAiCtrl->getTrigger1();
         if (waveformAiCtrl->getFeatures()->getTriggerCount() > 0)
         {
            errorCode = waveformAiCtrl->getTrigger()->setSource(SignalNone);
            CheckError(errorCode);
         }
         if (trigger1 != NULL) {
            errorCode = trigger1->setSource(configure.triggerSource);
            CheckError(errorCode);
            if (trigger1->getSource() != SignalNone)
            {
              errorCode = trigger1->setAction(configure.triggerAction);
              CheckError(errorCode);
              errorCode = trigger1->setDelayCount(configure.delayCount) ;
              CheckError(errorCode);
              errorCode = trigger1->setEdge(configure.triggerEdge);
              CheckError(errorCode);
              errorCode = trigger1->setLevel(configure.triggerLevel);
              CheckError(errorCode);
            }
         }

         SignalDrop triggerSource1 = waveformAiCtrl->getTrigger1()->getSource();
         this->isSourceNone = (triggerSource1 != 0)? false : true;
      }
   }

    errorCode = waveformAiCtrl->Prepare();
	CheckError(errorCode);
}

void AsynOneBufferedAI_TDtp::ConfigureGraph()
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

void AsynOneBufferedAI_TDtp::ConfigureGraph(int samplesCountPerChan) {
   double clockRate = waveformAiCtrl->getConversion()->getClockRate();
   int tUnit = (int)Millisecond;
   double shiftMax = 1000.0 * samplesCountPerChan / clockRate;
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


void AsynOneBufferedAI_TDtp::InitializeList()
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

void AsynOneBufferedAI_TDtp::SetXCord()
{
	graph->m_xCordTimeDiv = (double)ui.sldDiv->value();
	graph->m_xCordTimeOffset = (double)ui.sldShift->value();
	QString xRanges[2];

	double shiftMaxValue = qRound(graph->m_xCordTimeDiv * 10 + graph->m_xCordTimeOffset);
	graph->GetXCordRange(xRanges, shiftMaxValue, graph->m_xCordTimeOffset, timeUnit);
	ui.lblXCoordinateStart->setText(xRanges[1]);
	ui.lblXCoordinateEnd->setText(xRanges[0]);
}

void AsynOneBufferedAI_TDtp::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void AsynOneBufferedAI_TDtp::OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam)
{
   AsynOneBufferedAI_TDtp * uParam = (AsynOneBufferedAI_TDtp *)userParam;
   ((WaveformAiCtrl *)sender)->GetData(args->Count, uParam->scaledData, 0, NULL, NULL, NULL, NULL);
   uParam->dataReadyCount = args->Count;
   int chanCount = uParam->waveformAiCtrl->getConversion()->getChannelCount();
   emit uParam->UpdateGraph(uParam->dataReadyCount / chanCount);
}

void AsynOneBufferedAI_TDtp::GraphInitialize(int samplesCountPerChan) {
	ConfigureGraph(samplesCountPerChan);	
   graph->Clear();
	graph->Chart(scaledData, configure.channelCount, dataReadyCount /configure.channelCount, 1.0 / waveformAiCtrl->getConversion()->getClockRate());
	
	emit updateTriggerFlag(); 
}

void AsynOneBufferedAI_TDtp::TriggerFlag() {
	if (isTriggerSupported && !isSourceNone) {
      int totalDataCountPerChan = dataReadyCount / waveformAiCtrl->getConversion()->getChannelCount();
        
        int delayCount = 0;
        if (configure.triggerIndex == 0)
        {
           delayCount = waveformAiCtrl->getTrigger()->getDelayCount();
        } 
        else
        {
           delayCount = waveformAiCtrl->getTrigger1()->getDelayCount();
        }
        
        double rate = waveformAiCtrl->getConversion()->getClockRate();

		//set the trigger time
		QString timeUnit = "ms";
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

		ui.label_triggerPoint->setText(QString("%1").arg(triggerTime) + tr(" ") + timeUnit + tr(" Triggered."));
      int relativeWidth = GetArrowXCordRelativeWidth(dataReadyCount / waveformAiCtrl->getConversion()->getChannelCount(),  waveformAiCtrl->getTrigger()->getDelayCount(), ui.graphFrame->width());

		ui.triggerPointFlag->setVisible(false);
		ui.label_triggerPoint->setVisible(false);
		ui.triggerPointFlag->move(46, 367);
		ui.label_triggerPoint->move(64, 373);
		
		if (relativeWidth == 0) {
			ui.triggerPointFlag->setVisible(false);
			ui.label_triggerPoint->setVisible(false);
		} else {
			ui.triggerPointFlag->move(ui.triggerPointFlag->x() + relativeWidth, ui.triggerPointFlag->y());
			ui.triggerPointFlag->setVisible(true);
			ui.label_triggerPoint->move(ui.label_triggerPoint->x() + relativeWidth, ui.label_triggerPoint->y());
			ui.label_triggerPoint->setVisible(true);
		}
	}
	
	//Emit the signal 'uptateButton' to enable the main frame's button. 
	emit UpdateButton(); 
}

//////////////////////////////////////////////////////////////////////////
//These function is used to enable the button 
//////////////////////////////////////////////////////////////////////////
void AsynOneBufferedAI_TDtp::ButtonEnable()
{
	ui.btnConfigure->setEnabled(true);
	ui.btnGetData->setEnabled(true);
}

void AsynOneBufferedAI_TDtp::ButtonConfigureClicked()
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

void AsynOneBufferedAI_TDtp::ButtonGetDataClicked()
{
	ErrorCode errorCode = waveformAiCtrl->Start();
	CheckError(errorCode);

	ui.btnConfigure->setEnabled(false);
	ui.btnGetData->setEnabled(false);
	ui.sldDiv->setEnabled(true);
	ui.sldShift->setEnabled(true);
}

void AsynOneBufferedAI_TDtp::ShiftValueChanged(int value)
{
	ui.edtShiftValue->setText(QString("%1").arg(value));
	graph->Shift(value);
	
	SetXCord();

	if (isTriggerSupported && !isSourceNone) {
		ui.triggerPointFlag->move(46, 367);
		ui.label_triggerPoint->move(64, 373);
		ui.triggerPointFlag->setVisible(false);
		ui.label_triggerPoint->setVisible(false);

      int delayCount = 0;
      if (configure.triggerIndex == 0)
      {
         delayCount = waveformAiCtrl->getTrigger()->getDelayCount();
      } 
      else
      {
         delayCount = waveformAiCtrl->getTrigger1()->getDelayCount();
      }

		SetTriggerPointFlagLoacation(delayCount);
	}
}

void AsynOneBufferedAI_TDtp::DivValueChanged(int value)
{
	ui.edtDivValue->setText(QString("%1").arg(value));
	graph->Div(value);
	
	SetXCord();

	if (isTriggerSupported && !isSourceNone) {
		ui.triggerPointFlag->move(46, 367);
		ui.label_triggerPoint->move(64, 373);
		ui.triggerPointFlag->setVisible(false);
		ui.label_triggerPoint->setVisible(false);
      int delayCount = 0;
      if (configure.triggerIndex == 0)
      {
         delayCount = waveformAiCtrl->getTrigger()->getDelayCount();
      } 
      else
      {
         delayCount = waveformAiCtrl->getTrigger1()->getDelayCount();
      }

      SetTriggerPointFlagLoacation(delayCount);
	}
}

int AsynOneBufferedAI_TDtp::GetArrowXCordRelativeWidth(int dataCount, int delayCount, int pixelCount) {
	int relativePixelWidth = 0;
	int shift = ui.sldShift->value();
	int divide = ui.sldDiv->value();
	double rate = waveformAiCtrl->getConversion()->getClockRate();

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

void AsynOneBufferedAI_TDtp::SetTriggerPointFlagLoacation(int delayCount) {
	int dataCount = dataReadyCount / waveformAiCtrl->getConversion()->getChannelCount();
	int relativeWidth = GetArrowXCordRelativeWidth(dataCount, delayCount, ui.graphFrame->width());

	if (relativeWidth == 0) {
		ui.triggerPointFlag->setVisible(false);
		ui.label_triggerPoint->setVisible(false);
	} else {
		ui.triggerPointFlag->move(ui.triggerPointFlag->x() + relativeWidth, ui.triggerPointFlag->y());
		ui.triggerPointFlag->setVisible(true);
		ui.label_triggerPoint->move(ui.label_triggerPoint->x() + relativeWidth, ui.label_triggerPoint->y());
		ui.label_triggerPoint->setVisible(true);
	}

	if (ui.triggerPointFlag->x() < 46) {
		ui.triggerPointFlag->setVisible(false);
		ui.label_triggerPoint->setVisible(false);
	}
}
