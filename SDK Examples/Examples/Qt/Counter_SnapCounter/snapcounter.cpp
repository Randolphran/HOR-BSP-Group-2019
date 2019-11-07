#include <QMessageBox>
#include "snapcounter.h"

SnapCounter::SnapCounter(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

   udCounterCtrl = UdCounterCtrl::Create();
   udCounterCtrl->addUdCntrEventHandler(OnCounterEvent, this);
	timer = new QTimer(this);

	ui.txtTimeInterval->setValidator(new QDoubleValidator(0.02, 50000, 2));

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
	connect(ui.listSnapSource, SIGNAL(itemSelectionChanged ()), this, SLOT(SnapSrcSelChanged()));
}

SnapCounter::~SnapCounter()
{
	udCounterCtrl->Dispose();
}

void SnapCounter::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Snap Counter - Run(") + configure.deviceName + tr(")"));	

	ui.txtTimeInterval->setText(tr("5"));
	ui.CounterValueList->clear();
	m_isTimerUsing = false;

	ConfigureDevice();
	ConfiguratePanel();

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);
}

void SnapCounter::ConfigureDevice() {
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

void SnapCounter::ConfiguratePanel() {
	//for reset value
   Array<EventId> * snapSrcs = udCounterCtrl->getFeatures()->getUdSnapEventSources();

	int srcCount = snapSrcs->getCount();
	QString srcSrc;
	ui.listSnapSource->clear();
	for (int i = 0; i < srcCount; i++) {
		EventIDtoString((EventId)snapSrcs->getItem(i), srcSrc);
		QListWidgetItem * item = new  QListWidgetItem();
		item->setData(0, srcSrc);
		item->setData(32, (EventId)snapSrcs->getItem(i));
		ui.listSnapSource->addItem(item);
	}
}

void SnapCounter::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void SnapCounter::ButtonStartClicked() {
	ErrorCode errorCode;
	ui.CounterValueList->clear();
	ui.txtCounterValue->setText(tr("0"));
	ui.txtSnapCount->setText(tr("0"));
   
   m_snapCount = 0;

	aryListBoxSrcSel.clear();
	m_isTimerUsing = false;

	EventId item;
	int timerChan = -1;
	aryListBoxSrcSel = ui.listSnapSource->selectedItems();
	int snapSrcCount = aryListBoxSrcSel.count();
	for (int i = 0; i < snapSrcCount; i++) {
		item = (EventId)aryListBoxSrcSel.at(i)->data(32).toInt();
		CheckTimerUsingParam(item, timerChan, m_isTimerUsing);
      udCounterCtrl->SnapStart(item);

	}

	if (m_isTimerUsing) {
		ErrorCode errorCode;
        m_timerPulseCtrl = TimerPulseCtrl::Create();

        std::wstring description = configure.deviceName.toStdWString();
        DeviceInformation selected(description.c_str());

		errorCode = m_timerPulseCtrl->setSelectedDevice(selected);
		CheckError(errorCode);

		double frequency = ui.txtTimeInterval->text().toDouble();
		m_timerPulseCtrl->setChannel(timerChan);
		m_timerPulseCtrl->setFrequency(frequency);
		m_timerPulseCtrl->setEnabled(true);
	}

	 //Start Snap Counter function.
	errorCode = udCounterCtrl->setEnabled(true);
	CheckError(errorCode);
	timer->start(50);

	ui.btnStart->setEnabled(false);
	ui.btnConfig->setEnabled(false);
	ui.btnStop->setEnabled(true);
	ui.listSnapSource->setEnabled(false);
}

void SnapCounter::ButtonStopClicked() {
	timer->stop();

	ui.btnStart->setEnabled(true);
	ui.btnConfig->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.listSnapSource->setEnabled(true);
	
	//stop timer pulse
	if(m_isTimerUsing) {
		m_timerPulseCtrl->setEnabled(false);
		m_timerPulseCtrl->Dispose();
	} 

	//stop snap function
	aryListBoxSrcSel = ui.listSnapSource->selectedItems();
	int cnt = aryListBoxSrcSel.count();
	for (int i = 0; i < cnt; i++) {
		udCounterCtrl->SnapStop((EventId)(aryListBoxSrcSel.at(i)->data(32).toInt()));
	}

	//stop updown counter
	ErrorCode errorcode = udCounterCtrl->setEnabled(false);
	CheckError(errorcode);
}

void SnapCounter::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}

void SnapCounter::TimerTicked() {
	ErrorCode errorCode;
	errorCode = udCounterCtrl->setEnabled(true);
	CheckError(errorCode);
   
   int32 cntrValue;
   errorCode = udCounterCtrl->Read(1, &cntrValue);
   CheckError(errorCode);
	ui.txtCounterValue->setText(QString("%1").arg(cntrValue));
}

