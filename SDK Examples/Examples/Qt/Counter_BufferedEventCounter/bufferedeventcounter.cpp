#include <QPalette>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "bufferedeventcounter.h"

BufferedEventCounter::BufferedEventCounter(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
    QPixmap pixMap(":/BufferedEventCounter/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

    dataBuf = NULL;
    channelEnable = NULL;
    chs_dataBuf = NULL;
    chs_Status = NULL;

    bfdEventCounterCtrl = BufferedEventCounterCtrl::Create();
    bfdEventCounterCtrl->addDataReadyHandler(OnBfdEventCounterEvent, this);
    bfdEventCounterCtrl->addStoppedHandler(OnBfdEventCounterStoppedEvent, this);

	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
    connect(this, SIGNAL(refreshUI(int)), this, SLOT(onRefreshUI(int)));
    connect(this, SIGNAL(refreshStatus(int)), this, SLOT(onRefreshStatus(int)));
    connect(ui.cbxDisplayedChannel, SIGNAL(currentIndexChanged(int)), this, SLOT(onDisplayedChannelChanged()));
}

BufferedEventCounter::~BufferedEventCounter()
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
    if(bfdEventCounterCtrl != NULL){
        bfdEventCounterCtrl->Dispose();
        bfdEventCounterCtrl= NULL;
    }
}

void BufferedEventCounter::Initialize() {
	//set the title of the form.
    this->setWindowTitle(tr("Buffered Event Counter - Run(") + configure.deviceName + tr(")"));
    ui.txtChannelState->clear();

	ConfigureDevice();
	
	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

    ui.cntrValueList->setEnabled(true);
    ui.txtChannelState->setEnabled(true);

    //initialize ECisRunning
    BFDECisRunning = false;
    haveData = false;

    ui.cntrValueList->clear();
}

