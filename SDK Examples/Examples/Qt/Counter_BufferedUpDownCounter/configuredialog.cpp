#include "configuredialog.h"
#include <QMessageBox>
#include <QtDebug>
#include <QProcess>
#include <QFileDialog>

ConfigureDialog::ConfigureDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

    connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged()));
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));
	connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(ButtonBrowseClicked()));
    connect(ui.cbxTrgSource, SIGNAL(currentIndexChanged(int)), this, SLOT(TrgSourceChanged()));
    connect(ui.radBtn_LoadProfile, SIGNAL(clicked()), this, SLOT(onLoadProfileClicked()));
    connect(ui.radBtn_ManualConfig, SIGNAL(clicked()), this, SLOT(onManualConfigureClicked()));
    ui.txtTrgLevel->setValidator(new QDoubleValidator(-10.0, 10.0, 10, this));
	Initailization();
}

ConfigureDialog::~ConfigureDialog()
{
    m_bfdUdCounterCtrl->Dispose();
    m_bfdUdCounterCtrl = NULL;
}

void ConfigureDialog::Initailization()
{
    m_bfdUdCounterCtrl = BufferedUdCounterCtrl::Create();
    Array<DeviceTreeNode> *supportedDevices = m_bfdUdCounterCtrl->getSupportedDevices();

	if (supportedDevices->getCount() == 0){
		QMessageBox::information(this, tr("Warning Information"), 
			tr("No device to support the currently demonstrated function!"));
		QCoreApplication::quit();
	} else {
		for (int i = 0; i < supportedDevices->getCount(); i++) {
			DeviceTreeNode const &node = supportedDevices->getItem(i);
			qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
			ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
		}
		ui.cmbDevice->setCurrentIndex(0);	
	}
	configure.profilePath = L"";
	supportedDevices->Dispose();

    ui.radBtn_ManualConfig->setChecked(true);
    ui.groupBox_profile->setEnabled(false);
    ui.groupBox_manual->setEnabled(true);
}