void SnapCounter::EventIDtoString(EventId id,QString &str) {
	switch (id)
	{
	case EvtUdIndex0:
		str = "Index0";
		break;
	case EvtUdIndex1:
		str = "Index1";
		break;
	case EvtUdIndex2:
		str = "Index2";
		break;
	case EvtUdIndex3:
		str = "Index3";
		break;
	case EvtUdIndex4:
		str = "Index4";
		break;
	case EvtUdIndex5:
		str = "Index5";
		break;
	case EvtUdIndex6:
		str = "Index6";
		break;
	case EvtUdIndex7:
		str = "Index7";
		break;
	case EvtCntTimer0:
		str = "Timer0";
		break;
	case EvtCntTimer1:
		str = "Timer1";
		break;
	case EvtCntTimer2:
		str = "Timer2";
		break;
	case EvtCntTimer3:
		str = "Timer3";
		break;
	case EvtCntTimer4:
		str = "Timer4";
		break;
	case EvtCntTimer5:
		str = "Timer5";
		break;
	case EvtCntTimer6:
		str = "Timer6";
		break;
	case EvtCntTimer7:
		str = "Timer7";
		break;
	case EvtDiintChannel000:
		str = "DiintChannel0";
		break;
	case EvtDiintChannel001:
		str = "DiintChannel1";
		break;
	case EvtDiintChannel002:
		str = "DiintChannel2";
		break;
	case EvtDiintChannel003:
		str = "DiintChannel3";
		break;
	case EvtDiintChannel004:
		str = "DiintChannel4";
		break;
	case EvtDiintChannel005:
		str = "DiintChannel5";
		break;
	case EvtDiintChannel006:
		str = "DiintChannel6";
		break;
	case EvtDiintChannel007:
		str = "DiintChannel7";
		break;
    case EvtDiCosintPort000:
        str = "DiConsintChannel0";
        break;
    case EvtDiCosintPort001:
        str = "DiConsintChannel1";
        break;
    case EvtDiCosintPort002:
        str = "DiConsintChannel2";
        break;
    case EvtDiCosintPort003:
        str = "DiConsintChannel3";
        break;
    case EvtDiPmintPort000:
        str = "DiPmintChannel0";
        break;
    case EvtDiPmintPort001:
        str = "DiPmintChannel1";
        break;
    case EvtDiPmintPort002:
        str = "DiPmintChannel2";
        break;
    case EvtDiPmintPort003:
        str = "DiPmintChannel3";
        break;
	default:
		str = "";
	}
}

void SnapCounter::CheckTimerUsingParam(EventId id, int& timerChan, bool& isTimerUsing) {
	if (id >= EvtCntTimer0 && id <=  EvtCntTimer7) {
		timerChan = id - EvtCntTimer0;
	}

	if (timerChan != -1) {
		isTimerUsing = true;
	}
}

void SnapCounter::SnapSrcSelChanged() {
	int item = 0;
	aryListBoxSrcSel = ui.listSnapSource->selectedItems();
	int cnt = aryListBoxSrcSel.count();

	int i = 0;
	int timerChan = -1;
	bool isTimerUsing = false;
	for (; i < cnt; i++) {
		item = aryListBoxSrcSel.at(i)->data(32).toInt();
		CheckTimerUsingParam((EventId)item, timerChan, isTimerUsing);
		if (isTimerUsing) {
			ui.txtTimeInterval->setEnabled(true);
			break;
		}
	}
	if (i == cnt) {
		ui.txtTimeInterval->setEnabled(false);
	}
}

void SnapCounter::OnCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam)
{
   SnapCounter * uParam = (SnapCounter *)userParam;
   if (uParam->ui.CounterValueList->count() > 40) {
      uParam->ui.CounterValueList->takeItem(0);
   }

   QString snapValue;
   QString srcID;
   QString source;

   uParam->ui.txtSnapCount->setText(QString("%1").arg(uParam->m_snapCount++));
   uParam->EventIDtoString((EventId)args->Id, srcID);

   snapValue = tr("CntrValue: ");
   for (int i = 0; i < args->Length; i++) {
      snapValue = snapValue + QString::number(args->Data[i], 16);
      snapValue = snapValue + tr(" ");
   }
   uParam->ui.CounterValueList->addItem(snapValue);

   source = tr("SrcID: ");
   source = source + srcID;
   uParam->ui.CounterValueList->addItem(source);

   if (uParam->ui.CounterValueList->count() > 40) {
      uParam->ui.CounterValueList->takeItem(0);
   }
}
