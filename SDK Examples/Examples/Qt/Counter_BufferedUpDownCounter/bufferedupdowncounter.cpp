#include <QPalette>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "bufferedupdowncounter.h"

BufferedUpdownCounter::BufferedUpdownCounter(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
    QPixmap pixMap(":/Counter_BufferedUpDownCounter/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

    dataBuf = NULL;
    channelEnable = NULL;
    chs_dataBuf = NULL;
    chs_Status = NULL;

    bfdUdCounterCtrl = BufferedUdCounterCtrl::Create();
    bfdUdCounterCtrl->addDataReadyHandler(OnBfdUdCounterEvent, this);
    bfdUdCounterCtrl->addStoppedHandler(OnBfdUdCounterStoppedEvent, this);

	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
    connect(this, SIGNAL(refreshUI(int)), this, SLOT(onRefreshUI(int)));
    connect(this, SIGNAL(refreshStatus(int)), this, SLOT(onRefreshStatus(int)));
    connect(ui.cbxDisplayedChannel, SIGNAL(currentIndexChanged(int)), this, SLOT(onDisplayedChannelChanged()));
}

BufferedUpdownCounter::~BufferedUpdownCounter()
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
        delete chs_dataBuf;
    }
    if(bfdUdCounterCtrl != NULL){
        bfdUdCounterCtrl->Dispose();
        bfdUdCounterCtrl= NULL;
    }
}

void BufferedUpdownCounter::Initialize() {
	//set the title of the form.
    this->setWindowTitle(tr("Buffered Up Down Counter - Run(") + configure.deviceName + tr(")"));
    ui.txtChannelState->clear();
    ConfigureDevice();
	
	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

    ui.cntrValueList->setEnabled(true);
    ui.txtChannelState->setEnabled(true);

    //initialize ECisRunning
    isRunning = false;
    haveData = false;

    ui.cntrValueList->clear();
}