void BufferedEventCounter::ConfigureDevice() {
    ErrorCode errorCode = Success;

    // Setting Device
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    errorCode = bfdEventCounterCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    //Get Channel Count Max
    channelCountMax = bfdEventCounterCtrl->getFeatures()->getChannelCountMax();
    channelEnable = new int8[channelCountMax];
    memset(channelEnable, 0, sizeof(int8)* channelCountMax);

    chs_Status = new QString[channelCountMax];

    //configure parameters mode (Profile configure/Manual configure)
    if(!configure.configMode){
        errorCode = bfdEventCounterCtrl->LoadProfile(configure.profilePath);
        CheckError(errorCode);
        bfdEventCounterCtrl->getChannelMap(channelCountMax, channelEnable);
        sectionLength = bfdEventCounterCtrl->getRecord()->getSectionLength();
        sectionCount = bfdEventCounterCtrl->getRecord()->getSectionCount();
    }else{
        memcpy(channelEnable, configure.channelEnable, sizeof(int8) * channelCountMax);
        sectionLength = configure.sectionLength;
        sectionCount = configure.sectionCount;

        errorCode = bfdEventCounterCtrl->setChannelMap(channelCountMax,configure.channelEnable);
        CheckError(errorCode);

        errorCode = bfdEventCounterCtrl->setSampleClkSrc(configure.clkSource);
        CheckError(errorCode);

        Record* record = bfdEventCounterCtrl->getRecord();
        errorCode = record->setSectionLength(configure.sectionLength);
        CheckError(errorCode);
        errorCode = record->setSectionCount(configure.sectionCount);
        CheckError(errorCode);

        Trigger* trigger = bfdEventCounterCtrl->getTrigger();
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
       samples *= sectionCount;
    }
    dataBuf = new int32[samples];
    memset(dataBuf, 0, sizeof(int32) * samples);

    chs_dataBuf = new int32*[channelCountMax];
    for(int i = 0; i < channelCountMax; i++ ){
        chs_dataBuf[i] = new int32[samples];
        memset(chs_dataBuf[i], 0, sizeof(int32) * samples);
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

void BufferedEventCounter::ButtonStartClicked() {
	ErrorCode errorCode = Success;
    ui.cntrValueList->clear();

    // Setting Status is Running.
    for(int i = 0; i < channelCountMax; i++){
       if(channelEnable[i] == 1){
           ChannelStatusStringChange(i, "Running");
       }
    }
    DisplayChannelStatus(displayedChannel);

    errorCode = bfdEventCounterCtrl->Prepare();
    CheckError(errorCode);
    errorCode = bfdEventCounterCtrl->setEnabled(true);
    CheckError(errorCode);
    BFDECisRunning = true;
    haveData = true;

    ui.btnStop->setEnabled(true);
    ui.btnStart->setEnabled(false);

	ui.btnConfig->setEnabled(false);
}

void BufferedEventCounter::ButtonStopClicked() {
	//Stop event counting
	ErrorCode errorCode = Success;
    errorCode = bfdEventCounterCtrl->setEnabled(false);
	CheckError(errorCode);
    BFDECisRunning = false;
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

void BufferedEventCounter::ButtonConfigureClicked() {
    configDialog->RefreshConfigureParameter();
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
    haveData = false;
}

void BufferedEventCounter::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void BufferedEventCounter::OnBfdEventCounterEvent(void *sender, BfdCntrEventArgs *args, void *userParam)
{
    ErrorCode ret = Success;
    int32 returnedCount = 0;
    BufferedEventCounter* uParam = (BufferedEventCounter*)userParam;
    BufferedEventCounterCtrl* ctrl = (BufferedEventCounterCtrl*)sender;
    int32 getDataCount = qMin(args->Count, uParam->samples);
    uParam->eventChannel = args->Channel;
    if(getDataCount){
        ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, &returnedCount, NULL);
    }
    emit uParam->refreshUI(args->Channel);
}

void BufferedEventCounter::onRefreshUI(int channel)
{ 
    CopyChannelData(channel);
    if(channel == displayedChannel){
        //display channel value.
        DisplayChannelValue(displayedChannel);
    }
}

void BufferedEventCounter::OnBfdEventCounterStoppedEvent(void *sender, BfdCntrEventArgs *args, void *userParam)
{
    ErrorCode ret = Success;
    int32 returnedCount = 0;
    BufferedEventCounter* uParam = (BufferedEventCounter*)userParam;
    BufferedEventCounterCtrl* ctrl = (BufferedEventCounterCtrl*)sender;
    int32 getDataCount = qMin(args->Count, uParam->samples);
    uParam->eventChannel = args->Channel;
    if(getDataCount){
        ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, &returnedCount, NULL);
        emit uParam->refreshUI(args->Channel);
    }

    emit uParam->refreshStatus(args->Channel);
}

void BufferedEventCounter::onRefreshStatus(int channel)
{
    if(bfdEventCounterCtrl->getState() == Stopped){
        ErrorCode errorCode = bfdEventCounterCtrl->setEnabled(FALSE);
        CheckError(errorCode);
        ui.btnStart->setEnabled(true);
        ui.btnStop->setEnabled(false);
        ui.btnConfig->setEnabled(true);
        BFDECisRunning = false;
       }
    ChannelStatusStringChange(channel, "Stopped");
    DisplayChannelStatus(displayedChannel);
}

void BufferedEventCounter::onDisplayedChannelChanged()
{
    displayedChannel = ui.cbxDisplayedChannel->currentText().toInt();

    DisplayChannelStatus(displayedChannel);
    DisplayChannelValue(displayedChannel);
}

void BufferedEventCounter::ChannelStatusStringChange(int32 channel, QString string)
{
    chs_Status[channel] = string;
}

void BufferedEventCounter::DisplayChannelStatus(int channel)
{
    int ch = channel;
    ui.txtChannelState->setText(chs_Status[ch]);
}

void BufferedEventCounter::DisplayChannelValue(int channel)
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
    if(haveData || BFDECisRunning){
        for(int i = 0; i < listCount; i++){
            item = new QListWidgetItem(QString("%1").arg(chs_dataBuf[ch][i]), ui.cntrValueList);
            item->setTextAlignment(Qt::AlignLeft);
        }
    }   
}

void BufferedEventCounter::CopyChannelData(int channel)
{
    int ch = channel;
    memcpy(chs_dataBuf[ch], dataBuf, sizeof(uint32)*samples);
}
