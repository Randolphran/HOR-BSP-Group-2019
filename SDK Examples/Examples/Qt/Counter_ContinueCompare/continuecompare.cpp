#include <QMessageBox>
#include "continuecompare.h"

ContinueCompare::ContinueCompare(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

   udCounterCtrl = UdCounterCtrl::Create();
   udCounterCtrl->addUdCntrEventHandler(OnUdCounterEvent, this);
	timer = new QTimer(this);

	//initialize the compare table
	ui.txtTab1Data0->setText(tr("100"));
	ui.txtTab1Data1->setText(tr("340"));
	ui.txtTab1Data2->setText(tr("720"));
	ui.txtTab2Data0->setText(tr("1000"));
	ui.txtTab2Data1->setText(tr("1980"));
	ui.txtTab2Data2->setText(tr("2510"));

	ui.txtInt1FirstValue->setText(tr("150"));
	ui.txtInt1Increment->setText(tr("3"));
	ui.txtInt1Count->setText(tr("3"));
	ui.txtInt2FirstValue->setText(tr("210"));
	ui.txtInt2Increment->setText(tr("3"));
	ui.txtInt2Count->setText(tr("3"));
    
	ui.txtTab1Data0->setValidator(new QIntValidator(0, 100000));
	ui.txtTab1Data1->setValidator(new QIntValidator(0, 100000));
	ui.txtTab1Data2->setValidator(new QIntValidator(0, 100000));
	ui.txtTab2Data0->setValidator(new QIntValidator(0, 100000));
	ui.txtTab2Data1->setValidator(new QIntValidator(0, 100000));
	ui.txtTab2Data2->setValidator(new QIntValidator(0, 100000));

	ui.txtInt1FirstValue->setValidator(new QIntValidator(0, 100000));
	ui.txtInt1Increment->setValidator(new QIntValidator(0, 100000));
	ui.txtInt1Count->setValidator(new QIntValidator(0, 100000));
	ui.txtInt2FirstValue->setValidator(new QIntValidator(0, 100000));
	ui.txtInt2Increment->setValidator(new QIntValidator(0, 100000));
	ui.txtInt2Count->setValidator(new QIntValidator(0, 100000));

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));	
}

ContinueCompare::~ContinueCompare()
{
	udCounterCtrl->Dispose();
}

void ContinueCompare::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Continue Compare - Run(") + configure.deviceName + tr(")"));	

	ConfigureDevice();

	ui.btnStart->setEnabled(true);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);
}

void ContinueCompare::ConfigureDevice() {
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

    for(int i = udCounterCtrl->getChannelStart(); i < udCounterCtrl->getChannelStart() + udCounterCtrl->getChannelCount(); i++)
    {
        errorCode = udCounterCtrl->getChannels()->getItem(i).setCountingType(configure.cntType);
        CheckError(errorCode);
    }
}

void ContinueCompare::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void ContinueCompare::CreateDisperseTable(int tabIndex, int CompTab[]) {
	if (tabIndex == 0) {
		CompTab[0] = ui.txtTab1Data0->text().toInt();
		CompTab[1] = ui.txtTab1Data1->text().toInt();
		CompTab[2] = ui.txtTab1Data2->text().toInt();
	} else {
		CompTab[0] = ui.txtTab2Data0->text().toInt();
		CompTab[1] = ui.txtTab2Data1->text().toInt();
		CompTab[2] = ui.txtTab2Data2->text().toInt();
	}
}

void ContinueCompare::CreateLineTable(int tabIndex, LineTabParam& param) {
	if (tabIndex == 0) {
		param.firstValue = ui.txtInt1FirstValue->text().toULong();
		param.increment = ui.txtInt1Increment->text().toULong();
		param.count = ui.txtInt1Count->text().toULong();
	} else {
		param.firstValue = ui.txtInt2FirstValue->text().toULong();
		param.increment = ui.txtInt2Increment->text().toULong();
		param.count = ui.txtInt2Count->text().toULong();
	}
}

void ContinueCompare::TimerTicked() {
	ErrorCode errorCode;
	errorCode = udCounterCtrl->setEnabled(true);
	CheckError(errorCode);
	udCounterCtrl->Read(1, &m_counterValue);
	ui.txtCounterValue->setText("0x" + QString::number((uint)(m_counterValue), 16));
}

