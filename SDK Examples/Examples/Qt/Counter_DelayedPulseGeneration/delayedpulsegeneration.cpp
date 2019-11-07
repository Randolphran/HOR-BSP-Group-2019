#include <QPalette>
#include <QMessageBox>
#include "delayedpulsegeneration.h"

DelayedPulseGeneration::DelayedPulseGeneration(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
	QPixmap pixMap(":/DelayedPulseGeneration/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

	movie = new QMovie(":/DelayedPulseGeneration/Resources/OneShotStatus.gif");
	ui.ExecutionStatus->setMovie(movie);
	movie->start();
	movie->stop();

   oneShotCtrl = OneShotCtrl::Create();
   oneShotCtrl->addOneShotHandler(OnCounterEvent, this);

	DelayedPulseCount = 1000;
   countOfValue = 0;

	ui.clockCountEditor->setText(QString("%1").arg(DelayedPulseCount));
	ui.label_shotCount->setEnabled(false);
	ui.btnStop->setEnabled(false);

    connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
    connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
    connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
    connect(ui.shotCountEditor, SIGNAL(clicked()), this, SLOT(TextCountEdit()));
    connect(this, SIGNAL(DelayCountValue()), this, SLOT(TextDelayCount()));
}

DelayedPulseGeneration::~DelayedPulseGeneration()
{

}

void DelayedPulseGeneration::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Delayed Pulse Generation - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
}

void DelayedPulseGeneration::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

    ErrorCode errorCode = oneShotCtrl->setSelectedDevice(selected);
    CheckError(errorCode);
    errorCode = oneShotCtrl->LoadProfile(configure.profilePath);
    CheckError(errorCode);
    errorCode = oneShotCtrl->setChannelCount(1);
    CheckError(errorCode);
    errorCode = oneShotCtrl->setChannelStart(configure.channel);
    CheckError(errorCode);
}

void DelayedPulseGeneration::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void DelayedPulseGeneration::OnCounterEvent(void *sender, CntrEventArgs *args, void * userParam)
{
   DelayedPulseGeneration * uParam = (DelayedPulseGeneration *)userParam;
   uParam->countOfValue++;
   emit uParam->DelayCountValue();
}
void DelayedPulseGeneration::ButtonStartClicked() {
	this->countOfValue = 0;
	ui.shotCountEditor->setText(tr(""));

	DelayedPulseCount = ui.clockCountEditor->text().toInt();

	ErrorCode errorCode = Success;

   for (int32 i = oneShotCtrl->getChannelStart(); i < oneShotCtrl->getChannelStart() + oneShotCtrl->getChannelCount(); i ++)
   {
      errorCode = oneShotCtrl->getChannels()->getItem(i).setDelayCount(DelayedPulseCount);
      CheckError(errorCode);
   }
	errorCode = oneShotCtrl->setEnabled(true);
	CheckError(errorCode);

	movie->start();

	ui.clockCountEditor->setEnabled(false);
	ui.btnStart->setEnabled(false);
	ui.btnStop->setEnabled(true);
	ui.btnConfig->setEnabled(false);	
}

void DelayedPulseGeneration::ButtonStopClicked() {
	//stop oneShot
	ErrorCode errorCode = Success;
	errorCode = oneShotCtrl->setEnabled(false);
	CheckError(errorCode);

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);
	ui.clockCountEditor->setEnabled(true);

	movie->stop();
}

void DelayedPulseGeneration::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}
}

void DelayedPulseGeneration::TextDelayCount(){
   ui.label_shotCount->setEnabled(true);
   ui.shotCountEditor->setText(QString("%1").arg(countOfValue));
}