void BufferedUpdownCounter::ConfigureDevice() {
    ErrorCode errorCode = Success;
    // Setting Device
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
    errorCode = bfdUdCounterCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    //Get Channel Count Max
    channelCountMax = bfdUdCounterCtrl->getFeatures()->getChannelCountMax();
    channelEnable = new int8[channelCountMax];
    memset(channelEnable, 0, sizeof(int8)* channelCountMax);

    chs_Status = new QString[channelCountMax];

    //configure parameters mode (Profile configure/Manual configure)
    if(!configure.configMode){
        errorCode = bfdUdCounterCtrl->LoadProfile(configure.profilePath);
        CheckError(errorCode);
        bfdUdCounterCtrl->getChannelMap(channelCountMax, channelEnable);
        sectionLength = bfdUdCounterCtrl->getRecord()->getSectionLength();
        sectionCount = bfdUdCounterCtrl->getRecord()->getSectionCount();
    }else{
        memcpy(channelEnable, configure.channelEnable, sizeof(int8) * channelCountMax);
        sectionLength = configure.sectionLength;
        sectionCount = configure.sectionCount;

        errorCode = bfdUdCounterCtrl->setChannelMap(channelCountMax,configure.channelEnable);
        CheckError(errorCode);

        errorCode = bfdUdCounterCtrl->setSampleClkSrc(configure.clkSource);
        CheckError(errorCode);

        Record* record = bfdUdCounterCtrl->getRecord();
        errorCode = record->setSectionLength(configure.sectionLength);
        CheckError(errorCode);
        errorCode = record->setSectionCount(configure.sectionCount);
        CheckError(errorCode);

        for(int i = 0; i < channelCountMax; i++){
            if(configure.channelEnable[i] & 0x1){
                errorCode = bfdUdCounterCtrl->getChannels()->getItem(i).setCountingType(configure.cntType);
                CheckError(errorCode);
            }
        }

        Trigger* trigger = bfdUdCounterCtrl->getTrigger();
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
    dataBuf = new int32[samples];
    memset(dataBuf, 0, sizeof(int32) * samples);

    chs_dataBuf = new int32*[channelCountMax];
    for(int i = 0; i < channelCountMax; i++ ){
        chs_dataBuf[i] = new int32[samples];
        memset(chs_dataBuf[i], 0, sizeof(int32) * samples);
    }

    if ((dataBuf == NULL) || (chs_dataBuf == NULL) )
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

void BufferedUpdownCounter::ButtonStartClicked() {
	ErrorCode errorCode = Success;
    ui.cntrValueList->clear();

    // Setting Status is Running.
    for(int i = 0; i < channelCountMax; i++){
       if(channelEnable[i] == 1){
           ChannelStatusStringChange(i, "Running");
       }
    }
    DisplayChannelStatus(displayedChannel);

    errorCode = bfdUdCounterCtrl->Prepare();
    CheckError(errorCode);
    errorCode = bfdUdCounterCtrl->setEnabled(true);
    CheckError(errorCode);
    isRunning = true;
    haveData = true;

    ui.btnStop->setEnabled(true);
    ui.btnStart->setEnabled(false);

	ui.btnConfig->setEnabled(false);
}

void BufferedUpdownCounter::ButtonStopClicked() {
	//Stop event counting
	ErrorCode errorCode = Success;
    errorCode = bfdUdCounterCtrl->setEnabled(false);
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

void BufferedUpdownCounter::ButtonConfigureClicked() {
    configDialog->RefreshConfigureParameter();
    int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
    }
    haveData = false;
}

void BufferedUpdownCounter::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void BufferedUpdownCounter::OnBfdUdCounterEvent(void *sender, BfdCntrEventArgs *args, void *userParam)
{
    ErrorCode ret = Success;
    int32 returnedCount = 0;
    BufferedUpdownCounter* uParam = (BufferedUpdownCounter*)userParam;
    BufferedEventCounterCtrl* ctrl = (BufferedEventCounterCtrl*)sender;
    int32 getDataCount = qMin(args->Count, uParam->samples);
    uParam->eventChannel = args->Channel;
    if(getDataCount){
        ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, &returnedCount, NULL);
        emit uParam->refreshUI(args->Channel);
    }
}

void BufferedUpdownCounter::onRefreshUI(int channel)
{ 
    CopyChannelData(channel);
    if(eventChannel == displayedChannel){
        //display channel value.
        DisplayChannelValue(displayedChannel);
    }
}

void BufferedUpdownCounter::OnBfdUdCounterStoppedEvent(void *sender, BfdCntrEventArgs *args, void *userParam)
{
    ErrorCode ret = Success;
    int32 returnedCount = 0;
    BufferedUpdownCounter* uParam = (BufferedUpdownCounter*)userParam;
    BufferedEventCounterCtrl* ctrl = (BufferedEventCounterCtrl*)sender;
    int32 getDataCount = qMin(args->Count, uParam->samples);
    uParam->eventChannel = args->Channel;
    if(getDataCount > 0){
        ret = ctrl->GetData(args->Channel, getDataCount, uParam->dataBuf, 0, &returnedCount, NULL);
        emit uParam->refreshUI(args->Channel);
    }

    emit uParam->refreshStatus(args->Channel);
}

void BufferedUpdownCounter::onRefreshStatus(int channel)
{
    if(bfdUdCounterCtrl->getState() == Stopped){
        ErrorCode errorCode = bfdUdCounterCtrl->setEnabled(FALSE);
        CheckError(errorCode);
        ui.btnStart->setEnabled(true);
        ui.btnStop->setEnabled(false);
        ui.btnConfig->setEnabled(true);
        isRunning = false;
       }
    ChannelStatusStringChange(channel, "Stopped");
    DisplayChannelStatus(displayedChannel);
}

void BufferedUpdownCounter::onDisplayedChannelChanged()
{
    displayedChannel = ui.cbxDisplayedChannel->currentText().toInt();

    DisplayChannelStatus(displayedChannel);
    DisplayChannelValue(displayedChannel);
}

void BufferedUpdownCounter::ChannelStatusStringChange(int32 channel, QString string)
{
    chs_Status[channel] = string;
}

void BufferedUpdownCounter::DisplayChannelStatus(int channel)
{
    int ch = channel;
    ui.txtChannelState->setText(chs_Status[ch]);
}

void BufferedUpdownCounter::DisplayChannelValue(int channel)
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
    if(haveData || isRunning){
        for(int i = 0; i < listCount; i++){
            item = new QListWidgetItem(QString("%1").arg(chs_dataBuf[ch][i]), ui.cntrValueList);
            item->setTextAlignment(Qt::AlignLeft);
        }
    }
}

void BufferedUpdownCounter::CopyChannelData(int channel)
{
    int ch = channel;
    memcpy(chs_dataBuf[ch], dataBuf, sizeof(int32)*samples);
}
