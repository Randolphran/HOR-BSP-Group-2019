#include <QPalette>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "bufferedpulsewidthmeasurement.h"

BufferedPulseWidthMeasurement::BufferedPulseWidthMeasurement(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
    QPixmap pixMap(":/Counter_BufferedPulseWidthMeasurement/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

    dataBuf = NULL;
    chs_dataBuf = NULL;
    chs_Status = NULL;

    bfdPwMeterCtrl = BufferedPwMeterCtrl::Create();
    bfdPwMeterCtrl->addDataReadyHandler(OnBfdPwMeterEvent, this);
    bfdPwMeterCtrl->addStoppedHandler(OnBfdPWMeterStoppedEvent, this);

	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
    connect(this, SIGNAL(refreshUI(int)), this, SLOT(onRefreshUI(int)));
    connect(this, SIGNAL(refreshStatus(int)), this, SLOT(onRefreshStatus(int)));
    connect(ui.cbxDisplayedChannel, SIGNAL(currentIndexChanged(int)), this, SLOT(onDisplayedChannelChanged()));
}

BufferedPulseWidthMeasurement::~BufferedPulseWidthMeasurement()
{
    if(dataBuf != NULL){
        delete[]dataBuf;
        dataBuf = NULL;
    }
    if (channelEnable != NULL ){
        delete []channelEnable;
        channelEnable = NULL;
    }
    if(chs_Status != NULL){
        delete []chs_Status;
        chs_Status = NULL;
    }
    if(chs_dataBuf != NULL){
        for(int i = 0; i < channelCountMax; i++){
            if(chs_dataBuf[i] != NULL)
            delete []chs_dataBuf[i];
        }
        chs_dataBuf = NULL;
    }
    if(bfdPwMeterCtrl != NULL){
        bfdPwMeterCtrl->Dispose();
        bfdPwMeterCtrl= NULL;
    }
}

void BufferedPulseWidthMeasurement::Initialize() {
	//set the title of the form.
    this->setWindowTitle(tr("Buffered Pulse Width Measurement - Run(") + configure.deviceName + tr(")"));
    ui.txtChannelState->clear();
	ConfigureDevice();
	
	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

    ui.cntrValueList->setEnabled(true);
    ui.txtChannelState->setEnabled(true);

    //initialize isRunning
    isRunning = false;
    haveData = false;

    ui.cntrValueList->clear();
}

void BufferedPulseWidthMeasurement::ConfigureDevice() {
    ErrorCode errorCode = Success;
    // Setting Device
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    errorCode = bfdPwMeterCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    //Get Channel Count Max
    channelCountMax = bfdPwMeterCtrl->getFeatures()->getChannelCountMax();
    channelEnable = new int8[channelCountMax];
    memset(channelEnable, 0, sizeof(int8)* channelCountMax);

    chs_Status = new QString[channelCountMax];

    //configure parameters mode (Profile configure/Manual configure)
    if(!configure.configMode){
        errorCode = bfdPwMeterCtrl->LoadProfile(configure.profilePath);
        CheckError(errorCode);
        bfdPwMeterCtrl->getChannelMap(channelCountMax, channelEnable);
        sectionLength = bfdPwMeterCtrl->getRecord()->getSectionLength();
        sectionCount = bfdPwMeterCtrl->getRecord()->getSectionCount();
    }else{
        memcpy(channelEnable, configure.channelEnable, sizeof(int8) * channelCountMax);
        sectionLength = configure.sectionLength;
        sectionCount = configure.sectionCount;

        errorCode = bfdPwMeterCtrl->setChannelMap(channelCountMax,configure.channelEnable);
        CheckError(errorCode);

        errorCode = bfdPwMeterCtrl->setSampleClkSrc(configure.clkSource);
        CheckError(errorCode);

        Record* record = bfdPwMeterCtrl->getRecord();
        errorCode = record->setSectionLength(configure.sectionLength);
        CheckError(errorCode);
        errorCode = record->setSectionCount(configure.sectionCount);
        CheckError(errorCode);

        Trigger* trigger = bfdPwMeterCtrl->getTrigger();
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

    samples = sectionLength;
    if(sectionCount){
        samples *= configure.sectionCount;
    }
    dataBuf = new PulseWidth[samples];
    memset(dataBuf, 0, sizeof(PulseWidth) * samples);

    chs_dataBuf = new PulseWidth*[channelCountMax];
    for(int i = 0; i < channelCountMax; i++ ){
        chs_dataBuf[i] = new PulseWidth[samples];
        memset(chs_dataBuf[i], 0, sizeof(PulseWidth) * samples);
    }

    if ((dataBuf == NULL) || (chs_dataBuf == NULL))
    {
        QMessageBox::information(this, tr("Warning Information"),
            tr("Sorry! Error in allocating memory...."));
        return;
    }

    ui.cbxDisplayedChannel->clear();
    //enum enabled channels
    for(int i = 0; i < channelCountMax; i++){
        if(channelEnable[i] & 0x1){
            ui.cbxDisplayedChannel->addItem(QString("%1").arg(i));
        }
    }
    ui.cbxDisplayedChannel->setCurrentIndex(0);

    // Setting Status is Ready.
    for(int i = 0; i < channelCountMax; i++){
       if(channelEnable[i] == 1){
           ChannelStatusStringChange(i, "Ready");
       }
    }
    displayedChannel = ui.cbxDisplayedChannel->currentText().toInt();
    DisplayChannelStatus(displayedChannel);
}

void BufferedPulseWidthMeasurement::ButtonStartClicked() {
	ErrorCode errorCode = Success;
    ui.cntrValueList->clear();

    // Setting Status is Running.
    for(int i = 0; i < channelCountMax; i++){
       if(channelEnable[i] == 1){
           ChannelStatusStringChange(i, "Running");
       }
    }
    DisplayChannelStatus(displayedChannel);

    errorCode = bfdPwMeterCtrl->Prepare();
    CheckError(errorCode);
    errorCode = bfdPwMeterCtrl->setEnabled(true);
    CheckError(errorCode);
    isRunning = true;
    haveData = true;
    ui.btnStop->setEnabled(true);
    ui.btnStart->setEnabled(false);

	ui.btnConfig->setEnabled(false);
}

void BufferedPulseWidthMeasurement::ButtonStopClicked() {
	//Stop event counting
	ErrorCode errorCode = Success;
    errorCode = bfdPwMeterCtrl->setEnabled(false);
	CheckError(errorCode);
    isRunning = false;

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

    for(int i = 0; i < channelCountMax; i++){
       if(channelEnable[i] == 1){
           ChannelStatusStringChange(i, "Stopped");
       }
    }
    DisplayChannelStatus(displayedChannel);
}

void BufferedPulseWidthMeasurement::ButtonConfigureClicked() {
    configDialog->RefreshConfigureParameter();
    int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
    haveData = false;
}

void BufferedPulseWidthMeasurement::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void BufferedPulseWidthMeasurement::OnBfdPwMeterEvent(void *sender, BfdCntrEventArgs *args, void *userParam)
{
    ErrorCode ret = Success;
    int32 returnedCount = 0;
    BufferedPulseWidthMeasurement* uParam = (BufferedPulseWidthMeasurement*)userParam;
    BufferedPwMeterCtrl* ctrl = (BufferedPwMeterCtrl*)sender;
    int32 getDataCount = qMin(args->Count, uParam->samples);
    uParam->eventChannel = args->Channel;
    if(getDataCount){
        ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, &returnedCount, NULL);
        emit uParam->refreshUI(args->Channel);
    }
}

void BufferedPulseWidthMeasurement::onRefreshUI(int channel)
{ 
    CopyChannelData(channel);
    if(channel == displayedChannel){
        //display channel value.
        DisplayChannelValue(displayedChannel);
    }
}

void BufferedPulseWidthMeasurement::OnBfdPWMeterStoppedEvent(void *sender, BfdCntrEventArgs *args, void *userParam)
{
    ErrorCode ret = Success;
    int32 returnedCount = 0;
    BufferedPulseWidthMeasurement* uParam = (BufferedPulseWidthMeasurement*)userParam;
    BufferedPwMeterCtrl* ctrl = (BufferedPwMeterCtrl*)sender;
    int32 getDataCount = qMin(args->Count, uParam->samples);
    uParam->eventChannel = args->Channel;
    if(getDataCount > 0){
        ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, &returnedCount, NULL);
        emit uParam->refreshUI(args->Channel);
    }
    emit uParam->refreshStatus(args->Channel);
}

