#include <QPalette>
#include <QMessageBox>
#include "pulsewidthmeasurement.h"

PulseWidthMeasurement::PulseWidthMeasurement(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
	QPixmap pixMap(":/PulseWidthMeasurement/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

    pwMeterCtrl = PwMeterCtrl::Create();
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
}

PulseWidthMeasurement::~PulseWidthMeasurement()
{

}

void PulseWidthMeasurement::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Pulse Width Measurement - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

	//initialize ECisRunning and  isPwMeterReset
    ECisRunning = true;
    isPwMeterReset = true;
}

void PulseWidthMeasurement::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

	ErrorCode errorCode = pwMeterCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = pwMeterCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);
    errorCode = pwMeterCtrl->setChannelCount(1);
    CheckError(errorCode);
    errorCode = pwMeterCtrl->setChannelStart(configure.channel);
	CheckError(errorCode);
}

void PulseWidthMeasurement::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}

void PulseWidthMeasurement::TimerTicked() {
	if (ECisRunning == true) {
		//Show event counting value
      PulseWidth pulseWidth;
      pwMeterCtrl->Read(1, &pulseWidth);
      ui.hiPeriodEditor->setText(QString::number(pulseWidth.HiPeriod,'f', 6));
      ui.loPeriodEditor->setText(QString::number(pulseWidth.LoPeriod,'f', 6));
	}
}

void PulseWidthMeasurement::ButtonStartClicked() {
	if (isPwMeterReset == true) {
		ui.cntrValueList->clear();

		//start PwMeter
		ErrorCode errorCode = Success;
		errorCode = pwMeterCtrl->setEnabled(true);
		CheckError(errorCode);

		ECisRunning = true;

		timer->start(50);

		ui.btnStop->setEnabled(true);
		ui.btnStart->setText(tr("Latch"));
		isPwMeterReset = false;
	} else {
		if (ui.cntrValueList->count() > 8) {
			ui.cntrValueList->takeItem(0);
		}

		QListWidgetItem* item = NULL;
		QString str = tr("High:") + ui.hiPeriodEditor->text() + tr("  Low:") + ui.loPeriodEditor->text(); 
		item = new QListWidgetItem(str, ui.cntrValueList);
		item->setTextAlignment(Qt::AlignRight);
	}
	ui.btnConfig->setEnabled(false);
}

void PulseWidthMeasurement::ButtonStopClicked() {
	//Stop event counting
	ErrorCode errorCode = Success;
	errorCode = pwMeterCtrl->setEnabled(false);
	CheckError(errorCode);

	ECisRunning = false;
    isPwMeterReset = true;

	ui.btnStart->setEnabled(true);
	ui.btnStart->setText(tr("Start"));
	ui.btnStop->setEnabled(false);

	if (ECisRunning == false) { 
		timer->stop();
	}

	ui.btnConfig->setEnabled(true);
}

void PulseWidthMeasurement::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}
