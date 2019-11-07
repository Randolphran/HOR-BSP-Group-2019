#include "staticao.h"
#include <QMessageBox>

StaticAO::StaticAO(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

    /*this->buttonGroup1 = new QButtonGroup();
	this->buttonGroup1->addButton(ui.BtnSineA, 0);
	this->buttonGroup1->addButton(ui.BtnTriangleA, 1);
	this->buttonGroup1->addButton(ui.BtnSquareA, 2);
	this->buttonGroup1->addButton(ui.BtnSineB, 3);
	this->buttonGroup1->addButton(ui.BtnTriangleB, 4);
	this->buttonGroup1->addButton(ui.BtnSquareB, 5);
	this->buttonGroup1->setExclusive(false);

	this->buttonGroup2 = new QButtonGroup();
	this->buttonGroup2->addButton(ui.BtnManualA, 0);
	this->buttonGroup2->addButton(ui.BtnManualB, 1);
    this->buttonGroup2->setExclusive(false);*/

	this->buttons[0] = ui.BtnSineA;
	this->buttons[1] = ui.BtnTriangleA;
	this->buttons[2] = ui.BtnSquareA;
	this->buttons[3] = ui.BtnSineB;
	this->buttons[4] = ui.BtnTriangleB;
	this->buttons[5] = ui.BtnSquareB;
	
	strs[0] = "background:url(:/StaticAO/Resources/sine.png)";
	strs[1] = "background:url(:/StaticAO/Resources/sine_down.png)";
	strs[2] = "background:url(:/StaticAO/Resources/triangle.png)";
	strs[3] = "background:url(:/StaticAO/Resources/triangle_down.png)";
	strs[4] = "background:url(:/StaticAO/Resources/square.png)";
	strs[5] = "background:url(:/StaticAO/Resources/square_down.png)";

   instantAoCtrl = InstantAoCtrl::Create();
	this->m_waveSeled[0] = false;
	this->m_waveSeled[1] = false;
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(TimerTicked()));
	connect(ui.timerTrackBar, SIGNAL(valueChanged(int)), this, SLOT(SliderValueChanged(int)));
	connect(ui.btnConfigure, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
    //connect(this->buttonGroup1, SIGNAL(buttonClicked(int)), this, SLOT(WaveButtonClicked(int)));
    //connect(this->buttonGroup2, SIGNAL(buttonClicked(int)), this, SLOT(ManualClicked(int)));
}

StaticAO::~StaticAO()
{

}

void StaticAO::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Static AO - Run(") + configure.deviceName + tr(")"));

	//initialize these variables
    channelStart = 0;
    channelCount = 0;

	waveformGenerator = new WaveformGenerator(configure.pointCountPerWave);

	ConfigureDevice();
	ConfigurePanel();

	//initialize a timer which drive the data acquisition.
	timer->start(50);
}

void StaticAO::ConfigureDevice() {
	ErrorCode errorCode = Success;
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
	errorCode = instantAoCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = instantAoCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

	for (int i = 0; i < instantAoCtrl->getChannels()->getCount(); i++) {
		errorCode = instantAoCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
		CheckError(errorCode);
	}
}

void StaticAO::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode)) {
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void StaticAO::ButtonConfigureClicked() {
	timer->stop();
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted) {
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}
}

void StaticAO::ConfigurePanel() {
	if (configure.channelCount == 1) {
		channelStart = configure.channelStart;
		channelCount = 1;

		ui.BtnSineB->setEnabled(false);
		ui.BtnTriangleB->setEnabled(false);
		ui.BtnSquareB->setEnabled(false);
		ui.BtnManualB->setEnabled(false);
		ui.txtboxHiLevelB->setEnabled(false);
		ui.txtboxLoLevelB->setEnabled(false);
		ui.txtboxValueB->setEnabled(false);
		ui.chLabelB->setText(tr(""));
	} else {
		channelStart = configure.channelStart;
		channelCount = 2;

		ui.BtnSineB->setEnabled(true);
		ui.BtnTriangleB->setEnabled(true);
		ui.BtnSquareB->setEnabled(true);
		ui.BtnManualB->setEnabled(true);
		ui.txtboxHiLevelB->setEnabled(true);
		ui.txtboxLoLevelB->setEnabled(true);
		ui.txtboxValueB->setEnabled(true);
		ui.chLabelB->setText(QString("%1").arg((channelStart + 1) % instantAoCtrl->getChannelCount()));
	}
	ui.chLabelA->setText(QString("%1").arg(channelStart));
}

void StaticAO::SliderValueChanged(int value) {
	timer->setInterval(ui.timerTrackBar->value());
	ui.timerFreqLabel->setText(QString("%1").arg(ui.timerTrackBar->value()) + tr("ms"));
}

void StaticAO::WaveButtonClicked(int id) {
	int seledCH, baseIdx, imgIdx;

	seledCH = id / 3;
	baseIdx = seledCH * 3;

	for (int i = baseIdx; i < baseIdx + 3; i++) {
		if (i != id && buttons[i]->isChecked()) {
			imgIdx = (i- baseIdx) * 2;
			buttons[i]->setChecked(false);
			buttons[i]->setStyleSheet(strs[imgIdx]);
		}
	}

	if (buttons[id]->isChecked()) {
		buttons[id]->setStyleSheet(strs[(id - baseIdx) * 2 + 1]);
	} else {
		buttons[id]->setStyleSheet(strs[(id - baseIdx) * 2]);
	}

	m_waveSeled[seledCH] = buttons[id]->isChecked();
	m_waveParam[seledCH].Style = (WaveformStyle)(id % 3);

	if (seledCH == 0) {
		m_waveParam[seledCH].HighLevel = ui.txtboxHiLevelA->text().toDouble();
		m_waveParam[seledCH].LowLevel = ui.txtboxLoLevelA->text().toDouble();
	} else {
		m_waveParam[seledCH].HighLevel = ui.txtboxHiLevelB->text().toDouble();
		m_waveParam[seledCH].LowLevel = ui.txtboxLoLevelB->text().toDouble();
	}
	m_wavePtIdx[seledCH] = 0;
}

void StaticAO::ManualClicked(int id) {
	int ch, baseIdx;

	//manual ouput button click
	ch = id;
	baseIdx = id * 3;

	for (int i = 0; i < 3; i++) {
		if (buttons[i + baseIdx]->isChecked()) {
			buttons[i + baseIdx]->setChecked(false);
			buttons[i + baseIdx]->setStyleSheet(strs[i * 2]);
		}
	}

	m_waveSeled[ch] = false;

	if (ch == 0) {
		dataScaled[ch] = ui.txtboxValueA->text().toDouble();
	} else {
		dataScaled[ch] = ui.txtboxValueB->text().toDouble();
	}
}

void StaticAO::TimerTicked() {
	for (int i = 0; i < 2; i++) {
		if (m_waveSeled[i]) {
			dataScaled[i] = waveformGenerator->GetOnePoint(m_waveParam[i].Style, m_wavePtIdx[i], m_waveParam[i].HighLevel, m_waveParam[i].LowLevel);
			m_wavePtIdx[i] = (m_wavePtIdx[i] + 1) % configure.pointCountPerWave;
		}
	}

	ErrorCode errorCode = Success;
	errorCode = instantAoCtrl->Write(channelStart, channelCount, dataScaled);
	if (errorCode != Success) {
		timer->stop();
		CheckError(errorCode);
	}
}