void ContinueCompare::ButtonStartClicked() {
	ErrorCode errorCode;

	//Set compare table
	int ComTable[3] = {0};
	LineTabParam param;
	
	if (ui.radTable->isChecked()) {
		m_contCompTabSel = dispersed;
	} else {
		m_contCompTabSel = lined;
	}

	if (dispersed == m_contCompTabSel) {
		CreateDisperseTable(0,ComTable);
		udCounterCtrl->CompareSetTable(udCounterCtrl->getChannelStart(), 3, ComTable);
	} else {
		CreateLineTable(0, param);
		udCounterCtrl->CompareSetInterval(udCounterCtrl->getChannelStart(), param.firstValue, param.increment, param.count);
	}
    m_endCount = 0;
    m_matchCount = 0;
    m_tabIndex = 0;
    m_counterValue = 0;

	//Start Snap Counter function.
	errorCode = udCounterCtrl->setEnabled(true);
	CheckError(errorCode);
	timer->start(50);

	ui.btnStart->setEnabled(false);
	ui.btnStop->setEnabled(true);
	ui.btnConfig->setEnabled(false);

	EnableCompareTable(false);

	ui.txtPMCount->setText(tr("0"));
	ui.txtEndCount->setText(tr("0"));
}

void ContinueCompare::ButtonStopClicked() {
	 //Stop the user Timer
	timer->stop();

	ui.btnStart->setEnabled(true);
	ui.btnConfig->setEnabled(true);
	ui.btnStop->setEnabled(false);

	EnableCompareTable(true);

	ErrorCode errorCode = udCounterCtrl->setEnabled(false);
	CheckError(errorCode);
}

void ContinueCompare::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}

void ContinueCompare::EnableCompareTable(bool enabled) {
	ui.radTable->setEnabled(enabled);
	ui.txtTab1Data0->setEnabled(enabled);
	ui.txtTab1Data1->setEnabled(enabled);
	ui.txtTab1Data2->setEnabled(enabled);
	ui.txtTab2Data0->setEnabled(enabled);
	ui.txtTab2Data1->setEnabled(enabled);
	ui.txtTab2Data2->setEnabled(enabled);

	ui.radInterval->setEnabled(enabled);
	ui.txtInt1FirstValue->setEnabled(enabled);
	ui.txtInt1Increment->setEnabled(enabled);
	ui.txtInt1Count->setEnabled(enabled);
	ui.txtInt2FirstValue->setEnabled(enabled);
	ui.txtInt2Increment->setEnabled(enabled);
	ui.txtInt2Count->setEnabled(enabled);
}

void ContinueCompare::OnUdCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam)
{
   static int    comTable[3];
   LineTabParam  lineTabparam;
   static int    evntEndID[8];
   static int    evntMatchId[8];
   static bool   matched;

   ContinueCompare * uParam = (ContinueCompare *)userParam;
   
   int channelCount = 0;
   int channelStart = 0;

   UdCounterCtrl * udCounterCtrl = (UdCounterCtrl*)sender;
   channelStart = udCounterCtrl->getChannelStart();
   channelCount = udCounterCtrl->getChannelCount();
   for (int i = 0; i < channelCount; i++)
   {
      evntEndID[i] = EvtCntCompareTableEnd0 + i + channelStart;
      evntMatchId[i] = EvtCntPatternMatch0 + i + channelStart;
   }

   if (EvtCntCompareTableEnd0 + channelStart <= args->Id && args->Id <EvtCntCompareTableEnd0 + channelStart + channelCount)
   {
      uParam->m_endCount++;
      uParam->m_tabIndex++;
      if (uParam->m_contCompTabSel == dispersed)
      {
         uParam->CreateDisperseTable(uParam->m_tabIndex % 2, comTable);
         udCounterCtrl->CompareSetTable(channelStart, 3, comTable);
      }else{
         uParam->CreateLineTable(uParam->m_tabIndex % 2, lineTabparam);
         udCounterCtrl->CompareSetInterval(channelStart, lineTabparam.firstValue, lineTabparam.increment, lineTabparam.count);
      }
      matched = true;
   } else if (EvtCntPatternMatch0 + channelStart <= args->Id && args->Id <= EvtCntPatternMatch0 + channelStart + channelCount)
   {
      uParam->m_matchCount++;
      matched = true;
   }
   if (matched)
   {
       uParam->ui.txtPMCount->setText(QString("%1").arg(uParam->m_matchCount));
       uParam->ui.txtEndCount->setText(QString("%1").arg(uParam->m_endCount));
       matched = false;
   }
}
