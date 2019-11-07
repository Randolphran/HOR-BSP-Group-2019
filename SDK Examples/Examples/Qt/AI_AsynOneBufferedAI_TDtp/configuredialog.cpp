#include "configuredialog.h"
#include <QtWidgets/QMessageBox>
#include <QProcess>
#include <QFileDialog>

#define MAXCLOCKRATE 500000000

ConfigureDialog::ConfigureDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

    connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged(int)));
    connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
    connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));
    connect(ui.cmbTriggerSource, SIGNAL(currentIndexChanged(int)), this, SLOT(TriggerSourceChanged(int)));
    connect(ui.cmbTriggerTriggerIndex, SIGNAL(currentIndexChanged(int)), this, SLOT(TriggerIndexChanged(int)));
    connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(ButtonBrowseClicked()));

    ui.edtClockRatePerChan->setValidator(new QIntValidator(1, MAXCLOCKRATE, this));
    ui.txtDelayCount->setValidator(new QIntValidator(0, 10000000, this));
    ui.txtTriggerLevel->setValidator(new QIntValidator(-10, 10, this));

    Initailization();
}

ConfigureDialog::~ConfigureDialog()
{

}

void ConfigureDialog::Initailization()
{
    WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
	Array<DeviceTreeNode> *supportedDevice = waveformAiCtrl->getSupportedDevices();

	if (supportedDevice->getCount() == 0)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("No device to support the currently demonstrated function!"));
		QCoreApplication::quit();
	}
	else
	{
		for (int i = 0; i < supportedDevice->getCount(); i++)
		{
			DeviceTreeNode const &node = supportedDevice->getItem(i);
			qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
			ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
		}
		ui.cmbDevice->setCurrentIndex(0);
	}
	configure.profilePath = L"";
    waveformAiCtrl->Dispose();
	supportedDevice->Dispose();
}

void ConfigureDialog::CheckError(ErrorCode errorCode)
{
	if (errorCode >= 0xE0000000 && errorCode != Success)
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void ConfigureDialog::DeviceChanged(int index)
{
	ui.cmbChannelCount->clear();
	ui.cmbChannelStart->clear();
	ui.cmbValueRange->clear();
	ui.cmbTriggerSource->clear();
	ui.cmbTriggerEdge->clear();
    ui.cmbTriggerTriggerIndex->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
    ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);

	ui.btnOK->setEnabled(true);
	if (errorCode != 0){
		QString str;
        QString des = QString::fromStdWString(description);
		str.sprintf("Error:the error code is 0x%x\n\
						The %s is busy or not exit in computer now.\n\
                        Select other device please!", errorCode, des.toUtf8().data());
		QMessageBox::information(this, "Warning Information", str);
		ui.btnOK->setEnabled(false);
		return;
	}

   int channelCount = (waveformAiCtrl->getChannelCount() < 16) ? 
      waveformAiCtrl->getChannelCount() : 16;
	int logicChannelCount = waveformAiCtrl->getChannelCount();

	for (int i = 0; i < logicChannelCount; i++)
	{
		ui.cmbChannelStart->addItem(QString("%1").arg(i));
	}

	for (int i = 0; i < channelCount; i++)
	{
		ui.cmbChannelCount->addItem(QString("%1").arg(i + 1));
	}
	
	//Set value range combo box
	Array<ValueRange> *ValueRanges = waveformAiCtrl->getFeatures()->getValueRanges();
	wchar_t			vrgDescription[128];
	MathInterval	ranges;
	ValueUnit		valueUnit;
	for(int i = 0; i < ValueRanges->getCount(); i++)
	{
		errorCode = AdxGetValueRangeInformation(ValueRanges->getItem(i), 
			sizeof(vrgDescription), vrgDescription, &ranges, &valueUnit);
		CheckError(errorCode);
		
		//we filter the Celsius degree for the buffered AI can not support this function.
		if (valueUnit == CelsiusUnit)
		{
			continue;
		}

		QString str = QString::fromWCharArray(vrgDescription);
		ui.cmbValueRange->addItem(str);
	}

    // for trigger setting
    if (waveformAiCtrl->getFeatures()->getTriggerCount() > 0)
    {
      ui.cmbTriggerTriggerIndex->addItem(tr("trigger0"));
    }

    if (waveformAiCtrl->getFeatures()->getTriggerCount() > 1)
    {
      ui.cmbTriggerTriggerIndex->addItem(tr("trigger1"));
    }

    AiFeatures *features = waveformAiCtrl->getFeatures();
    this->isTriggerSupported = (features->getTriggerCount() > 0) ? TRUE : FALSE;

    ui.cmbTriggerSource->setEnabled(isTriggerSupported);
    ui.cmbTriggerEdge->setEnabled(isTriggerSupported);
    ui.txtDelayCount->setEnabled(isTriggerSupported);
    ui.txtTriggerLevel->setEnabled(isTriggerSupported);
	if (isTriggerSupported) {

		// Initialize trigger parameter: trigger source.
		 wchar_t signalDes[128];
         SignalPosition sigPos;
         ErrorCode errorCode = Success;
         Array<SignalDrop>*  sources = features->getTriggerSources();
		 if (sources != NULL) {
         ui.cmbTriggerSource->clear();
			 for (int i = 0; i < sources->getCount(); i++) {
				 errorCode = AdxGetSignalConnectionInformation(sources->getItem(i),sizeof(signalDes) ,signalDes, &sigPos);
				 CheckError(errorCode);

				 ui.cmbTriggerSource->addItem(QString::fromWCharArray(signalDes));
			 }
		 }

		 //Initialize trigger parameter: trigger edge.
		 ui.cmbTriggerEdge->addItem(tr("RisingEdge"));
		 ui.cmbTriggerEdge->addItem(tr("FallingEdge"));

		 ui.cmbTriggerSource->setCurrentIndex(0);
		 ui.cmbTriggerEdge->setCurrentIndex(0);
	}

	waveformAiCtrl->Dispose();

	//Set the default value.
	ui.cmbChannelStart->setCurrentIndex(0);
	ui.cmbChannelCount->setCurrentIndex(1);
	ui.cmbValueRange->setCurrentIndex(0);

   TriggerSourceChanged(0); 
}

