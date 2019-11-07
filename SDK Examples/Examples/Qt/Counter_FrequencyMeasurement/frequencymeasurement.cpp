#include <QPalette>
#include <QMessageBox>
#include "frequencymeasurement.h"

FrequencyMeasurement::FrequencyMeasurement(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	//Set the background image for the main frame.
	ui.bkgrndImage->setAutoFillBackground(true);
	QPixmap pixMap(":/FrequencyMeasurement/Resources/Background.png");
	QPalette backPalette;
	backPalette.setBrush(ui.bkgrndImage->backgroundRole(),QBrush(pixMap));
	ui.bkgrndImage->setPalette(backPalette);

   freqMeterCtrl = FreqMeterCtrl::Create();
	timer = new QTimer(this);

	graph = new SimpleGraph(ui.DataView);
	graph->setFixedSize(ui.DataView->size());

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.timerTrackBar, SIGNAL(valueChanged(int)), this, SLOT(timerTrackBarChanged(int)));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnPause, SIGNAL(clicked()), this, SLOT(ButttonPauseClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.Enlarge, SIGNAL(clicked()), this, SLOT(EnlargeClicked()));
	connect(ui.Shorten, SIGNAL(clicked()), this, SLOT(ShortenClicked()));
}

FrequencyMeasurement::~FrequencyMeasurement()
{

}

void FrequencyMeasurement::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Frequency Measurement - Run(") + configure.deviceName + tr(")"));

	m_yaxisMax = 1000000;  // default is 1MHz
    isCounterReseted = true;

    ConfigureDevice();

	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);

	InitializeGraph();
}

void FrequencyMeasurement::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

	ErrorCode errorCode = freqMeterCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = freqMeterCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

    errorCode = freqMeterCtrl->setChannelCount(1);
    CheckError(errorCode);
    errorCode = freqMeterCtrl->setChannelStart(configure.channel);
    CheckError(errorCode);
}

void FrequencyMeasurement::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void FrequencyMeasurement::InitializeGraph() {
	graph->m_xCordTimeDiv = 1000;
	InitializeYAxis();
	graph->Clear();	
}

void FrequencyMeasurement::InitializeYAxis() {
	graph->m_yCordRangeMax = m_yaxisMax;
	graph->m_yCordRangeMin = 0;

	ui.yTLabel->setText(FormatFreqString(m_yaxisMax));
	ui.yMLabel->setText(FormatFreqString(m_yaxisMax / 2));
}

QString FrequencyMeasurement::FormatFreqString(double freqHz) {
	QString freqUnits[4] = {"Hz", "KHz", "MHz", "GHz"};
	QString freq;

	int i;
    for (i = 0; i < 3; i++) {
		if (freqHz < 1000) {
			break;
        } else {
			freqHz = freqHz / 1000;
        }
	}
	freq = QString("%1").arg(freqHz) + freqUnits[i];
	return freq;
}

void FrequencyMeasurement::TimerTicked() {
   freqMeterCtrl->Read(1, frequency);
   ui.lineEditFreqValue->setText(QString("%1").arg(frequency[0]));
	graph->Chart(frequency, 1, 1, timer->interval() / 1000.0);
}

void FrequencyMeasurement::timerTrackBarChanged(int value) {
	timer->setInterval(ui.timerTrackBar->value());
	ui.timerValueLabel->setText(QString("%1").arg(ui.timerTrackBar->value()) + tr("ms"));
	graph->Clear();
}

void FrequencyMeasurement::EnlargeClicked() {
	if (m_yaxisMax < 10000000) {
		graph->Clear();
		m_yaxisMax = m_yaxisMax * 10;
        InitializeYAxis();
	}
}

void FrequencyMeasurement::ShortenClicked() {
	if (m_yaxisMax > 1) {
		graph->Clear();
		m_yaxisMax = m_yaxisMax / 10;
        InitializeYAxis();
	}
}

void FrequencyMeasurement::ButtonStartClicked() {
	if (isCounterReseted == true) {
		ErrorCode errorCode = Success;
        errorCode = freqMeterCtrl->setEnabled(true);
        CheckError(errorCode);

		ui.btnStop->setEnabled(true);
	}

	ui.btnStart->setEnabled(false);
	ui.btnPause->setEnabled(true);
	ui.btnConfig->setEnabled(false);
	timer->start(ui.timerTrackBar->value());
}

void FrequencyMeasurement::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted)
	{
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}	
}

void FrequencyMeasurement::ButttonPauseClicked() {
	timer->stop();
	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(true);
	ui.btnConfig->setEnabled(false);
	isCounterReseted = false;
}

void FrequencyMeasurement::ButtonStopClicked() {
	ErrorCode errorCode = Success;
    errorCode = freqMeterCtrl->setEnabled(false);
    CheckError(errorCode);	

	timer->stop();
	ui.btnStart->setEnabled(true);
	ui.btnPause->setEnabled(false);
	ui.btnStop->setEnabled(false);
	ui.btnConfig->setEnabled(true);
	isCounterReseted = true;
	graph->Clear();
}