void BufferedPulseWidthMeasurement::onRefreshStatus(int channel)
{
    if(bfdPwMeterCtrl->getState() == Stopped){
        ErrorCode errorCode = bfdPwMeterCtrl->setEnabled(FALSE);
        CheckError(errorCode);
        ui.btnStart->setEnabled(true);
        ui.btnStop->setEnabled(false);
        ui.btnConfig->setEnabled(true);
        isRunning = false;
       }
    ChannelStatusStringChange(channel, "Stopped");
    DisplayChannelStatus(displayedChannel);
}

void BufferedPulseWidthMeasurement::onDisplayedChannelChanged()
{
    displayedChannel = ui.cbxDisplayedChannel->currentText().toInt();

    DisplayChannelStatus(displayedChannel);
    DisplayChannelValue(displayedChannel);
}

void BufferedPulseWidthMeasurement::ChannelStatusStringChange(int32 channel, QString string)
{
    chs_Status[channel] = string;
}

void BufferedPulseWidthMeasurement::DisplayChannelStatus(int channel)
{
    int ch = channel;
    ui.txtChannelState->setText(chs_Status[ch]);
}

void BufferedPulseWidthMeasurement::DisplayChannelValue(int channel)
{
    int ch = channel;
    ui.cntrValueList->clear();

    int listCount = 0;
    if(sectionLength >= 10){
        listCount = 10;
    }else{
        listCount = sectionLength;
    }

    QListWidgetItem* item = NULL;
    for(int i = 0; i < listCount; i++){
        QString str = tr("High:") + QString::number(chs_dataBuf[ch][i].HiPeriod,'f', 6) + tr(" s  Low:") + QString::number(chs_dataBuf[ch][i].LoPeriod,'f', 6) + tr(" s");
        item = new QListWidgetItem(str, ui.cntrValueList);
        item->setTextAlignment(Qt::AlignLeft);
    }
}

void BufferedPulseWidthMeasurement::CopyChannelData(int channel)
{
    int ch = channel;
    memcpy(chs_dataBuf[ch], dataBuf, sizeof(PulseWidth)*samples);
}