void ConfigureDialog::CheckError(ErrorCode errorCode)
{
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void ConfigureDialog::DeviceChanged()
{
    ui.cbxSampleClkSrc->clear();
    ui.cbxTrgAction->clear();
    ui.cbxTrgEdge->clear();
    ui.cbxTrgSource->blockSignals(true);
    ui.cbxTrgSource->clear();
    ui.cbxTrgSource->blockSignals(false);


    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    ErrorCode errorCode = m_bfdUdCounterCtrl->setSelectedDevice(selected);
	ui.btnOK->setEnabled(true);

    if (errorCode != Success) {
        QString str;
        QString des = QString::fromStdWString(description);
        str.sprintf("Error:the error code is 0x%x\nThe %s is busy or not exit in computer now.\nSelect other device please!", errorCode, des.toUtf8().data());
        QMessageBox::information(this, "Warning Information", str);
        ui.btnOK->setEnabled(false);
        return;
    }

    //configure CheckBox for ChannelMap
    Max_Channel_Count = m_bfdUdCounterCtrl->getFeatures()->getChannelCountMax();
    configure.channelEnable = new int8[Max_Channel_Count];
    memset(configure.channelEnable, 0, sizeof(int8) * Max_Channel_Count);
    InitialChannelCheckBox();

    //Set Sample Clock Source combo box
    CounterClockSourceIndexer* indexer = m_bfdUdCounterCtrl->getFeatures()->getUdSampleClockSources();
    for(int i = 0; i < indexer->getItem(0)->getCount(); i++)
    {
        SignalDrop clkSrc = indexer->getItem(0)->getItem(i);
        wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
        errorCode = AdxEnumToString(L"SignalDrop", clkSrc, MAX_SIG_DROP_DESC_LEN, enumStr);
        CheckError(errorCode);
        ui.cbxSampleClkSrc->addItem(QString::fromWCharArray(enumStr));
    }
    ui.cbxSampleClkSrc->setCurrentIndex(0);

    // Set Counting type for selected device
    int cntTypeCount = m_bfdUdCounterCtrl->getFeatures()->getUdCountingTypes()->getCount();
    Array<CountingType> * counttingType = m_bfdUdCounterCtrl->getFeatures()->getUdCountingTypes();

    wchar_t strType[32] = {0};
    for (int i = 0; i < cntTypeCount; ++i) {
        AdxEnumToString(L"CountingType",counttingType->getItem(i),32,strType);
        ui.cbxCountingType->addItem(QString::fromWCharArray(strType));
    }
    ui.cbxCountingType->setCurrentIndex(0);

    //Set trigger function layout
    Array<SignalDrop>* trgSrc = m_bfdUdCounterCtrl->getFeatures()->getTriggerSources();
    for(int i = 0; i < trgSrc->getCount(); i++)
    {
        wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
        errorCode = AdxEnumToString(L"SignalDrop", trgSrc->getItem(i), MAX_SIG_DROP_DESC_LEN, enumStr);
        CheckError(errorCode);
        ui.cbxTrgSource->addItem(QString::fromWCharArray(enumStr));
    }
    ui.cbxTrgSource->setCurrentIndex(0);

    Array<TriggerAction>* trgAct = m_bfdUdCounterCtrl->getFeatures()->getTriggerActions();
    for(int i = 0; i < trgAct->getCount(); i++)
    {
        wchar_t enumStr[MAX_SIG_DROP_DESC_LEN];
        errorCode = AdxEnumToString(L"TriggerAction", trgAct->getItem(i), MAX_SIG_DROP_DESC_LEN, enumStr);
        CheckError(errorCode);
        ui.cbxTrgAction->addItem(QString::fromWCharArray(enumStr));
    }
    ui.cbxTrgAction->setCurrentIndex(0);

    ui.cbxTrgEdge->addItem(QString::fromWCharArray(L"RisingEdge"));
    ui.cbxTrgEdge->addItem(QString::fromWCharArray(L"FallingEdge"));
    ui.cbxTrgEdge->setCurrentIndex(0);
}

void ConfigureDialog::ButtonOKClicked()
{
    if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

    if(ui.radBtn_LoadProfile->isChecked()){
        if(ui.txtProfilePath->text().isEmpty()){
            ui.btnOK->setEnabled(false);
            QString message = tr("Sorry, profile path is null, please select the device's profile");
            QMessageBox::information(this, "Warning Information", message);
        }else{
            configure.configMode = ProfileConfigre;
            configure.deviceName = ui.cmbDevice->currentText();
            this->accept();
        }
    }else{
        configure.deviceName = ui.cmbDevice->currentText();
        configure.sectionLength = ui.txtSectionLength->text().toInt();
        configure.sectionCount = ui.txtSectionCount->text().toInt();

        CounterClockSourceIndexer* indexer = m_bfdUdCounterCtrl->getFeatures()->getUdSampleClockSources();
        configure.clkSource = indexer->getItem(0)->getItem(ui.cbxSampleClkSrc->currentIndex());

        Array<CountingType> * countingType = m_bfdUdCounterCtrl->getFeatures()->getUdCountingTypes();
        configure.cntType = countingType->getItem(ui.cbxCountingType->currentIndex());

        Array<SignalDrop>*  sources = m_bfdUdCounterCtrl->getFeatures()->getTriggerSources();
        configure.trgSource = sources->getItem(ui.cbxTrgSource->currentIndex());
        configure.trgAction = DelayToStart;
        if (ui.cbxTrgEdge->currentIndex() == 0) {
             configure.trgEdge = RisingEdge;
        } else {
            configure.trgEdge = FallingEdge;
        }
        configure.trgLevel = ui.txtTrgLevel->text().toDouble();
        configure.configMode = ManualConfigure;

        // check no channel been enabled.
        int sum = 0;
        for(int i = 0; i < Max_Channel_Count; i++){
            sum += configure.channelEnable[i];
        }

        // if the sum is no-zero value, that mean at least one channel been enabled .
        if(sum){
         this->accept();
        }else{
            QString message = tr("Please enable at least one channel!");
            QMessageBox::information(this, "Warning Information", message);
        }
    }
}

void ConfigureDialog::ButtonCancelClicked()
{
	this->reject();
}

void ConfigureDialog::ButtonBrowseClicked()
{
	QString str = QFileDialog::getOpenFileName(this, tr("Open Profile"), "../../profile", tr("Image Files(*.xml)")); 
	ui.txtProfilePath->setText(str);
    configure.profilePath = reinterpret_cast<const wchar_t *>(str.utf16());
    ui.btnOK->setEnabled(true);
}

void ConfigureDialog::TrgSourceChanged()
{
    Array<SignalDrop>*  sources = m_bfdUdCounterCtrl->getFeatures()->getTriggerSources();
    SignalDrop trgSrc = sources->getItem(ui.cbxTrgSource->currentIndex());

    switch(trgSrc)
    {
    case SignalNone:
        ui.cbxTrgAction->setEnabled(false);
        ui.cbxTrgEdge->setEnabled(false);
        ui.txtTrgLevel->setEnabled(false);
        break;
    case SigDiPatternMatch:
    case SigDiStatusChange:
        ui.cbxTrgAction->setEnabled(true);
        ui.cbxTrgEdge->setEnabled(false);
        ui.txtTrgLevel->setEnabled(false);
        break;
    default:
        ui.cbxTrgAction->setEnabled(true);
        ui.cbxTrgEdge->setEnabled(true);
        ui.txtTrgLevel->setEnabled(true);
        break;
    }
}

void ConfigureDialog::onLoadProfileClicked()
{
    ui.groupBox_profile->setEnabled(true);
    ui.groupBox_manual->setEnabled(false);
}

void ConfigureDialog::onManualConfigureClicked()
{
    ui.groupBox_profile->setEnabled(false);
    ui.groupBox_manual->setEnabled(true);
}

void ConfigureDialog::InitialChannelCheckBox()
{
    ui.scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    ui.scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.scrollArea->setWidgetResizable(false);

    QList<QCheckBox*> chkBoxs = ui.areaWidget->findChildren<QCheckBox*>();
    foreach (QCheckBox* chkBox, chkBoxs) {   delete chkBox;  }

    QString str("CH%1");
    for(int i = 0; i < Max_Channel_Count; i++){
        QCheckBox* chkBox = new QCheckBox(str.arg(i), ui.areaWidget);
        chkBox->setObjectName(QString::number(i));
        chkBox->setMinimumSize(chkBox->size());
        ui.horizontalLayout->addWidget(chkBox);

        connect(chkBox, SIGNAL(clicked(bool)), this, SLOT(onChannelChecked(bool)));
    }
}

void ConfigureDialog::onChannelChecked(bool isChecked)
{
    QString objName = sender()->objectName();
    configure.channelEnable[objName.toInt()] = (uint8) isChecked;
}

void ConfigureDialog::RefreshConfigureParameter()
{
    ui.txtSectionLength->setText(QString::number(m_bfdUdCounterCtrl->getRecord()->getSectionLength()));
    ui.txtSectionCount->setText(QString::number(m_bfdUdCounterCtrl->getRecord()->getSectionCount()));

    SignalDrop clkSrc = m_bfdUdCounterCtrl->getSampleClkSrc();
    CounterClockSourceIndexer* indexer = m_bfdUdCounterCtrl->getFeatures()->getEcSampleClockSources();
    for(int i = 0; i < indexer->getItem(0)->getCount(); i++){
        if(clkSrc == indexer->getItem(0)->getItem(i)){
            ui.cbxSampleClkSrc->setCurrentIndex(i);
            break;
        }
    }

    CountingType countingType = m_bfdUdCounterCtrl->getChannels()->getItem(0).getCountingType();
    Array<CountingType> * type = m_bfdUdCounterCtrl->getFeatures()->getUdCountingTypes();
    for(int i = 0; i < type->getCount(); i++){
        if(countingType == type->getItem(i)){
            ui.cbxCountingType->setCurrentIndex(i);
            break;
        }
    }

    SignalDrop trgSrc = m_bfdUdCounterCtrl->getTrigger()->getSource();
    Array<SignalDrop>*  sources = m_bfdUdCounterCtrl->getFeatures()->getTriggerSources();
    for(int i = 0; i < sources->getCount(); i++){
        if(trgSrc == sources->getItem(i)){
            ui.cbxTrgSource->setCurrentIndex(i);
            break;
        }
    }

    TriggerAction trgAction = m_bfdUdCounterCtrl->getTrigger()->getAction();
    Array<TriggerAction>* action = m_bfdUdCounterCtrl->getFeatures()->getTriggerActions();
    for(int i = 0; i < action->getCount(); i++){
        if(trgAction == action->getItem(i)){
            ui.cbxTrgAction->setCurrentIndex(i);
            break;
        }
    }

    ActiveSignal trgEdge = m_bfdUdCounterCtrl->getTrigger()->getEdge();
    int index = -1;
    trgEdge == RisingEdge ? (index = 0) : (index = 1);
    ui.cbxTrgEdge->setCurrentIndex(index);

    ui.txtTrgLevel->setText(QString::number(m_bfdUdCounterCtrl->getTrigger()->getLevel(), 'f',0.0));

    m_bfdUdCounterCtrl->getChannelMap(Max_Channel_Count, configure.channelEnable);
    for(int i = 0; i < Max_Channel_Count; i++) {
        QCheckBox* chkBox = ui.areaWidget->findChild<QCheckBox *>(QString::number(i));
        if(!chkBox) continue;

        if(configure.channelEnable[i]){
            chkBox->setCheckState(Qt::Checked);
        }else{
            chkBox->setCheckState(Qt::Unchecked);
        }
    }
}