void ConfigureDialog::TriggerSourceChanged(int index) {
	QString source = ui.cmbTriggerSource->currentText();
	if (source == "None" || !isTriggerSupported) {
		ui.cmbTriggerEdge->setEnabled(false);
		ui.txtDelayCount->setEnabled(false);
		ui.txtTriggerLevel->setEnabled(false);
	} else {
		ui.cmbTriggerEdge->setEnabled(true);
		ui.txtDelayCount->setEnabled(true);
		if (source.startsWith("External Digital")) {
			ui.txtTriggerLevel->setEnabled(false);
		} else {
			ui.txtTriggerLevel->setEnabled(true);
		}
	}
}

void ConfigureDialog::TriggerIndexChanged(int index) {
   ui.cmbTriggerSource->clear();
   ui.cmbTriggerEdge->clear();

   std::wstring description = ui.cmbDevice->currentText().toStdWString();
   DeviceInformation selected(description.c_str());

   WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
   ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);

   ui.btnOK->setEnabled(true);
   if (errorCode != 0){
      QString str;
      //QString des = deviceDesc;
      QString des = QString::fromStdWString(description);
      str.sprintf("Error:the error code is 0x%x\n\
                  The %s is busy or not exit in computer now.\n\
                  Select other device please!", errorCode, des.toUtf8().data());
      QMessageBox::information(this, "Warning Information", str);
      ui.btnOK->setEnabled(false);
      return;
   }

   // for trigger setting
   AiFeatures* features = waveformAiCtrl->getFeatures();
   if (index == 0)
   { 
      this->isTriggerSupported = (features->getTriggerCount() > 0) ? TRUE : FALSE;
      ui.cmbTriggerSource->setEnabled(isTriggerSupported);
      ui.cmbTriggerEdge->setEnabled(isTriggerSupported);
      ui.txtDelayCount->setEnabled(isTriggerSupported);
      ui.txtTriggerLevel->setEnabled(isTriggerSupported);
      if (isTriggerSupported) {
         // Initialize trigger parameter: trigger source.
         wchar_t signalDes[128];
         SignalPosition sigPos;
         ErrorCode errorCode = Success;
         Array<SignalDrop>*  sources = features->getTriggerSources();
         if (sources != NULL) {
            for (int i = 0; i < sources->getCount(); i++) {
               errorCode = AdxGetSignalConnectionInformation(sources->getItem(i),sizeof(signalDes) ,signalDes, &sigPos);
               CheckError(errorCode);

               ui.cmbTriggerSource->addItem(QString::fromWCharArray(signalDes));
            }
         }

         SignalDrop src = waveformAiCtrl->getTrigger()->getSource();
         for (int j = 0; j < sources->getCount(); ++j)
         {
            if (src == sources->getItem(j))
            {
               ui.cmbTriggerSource->setCurrentIndex(j);
            }
         }

         //Initialize trigger parameter: trigger edge.
         ui.cmbTriggerEdge->addItem(tr("RisingEdge"));
         ui.cmbTriggerEdge->addItem(tr("FallingEdge"));
         ActiveSignal edge = waveformAiCtrl->getTrigger()->getEdge();
         if (edge == RisingEdge)
         {
            ui.cmbTriggerEdge->setCurrentIndex(0);
         }else if (edge == FallingEdge){
            ui.cmbTriggerEdge->setCurrentIndex(1);
         }
         
         // for trigger level parameter
         double level = waveformAiCtrl->getTrigger()->getLevel();
         ui.txtTriggerLevel->setText(QString::number(level));

         //for trigger delay count parameter
         int count =  waveformAiCtrl->getTrigger()->getDelayCount();
         ui.txtDelayCount->setText(QString::number(count,10));
         
      }
   }else if (index == 1)
   {
      // for trigger1 setting
      this->isTrigger1Supported = (features->getTriggerCount() > 1) ? TRUE : FALSE;
      ui.cmbTriggerSource->setEnabled(isTrigger1Supported);
      ui.cmbTriggerEdge->setEnabled(isTrigger1Supported);
      ui.txtDelayCount->setEnabled(isTrigger1Supported);
      ui.txtTriggerLevel->setEnabled(isTrigger1Supported);
      if (isTrigger1Supported) {
         // Initialize trigger parameter: trigger source.
         wchar_t signalDes[128];
         SignalPosition sigPos;
         ErrorCode errorCode = Success;
         Array<SignalDrop>*  sources1 = features->getTrigger1Sources();
         if (sources1 != NULL) {
            for (int i = 0; i < sources1->getCount(); i++) {
               errorCode = AdxGetSignalConnectionInformation(sources1->getItem(i),sizeof(signalDes) ,signalDes, &sigPos);
               CheckError(errorCode);
               ui.cmbTriggerSource->addItem(QString::fromWCharArray(signalDes));
            }
         }
         SignalDrop src = waveformAiCtrl->getTrigger()->getSource();
         for (int j = 0; j < sources1->getCount(); ++j)
         {
            if (src == sources1->getItem(j))
            {
               ui.cmbTriggerSource->setCurrentIndex(j);
            }
         }

         //Initialize trigger parameter: trigger edge.
         ui.cmbTriggerEdge->addItem(tr("RisingEdge"));
         ui.cmbTriggerEdge->addItem(tr("FallingEdge"));
         ActiveSignal edge = waveformAiCtrl->getTrigger()->getEdge();
         if (edge == RisingEdge)
         {
            ui.cmbTriggerEdge->setCurrentIndex(0);
         }else if (edge == FallingEdge){
            ui.cmbTriggerEdge->setCurrentIndex(1);
         }

         // for trigger level parameter
         double level = waveformAiCtrl->getTrigger1()->getLevel();
         ui.txtTriggerLevel->setText(QString::number(level));

         //for trigger delay count parameter
         int count =  waveformAiCtrl->getTrigger1()->getDelayCount();
         ui.txtDelayCount->setText(QString::number(count,10));
      }
   }
   waveformAiCtrl->Dispose();
   TriggerSourceChanged(0); 
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

	double clockRate = ui.edtClockRatePerChan->text().toDouble();
	int dataCount = ui.edtSectionLength->text().toInt();
	if (clockRate < 1 || clockRate > MAXCLOCKRATE)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("Sorry, the clock rate per channel is invalid"));
		ui.edtSectionLength->setText(tr("1000"));
		return;
	}

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
    ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    Array<ValueRange> *ValueRanges = waveformAiCtrl->getFeatures()->getValueRanges();
    configure.deviceName = ui.cmbDevice->currentText();
    configure.channelCount = ui.cmbChannelCount->currentText().toInt();
    configure.channelStart = ui.cmbChannelStart->currentText().toInt();
    configure.valueRange = ValueRanges->getItem(ui.cmbValueRange->currentIndex());
    configure.sectionLength = ui.edtSectionLength->text().toInt();
    configure.clockRatePerChan = ui.edtClockRatePerChan->text().toDouble();

    configure.triggerIndex = ui.cmbTriggerTriggerIndex->currentIndex();
    if (isTriggerSupported && ui.cmbTriggerTriggerIndex->currentIndex() == 0) {
		 int chanCount = ui.cmbChannelCount->currentText().toInt();
       MathInterval delayCountRange;
       waveformAiCtrl->getFeatures()->getTriggerDelayRange(delayCountRange);
		 SamplingMethod method = waveformAiCtrl->getFeatures()->getSamplingMethod();
		if (method == EqualTimeSwitch) {
			delayCountRange.Max /= chanCount;
		}
		if (ui.txtDelayCount->text().toDouble() > delayCountRange.Max || ui.txtDelayCount->text().toDouble() < delayCountRange.Min) {
			QString str = tr("Error: 'trigger delayCount' is out of range! \nDelay count range is ") + QString("%1 - %2").arg(delayCountRange.Min).arg(delayCountRange.Max);
			QMessageBox::information(this, tr("Warning Information"), str); 
			ui.txtDelayCount->setText(tr("500"));
			return;
		}

		if (ui.txtTriggerLevel->text().toInt() > 10 || ui.txtTriggerLevel->text().toInt() < -10) {
			QMessageBox::information(this, tr("Warning Information"), tr("'trigger level' is out of range \"-10v ~ 10v \""));
			ui.txtTriggerLevel->setText(tr("3"));
			return;
		}
		
		configure.triggerAction = DelayToStop;
		Array<SignalDrop>*  sources = waveformAiCtrl->getFeatures()->getTriggerSources();
		configure.triggerSource = sources->getItem(ui.cmbTriggerSource->currentIndex());
		if (ui.cmbTriggerEdge->currentIndex() == 0) {
			 configure.triggerEdge = RisingEdge;
		} else {
			configure.triggerEdge = FallingEdge;
		}
		configure.delayCount = ui.txtDelayCount->text().toInt();
		configure.triggerLevel = ui.txtTriggerLevel->text().toDouble(); 

		if (configure.delayCount >= configure.sectionLength && ui.cmbTriggerSource->currentIndex() != 0) {
			QMessageBox::information(this, tr("Warning Information"), tr("Delay count must smaller than samples per channel!"));
			return;
		}
	}

   if (isTrigger1Supported && ui.cmbTriggerTriggerIndex->currentIndex() == 1) {
      int chanCount = ui.cmbChannelCount->currentText().toInt();
      MathInterval delayCountRange;
      waveformAiCtrl->getFeatures()->getTrigger1DelayRange(delayCountRange);

      SamplingMethod method = waveformAiCtrl->getFeatures()->getSamplingMethod();
      if (method == EqualTimeSwitch) {
         delayCountRange.Max /= chanCount;
      }
      if (ui.txtDelayCount->text().toDouble() > delayCountRange.Max || ui.txtDelayCount->text().toDouble() < delayCountRange.Min) {
         QString str = tr("Error: 'trigger delayCount' is out of range! \nDelay count range is ") + QString("%1 - %2").arg(delayCountRange.Min).arg(delayCountRange.Max);
         QMessageBox::information(this, tr("Warning Information"), str); 
         ui.txtDelayCount->setText(tr("500"));
         return;
      }

      if (ui.txtTriggerLevel->text().toInt() > 10 || ui.txtTriggerLevel->text().toInt() < -10) {
         QMessageBox::information(this, tr("Warning Information"), tr("'trigger level' is out of range \"-10v ~ 10v \""));
         ui.txtTriggerLevel->setText(tr("3"));
         return;
      }

      configure.triggerAction = DelayToStop;
      Array<SignalDrop>*  sources1 = waveformAiCtrl->getFeatures()->getTrigger1Sources();
      configure.triggerSource = sources1->getItem(ui.cmbTriggerSource->currentIndex());
      if (ui.cmbTriggerEdge->currentIndex() == 0) {
         configure.triggerEdge = RisingEdge;
      } else {
         configure.triggerEdge = FallingEdge;
      }
      configure.delayCount = ui.txtDelayCount->text().toInt();
      configure.triggerLevel = ui.txtTriggerLevel->text().toDouble(); 

      if (configure.delayCount >= configure.sectionLength && ui.cmbTriggerSource->currentIndex() != 0) {
         QMessageBox::information(this, tr("Warning Information"), tr("Delay count must smaller than samples per channel!"));
         return;
      }
   }
	waveformAiCtrl->Dispose();
	this->accept();
}

void ConfigureDialog::ButtonCancelClicked()
{
	this->reject();
}

void ConfigureDialog::ButtonBrowseClicked()
{
	QString str = QFileDialog::getOpenFileName(this, tr("Open Profile"), "../../profile", tr("Image Files(*.xml)")); 
	ui.txtProfilePath->setText(str);
    configure.profilePath = str.toStdWString().c_str();
}

void ConfigureDialog::RefreshConfigureParameter()
{
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

	WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();

	ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);
	CheckError(errorCode);

	ui.edtClockRatePerChan->setText(QString::number(waveformAiCtrl->getConversion()->getClockRate(), 'f',0));
	ui.edtSectionLength->setText(QString::number(waveformAiCtrl->getRecord()->getSectionLength(), 'f', 0));

    waveformAiCtrl->Dispose();
}
