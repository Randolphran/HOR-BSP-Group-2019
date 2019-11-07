#include "synchronousonewaveformao.h"
#include <QMessageBox>

SynchronousOneWaveformAO::SynchronousOneWaveformAO(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

   bfdAoCtrl = BufferedAoCtrl::Create();

   dataScaled = NULL;
	this->m_waveSeled[0] = false;
	this->m_waveSeled[1] = false;

	this->buttonGroup1 = new QButtonGroup();
	this->buttonGroup1->addButton(ui.BtnSineA, 0);
	this->buttonGroup1->addButton(ui.BtnTriangleA, 1);
	this->buttonGroup1->addButton(ui.BtnSquareA, 2);
	this->buttonGroup1->addButton(ui.BtnSineB, 3);
	this->buttonGroup1->addButton(ui.BtnTriangleB, 4);
	this->buttonGroup1->addButton(ui.BtnSquareB, 5);
	this->buttonGroup1->setExclusive(false);

	this->buttons[0] = ui.BtnSineA;
	this->buttons[1] = ui.BtnTriangleA;
	this->buttons[2] = ui.BtnSquareA;
	this->buttons[3] = ui.BtnSineB;
	this->buttons[4] = ui.BtnTriangleB;
	this->buttons[5] = ui.BtnSquareB;
	
	strs[0] = "background:url(:/SynchronousOneWaveformAO/Resources/sine.png)";
	strs[1] = "background:url(:/SynchronousOneWaveformAO/Resources/sine_down.png)";
	strs[2] = "background:url(:/SynchronousOneWaveformAO/Resources/triangle.png)";
	strs[3] = "background:url(:/SynchronousOneWaveformAO/Resources/triangle_down.png)";
	strs[4] = "background:url(:/SynchronousOneWaveformAO/Resources/square.png)";
	strs[5] = "background:url(:/SynchronousOneWaveformAO/Resources/square_down.png)";

	connect(ui.btnConfigure, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(buttonGroup1, SIGNAL(buttonClicked(int)), this, SLOT(WaveButtonClicked(int)));
}

SynchronousOneWaveformAO::~SynchronousOneWaveformAO()
{
	
}

void SynchronousOneWaveformAO::Initialize() {
	//set the title of the form.
	this->setWindowTitle(tr("Synchronous One Waveform AO - Run(") + configure.deviceName + tr(")"));
	
	if (dataScaled != NULL) {
        delete[] dataScaled;
        dataScaled = NULL;
    }

	waveformGenerator = new WaveformGenerator(configure.pointCountPerWave);

	InitialButtons();

	//initialize the sine as the default choice
	ui.BtnSineA->setChecked(true);
	ui.BtnSineA->setStyleSheet(strs[1]);
	m_waveSeled[0] = true;
	m_waveParam[0].Style = sine;

	if (configure.channelCount > 1) {
		ui.BtnSineB->setChecked(true);
		ui.BtnSineB->setStyleSheet(strs[1]);
		m_waveSeled[1] = true;
		m_waveParam[1].Style = sine;
	}

	ConfigureDevice();

	//set the ChannelCount
    if (bfdAoCtrl->getScanChannel()->getChannelCount() > 1) {
        bfdAoCtrl->getScanChannel()->setChannelCount(2);
    }

	ConfigurePanel();
}

void SynchronousOneWaveformAO::ConfigureDevice() {
	ErrorCode errorCode = Success;
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());
	errorCode = bfdAoCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = bfdAoCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

	errorCode = bfdAoCtrl->setStreaming(false);
    CheckError(errorCode);

	ScanChannel* scanChannel = bfdAoCtrl->getScanChannel();
    errorCode = scanChannel->setChannelStart(configure.channelStart);
    CheckError(errorCode);
    errorCode = scanChannel->setChannelCount(configure.channelCount);
    CheckError(errorCode);
    errorCode = scanChannel->setSamples(configure.pointCountPerWave);
    CheckError(errorCode);
    errorCode = bfdAoCtrl->getConvertClock()->setRate(configure.clockRate);
    CheckError(errorCode);

    for (int i = 0; i < bfdAoCtrl->getChannels()->getCount(); i++) {
        errorCode = bfdAoCtrl->getChannels()->getItem(i).setValueRange(configure.valueRange);
        CheckError(errorCode);
    }
}

