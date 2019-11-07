#include <QPalette>
#include <QMessageBox>
#include "pwmoutput.h"

PWMOutput::PWMOutput(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
	QPixmap pixMap(":/PWMOutput/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

	movie = new QMovie(":/PWMOutput/Resources/PwModulatorStatus.gif");
	ui.ExecutionStatus->setMovie(movie);

   pwModulatorCtrl = PwModulatorCtrl::Create();

	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	

	ui.hiPeriodEditor->setText(QString("%1").arg(0.08));
	ui.loPeriodEditor->setText(QString("%1").arg(0.02));

	movie->start();
	movie->stop();
	
	ui.btnStop->setEnabled(false);
}

PWMOutput::~PWMOutput()
{

}

void PWMOutput::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("PWM Output - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
}

void PWMOutput::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

	ErrorCode errorCode = pwModulatorCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = pwModulatorCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);
    errorCode = pwModulatorCtrl->setChannelCount(1);
	CheckError(errorCode);
    errorCode = pwModulatorCtrl->setChannelStart(configure.channel);
	CheckError(errorCode);
}

void PWMOutput::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void PWMOutput::ButtonStartClicked() {
	 PulseWidth pulseWidth;
	 pulseWidth.HiPeriod = ui.hiPeriodEditor->text().toDouble();
	 pulseWidth.LoPeriod = ui.loPeriodEditor->text().toDouble();

	 //set PulseWidth.
     ErrorCode errorCode = Success;
     for (int i = pwModulatorCtrl->getChannelStart(); i < pwModulatorCtrl->getChannelStart() + pwModulatorCtrl->getChannelCount(); i++)
     {
        errorCode = pwModulatorCtrl->getChannels()->getItem(i).setPulseWidth(pulseWidth);
        CheckError(errorCode);
     }
	 errorCode = pwModulatorCtrl->setEnabled(true);
    CheckError(errorCode);
	 movie->start();

    for (int i = pwModulatorCtrl->getChannelStart(); i < pwModulatorCtrl->getChannelStart() + pwModulatorCtrl->getChannelCount(); i++)
    {
       pwModulatorCtrl->getChannels()->getItem(i).getPulseWidth(pulseWidth);
    }
	 ui.actualHiPeriod->setText(QString("%1").arg(pulseWidth.HiPeriod));
	 ui.actualLoPeriod->setText(QString("%1").arg(pulseWidth.LoPeriod));
	 
	 ui.btnStart->setEnabled(false);
	 ui.btnStop->setEnabled(true);
	 ui.btnConfig->setEnabled(false);

	 ui.hiPeriodEditor->setEnabled(false);
	 ui.loPeriodEditor->setEnabled(false);
}

void PWMOutput::ButtonStopClicked() {
	//stop the PwModulator
   ErrorCode errorCode = Success;
   errorCode = pwModulatorCtrl->setEnabled(false);
   CheckError(errorCode);

	movie->stop();

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

	ui.hiPeriodEditor->setEnabled(true);
	ui.loPeriodEditor->setEnabled(true);
}

void PWMOutput::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}
