#include <QMessageBox>
#include "updowncounter.h"

UpDownCounter::UpDownCounter(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));
	
   udCounterCtrl = UdCounterCtrl::Create();
	timer = new QTimer(this);

	this->buttonGroup1 = new QButtonGroup();
	this->buttonGroup1->addButton(ui.radDisable, 0);
	this->buttonGroup1->addButton(ui.raInfinite, 1);
	this->buttonGroup1->addButton(ui.radFinite, 2);

	ui.txtResetValue->setValidator(new QIntValidator(0, 100000));
	ui.txtResetTimes->setValidator(new QIntValidator(0, 100000));

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
	connect(ui.btnValReset, SIGNAL(clicked()), this, SLOT(ButtonResetValueClicked()));
	connect(buttonGroup1, SIGNAL(buttonClicked(int)), this, SLOT(ResetIndexChged(int)));
	connect(ui.cmbResetValue, SIGNAL(currentIndexChanged(int)), this, SLOT(CmbResetValueChanged()));
}

UpDownCounter::~UpDownCounter()
{
	this->udCounterCtrl->Dispose();
}

void UpDownCounter::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("UpDown Counter - Run(") + configure.deviceName + tr(")"));	

	ui.CounterValueList->clear();

	ConfigureDevice();
	ConfiguratePanel();

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);
	ui.btnValReset->setEnabled(false);	
}

void UpDownCounter::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

	ErrorCode errorCode = udCounterCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = udCounterCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

   errorCode = udCounterCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = udCounterCtrl->setChannelStart(configure.channel);
	CheckError(errorCode);

   for (int i = udCounterCtrl->getChannelStart(); i < udCounterCtrl->getChannelStart() + udCounterCtrl->getChannelCount(); i++)
   {
      errorCode = udCounterCtrl->getChannels()->getItem(i).setCountingType(configure.cntType);
      CheckError(errorCode);
   }
} 

void UpDownCounter::ConfiguratePanel() {
	ui.cmbResetValue->clear();

	// for reset value
	Array<int32> * resetValues = udCounterCtrl->getFeatures()->getUdInitialValues();
	int valueCount = resetValues->getCount();

	int i = 0;
	for (; i < valueCount; i++) {
		if (resetValues->getItem(i) != -1) {
			ui.cmbResetValue->addItem(tr("0x") + QString::number(resetValues->getItem(i), 16).right(8));
		} else {
			ui.cmbResetValue->addItem(QString::number(-1, 10));
		}
	}
	if (i == 0) {
		ui.cmbResetValue->setCurrentIndex(0);
	}

	//for using edit text as reset value
	ui.txtResetValue->setText(QString::number(0, 16));

	//radio button for reset value.
	ui.radDisable->setChecked(true);
	ui.raInfinite->setChecked(false);
	ui.radFinite->setChecked(false);

	//reset times
	ui.txtResetTimes->setText(tr("0"));
	ui.txtResetTimes->setEnabled(false); 
}

void UpDownCounter::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void UpDownCounter::TimerTicked() {
	ErrorCode errorCode;
	errorCode = udCounterCtrl->setEnabled(true);
	CheckError(errorCode);
 
   int32 value = 0;
   errorCode = udCounterCtrl->Read(1, &value);
   CheckError(errorCode);
   cntrValue = (quint32) value; 
	ui.txtCounterValue->setText(QString("%1").arg(cntrValue));
}

void UpDownCounter::ButtonStartClicked() {
	ui.txtCounterValue->setText(tr("0"));

	ErrorCode errorCode;
	if (ui.btnStart->text() == "Start") {
		ui.CounterValueList->clear();

		//Set reset times for counter value
		int resetTimes = 0;

		if (ui.radFinite->isChecked()) {
			resetTimes = ui.txtResetTimes->text().toInt();
		} else if (ui.raInfinite->isChecked()) {
			resetTimes = -1;
		} else if (ui.radDisable->isChecked()) {
			resetTimes = 0;
		}

      for (int i = udCounterCtrl->getChannelStart(); i < udCounterCtrl->getChannelStart() + udCounterCtrl->getChannelCount(); i++)
      {
         errorCode = udCounterCtrl->getChannels()->getItem(i).setResetTimesByIndex(resetTimes);
         CheckError(errorCode);
      }
		//set reset value
		Array<int32> * resetValues = udCounterCtrl->getFeatures()->getUdInitialValues();
		int resetValue = resetValues->getItem(ui.cmbResetValue->currentIndex());
		if (resetValue == -1) {
			resetValue = ui.txtResetValue->text().toULong();
		}

		udCounterCtrl->setInitialValue(resetValue);
      for (int i = udCounterCtrl->getChannelStart(); i < udCounterCtrl->getChannelStart() + udCounterCtrl->getChannelCount(); i++)
      {
         errorCode = udCounterCtrl->getChannels()->getItem(i).setInitialValue(resetValue);
         CheckError(errorCode);
      }

		//Start UpDown Counter function.
		errorCode = udCounterCtrl->setEnabled(true);
		CheckError(errorCode);

		timer->start(50);

		ui.btnConfig->setEnabled(false);
		ui.btnStop->setEnabled(true);
		ui.btnValReset->setEnabled(true);
		ui.cmbResetValue->setEnabled(false);
		ui.radDisable->setEnabled(false);
		ui.radFinite->setEnabled(false);
		ui.raInfinite->setEnabled(false);

		ui.btnStart->setText(tr("Latch"));
	} else {
		if (ui.CounterValueList->count() > 12) {
			ui.CounterValueList->takeItem(0);
		} 
		QListWidgetItem* item = NULL;
		item = new QListWidgetItem(QString("%1").arg(cntrValue), ui.CounterValueList);
		item->setTextAlignment(Qt::AlignRight);
	}
}

void UpDownCounter::ButtonStopClicked() {
	//Stop the user Timer
	timer->stop();
	
	ui.btnStart->setText(tr("Start"));
	ui.btnConfig->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnValReset->setEnabled(false);

	ui.cmbResetValue->setEnabled(true);
	ui.radDisable->setEnabled(true);
	ui.radFinite->setEnabled(true);
	ui.raInfinite->setEnabled(true);
	
	ErrorCode errorCode = udCounterCtrl->setEnabled(false);
	CheckError(errorCode);
}

void UpDownCounter::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}

void UpDownCounter::ButtonResetValueClicked() {
	udCounterCtrl->ValueReset();
}

void UpDownCounter::ResetIndexChged(int) {
	if (ui.radDisable->isChecked()) {
		ui.txtResetTimes->setEnabled(false);
	} else if (ui.radFinite->isChecked()) {
		ui.txtResetTimes->setEnabled(true);
		ui.txtResetTimes->setText(tr("1"));
		udCounterCtrl->setResetTimesByIndex(1);
	} else if (ui.raInfinite->isChecked()) {
		ui.txtResetTimes->setEnabled(false);
	}
}

void UpDownCounter::CmbResetValueChanged() {
	Array<int32> * resetValues = udCounterCtrl->getFeatures()->getUdInitialValues();
	int resetValue = resetValues->getItem(ui.cmbResetValue->currentIndex());
	if (resetValue == -1) {
		ui.txtResetValue->setEnabled(true);
	} else {
		ui.txtResetValue->setEnabled(false);
	}
}