void SynchronousOneWaveformAO::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode)) {
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
		QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void SynchronousOneWaveformAO::ButtonConfigureClicked() {
	int dialogResult = configDialog->exec();
	if (dialogResult == QDialog::Accepted) {
		configure = configDialog->GetConfigureParameter();
		Initialize();
	}
}

void SynchronousOneWaveformAO::ConfigurePanel() {
	if (configure.channelCount == 1) {
		ui.BtnSineB->setEnabled(false);
		ui.BtnTriangleB->setEnabled(false);
		ui.BtnSquareB->setEnabled(false);
		ui.txtboxHiLevelB->setEnabled(false);
		ui.txtboxLoLevelB->setEnabled(false);
		ui.chLabelB->setText(tr(""));
	} else {
		ui.BtnSineB->setEnabled(true);
		ui.BtnTriangleB->setEnabled(true);
		ui.BtnSquareB->setEnabled(true);
		ui.txtboxHiLevelB->setEnabled(true);
		ui.txtboxLoLevelB->setEnabled(true);
		ui.chLabelB->setText(QString("%1").arg((configure.channelStart + 1) % bfdAoCtrl->getChannelCount()));
	}
	ui.chLabelA->setText(QString("%1").arg(configure.channelStart));
}

void SynchronousOneWaveformAO::InitialButtons() {
	for (int i = 0; i < 6; i++) {
		buttons[i]->setChecked(false);
		buttons[i]->setStyleSheet(strs[(i % 3) * 2]);
	}
}

void SynchronousOneWaveformAO::WaveButtonClicked(int id) {
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

	if (buttons[id]->isChecked()) {
		m_waveParam[seledCH].Style = (WaveformStyle)(id % 3);
	} else {
		m_waveParam[seledCH].Style = (WaveformStyle)2;
	}
}

void SynchronousOneWaveformAO::ButtonStartClicked() {
	int dataCount;
	ErrorCode errorCode = Success;

	if ((m_waveSeled[0] == false) && (m_waveSeled[1] == false)) {
		QMessageBox::information(this, "Warning Information", "Please select a waveform!");
		return;
	}

	//prepare the AO
    errorCode = bfdAoCtrl->Prepare();
    CheckError(errorCode);

	ScanChannel* scanChannel = bfdAoCtrl->getScanChannel();
    dataCount = scanChannel->getChannelCount() * scanChannel->getSamples();
	dataScaled = new double[dataCount];

	if ((m_waveSeled[0] == true) && (m_waveSeled[1] == false)) {
		m_waveParam[0].HighLevel = ui.txtboxHiLevelA->text().toDouble();
        m_waveParam[1].HighLevel = 0;
		m_waveParam[0].LowLevel = ui.txtboxLoLevelA->text().toDouble();
        m_waveParam[1].LowLevel = 0;
    } else if ((m_waveSeled[0] == false) && (m_waveSeled[1] == true)) {
        m_waveParam[0].HighLevel = 0;
		m_waveParam[1].HighLevel = ui.txtboxHiLevelB->text().toDouble();
        m_waveParam[0].LowLevel = 0;
		m_waveParam[1].LowLevel = ui.txtboxLoLevelB->text().toDouble();
    } else if ((m_waveSeled[0] == true) && (m_waveSeled[1] == true)) {
        m_waveParam[0].HighLevel = ui.txtboxHiLevelA->text().toDouble();
        m_waveParam[1].HighLevel = ui.txtboxHiLevelB->text().toDouble();
        m_waveParam[0].LowLevel = ui.txtboxLoLevelA->text().toDouble();
        m_waveParam[1].LowLevel = ui.txtboxLoLevelB->text().toDouble();
    }

	//generator the wave
	if (configure.channelCount <= 1) {
		this->waveformGenerator->GetOnePeriod(dataScaled, m_waveParam[0]);
	} else {
		this->waveformGenerator->GetMultipleWaveform(dataScaled, 2, m_waveParam);
	}

	//Convert scaled  data to raw data
	errorCode = bfdAoCtrl->SetData(dataCount, dataScaled);
    CheckError(errorCode);

    //Start buffered AO in synchronous
	errorCode = bfdAoCtrl->RunOnce();
    CheckError(errorCode);
}
