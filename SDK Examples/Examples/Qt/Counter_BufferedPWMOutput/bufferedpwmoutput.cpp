#include <QPalette>
#include <QMessageBox>
#include "bufferedpwmoutput.h"

BufferedPWMOutput::BufferedPWMOutput(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
    QPixmap pixMap(":/Counter_BufferedPWMOutput/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

    movie = new QMovie(":/Counter_BufferedPWMOutput/Resources/BufferedPwModulatorStatus.gif");
	ui.ExecutionStatus->setMovie(movie);

    channelEnable = NULL;
    pulseWidth = NULL;

    bfdPwModulatorCtrl = BufferedPwModulatorCtrl::Create();
    //bfdPwModulatorCtrl->addDataTransmittedHandler(OnBfdCntrEvent, this);

	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	

    ui.data1_hiPeriodEditor->setText(QString("%1").arg(0.08));
    ui.data1_loPeriodEditor->setText(QString("%1").arg(0.02));

    ui.data2_hiPeriodEditor->setText(QString("%1").arg(0.05));
    ui.data2_loPeriodEditor->setText(QString("%1").arg(0.05));

	movie->start();
	movie->stop();
	
	ui.btnStop->setEnabled(false);
}

BufferedPWMOutput::~BufferedPWMOutput()
{
    if (channelEnable != NULL ){
        delete []channelEnable;
        channelEnable = NULL;
    }
    if(pulseWidth != NULL){
        delete []pulseWidth;
        pulseWidth = NULL;
    }
    if(bfdPwModulatorCtrl != NULL){
        bfdPwModulatorCtrl->Dispose();
        bfdPwModulatorCtrl= NULL;
    }

}

void BufferedPWMOutput::Initialize() {
	//set the title of the form.
    this->setWindowTitle(tr("Buffered PWM Output - Run(") + configure.deviceName + tr(")"));
	ConfigureDevice();
}

void BufferedPWMOutput::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    ErrorCode errorCode = bfdPwModulatorCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
    channelCountMax = bfdPwModulatorCtrl->getFeatures()->getChannelCountMax();
    channelEnable = new int8[channelCountMax];
    memset(channelEnable, 0, sizeof(int8) * channelCountMax);

    if(configure.configMode == ProfileConfigre){
        errorCode = bfdPwModulatorCtrl->LoadProfile(configure.profilePath);
        CheckError(errorCode);
        bfdPwModulatorCtrl->getChannelMap(channelCountMax, channelEnable);
        samples = bfdPwModulatorCtrl->getSamples();
    }else{
        memcpy(channelEnable, configure.channelEnable, sizeof(int8) * channelCountMax);
        errorCode = bfdPwModulatorCtrl->setChannelMap(channelCountMax, configure.channelEnable);
        CheckError(errorCode);
        errorCode = bfdPwModulatorCtrl->setIntervalCount(configure.intervalCount);
        CheckError(errorCode);
        samples = configure.intervalCount * 2;
        errorCode = bfdPwModulatorCtrl->setSamples(samples);
        CheckError(errorCode);
        errorCode = bfdPwModulatorCtrl->setStreaming(true);
        CheckError(errorCode);
        errorCode = bfdPwModulatorCtrl->setSampleClkSrc(configure.clkSource);
        CheckError(errorCode);

        Trigger* trigger = bfdPwModulatorCtrl->getTrigger();
        if(trigger){
            errorCode = trigger->setSource(configure.trgSource);
            CheckError(errorCode);
            errorCode = trigger->setAction(configure.trgAction);
            CheckError(errorCode);
            errorCode = trigger->setEdge(configure.trgEdge);
            CheckError(errorCode);
            errorCode = trigger->setLevel(configure.trgLevel);
            CheckError(errorCode);
        }
    }
}

void BufferedPWMOutput::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void BufferedPWMOutput::ButtonStartClicked() {
    ErrorCode errorCode = Success;
    pulseWidth = new PulseWidth[samples];
    errorCode = bfdPwModulatorCtrl->Prepare();
    CheckError(errorCode);


    //the buffere will be filled with data1 and data2 inturn.
    for(int i = 0; i < samples; i++)
    {
        if((i & 1) == 0){
            //i is an even number
            pulseWidth[i].HiPeriod = ui.data1_hiPeriodEditor->text().toDouble();
            pulseWidth[i].LoPeriod = ui.data1_loPeriodEditor->text().toDouble();
        }else{
            //i is an odd number
            pulseWidth[i].HiPeriod = ui.data2_hiPeriodEditor->text().toDouble();
            pulseWidth[i].LoPeriod = ui.data2_loPeriodEditor->text().toDouble();
        }
    }


    for(int i = 0; i < channelCountMax; i++)
    {
        if(channelEnable[i]){
            errorCode = bfdPwModulatorCtrl->SetData(i, samples, pulseWidth);
            CheckError(errorCode);
        }
    }

     errorCode = bfdPwModulatorCtrl->setEnabled(true);
     CheckError(errorCode);
	 movie->start();

	 ui.btnStart->setEnabled(false);
	 ui.btnStop->setEnabled(true);
	 ui.btnConfig->setEnabled(false);

     ui.data1_hiPeriodEditor->setEnabled(false);
     ui.data1_loPeriodEditor->setEnabled(false);
     ui.data2_hiPeriodEditor->setEnabled(false);
     ui.data2_loPeriodEditor->setEnabled(false);
}

void BufferedPWMOutput::ButtonStopClicked() {
    ErrorCode errorCode = Success;
    errorCode = bfdPwModulatorCtrl->setEnabled(false);
    CheckError(errorCode);

	movie->stop();

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

    ui.data1_hiPeriodEditor->setEnabled(true);
    ui.data1_loPeriodEditor->setEnabled(true);
    ui.data2_hiPeriodEditor->setEnabled(true);
    ui.data2_loPeriodEditor->setEnabled(true);
}

void BufferedPWMOutput::ButtonConfigureClicked() {
    configDialog->RefreshConfigureParameter();
    int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}
