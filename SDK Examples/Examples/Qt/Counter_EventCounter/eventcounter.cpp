#include <QPalette>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "eventcounter.h"

EventCounter::EventCounter(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
	QPixmap pixMap(":/EventCounter/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

   eventCounterCtrl = EventCounterCtrl::Create();
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
}

EventCounter::~EventCounter()
{
	
}

void EventCounter::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Event Counter - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
	
	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

	//initialize ECisRunning and  isEventCountingReset
	ECisRunning = true;
    isEventCountingReset = true;
}

void EventCounter::ConfigureDevice() {
	QString deviceDesc = configure.deviceName;
	const wchar_t * description = reinterpret_cast<const wchar_t *>(deviceDesc.utf16());
	DeviceInformation selected(description);
	ErrorCode errorCode = eventCounterCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = eventCounterCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

   errorCode = eventCounterCtrl->setChannelCount(1);
   CheckError(errorCode);
   errorCode = eventCounterCtrl->setChannelStart(configure.channel);
	CheckError(errorCode);
}

void EventCounter::TimerTicked() {
	ui.curValueEditor->setText(QString("%1").arg(eventCounterCtrl->getValue()));
}

void EventCounter::ButtonStartClicked() {
	ErrorCode errorCode = Success;
	if (isEventCountingReset == true) {
		ui.cntrValueList->clear();

		errorCode = eventCounterCtrl->setEnabled(true);
		CheckError(errorCode);
		ECisRunning = true;

		timer->start(50);

		ui.btnStop->setEnabled(true);
		ui.btnStart->setText(tr("Latch"));
		isEventCountingReset = false;
	} else {
		if (ui.cntrValueList->count() > 8) {
			ui.cntrValueList->takeItem(0);
		}
        QListWidgetItem* item = NULL;
		item = new QListWidgetItem(ui.curValueEditor->text(), ui.cntrValueList);
		item->setTextAlignment(Qt::AlignRight);
	}
	ui.btnConfig->setEnabled(false);
}

void EventCounter::ButtonStopClicked() {
	//Stop event counting
	ErrorCode errorCode = Success;
	errorCode = eventCounterCtrl->setEnabled(false);
	CheckError(errorCode);
	ECisRunning = false;

	isEventCountingReset = true;
	ui.btnStart->setEnabled(true);
	ui.btnStart->setText(tr("Start"));
	ui.btnStop->setEnabled(false);

	//stop the timer
    if (ECisRunning == false) {
		timer->stop();
	}
	ui.btnConfig->setEnabled(true);
}

void EventCounter::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}

void EventCounter::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}
