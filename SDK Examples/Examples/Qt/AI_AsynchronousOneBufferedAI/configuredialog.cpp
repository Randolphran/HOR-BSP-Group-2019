#include "configuredialog.h"
#include <QtWidgets/QMessageBox>
#include <QProcess>
#include <QFileDialog>

#define MAXCLOCKRATE 500000000

ConfigureDialog::ConfigureDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged(int)));
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(ButtonOKClicked()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(ButtonCancelClicked()));
	connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(ButtonBrowseClicked()));

	//Set the maximum value of data count per channel and clock rate per channel
	//as 10Mb = 10000000, 500MHz = 500000000.
	ui.edtClockRatePerChan->setValidator(new QDoubleValidator(1, MAXCLOCKRATE, 3, this));

	Initailization();
}

ConfigureDialog::~ConfigureDialog()
{

}

void ConfigureDialog::Initailization()
{
   WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
	Array<DeviceTreeNode> *supportedDevice = waveformAiCtrl->getSupportedDevices();

	if (supportedDevice->getCount() == 0)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("No device to support the currently demonstrated function!"));
		QCoreApplication::quit();
	}
	else
	{
		for (int i = 0; i < supportedDevice->getCount(); i++)
		{
			DeviceTreeNode const &node = supportedDevice->getItem(i);
			qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
			ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
		}
		ui.cmbDevice->setCurrentIndex(0);
	}
	configure.profilePath = L"";
	waveformAiCtrl->Dispose();
	supportedDevice->Dispose();
}

void ConfigureDialog::CheckError(ErrorCode errorCode)
{
	if (errorCode >= 0xE0000000 && errorCode != Success)
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void ConfigureDialog::DeviceChanged(int index)
{
    ui.cmbChannelCount->clear();
    ui.cmbChannelStart->clear();
    ui.cmbValueRange->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
    ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);
    ui.btnOK->setEnabled(true);
	if (errorCode != 0){
		QString str;
        QString des = QString::fromStdWString(description);
		str.sprintf("Error:the error code is 0x%x\n\
						The %s is busy or not exit in computer now.\n\
                        Select other device please!", errorCode, des.toUtf8().data());
		QMessageBox::information(this, "Warning Information", str);
		ui.btnOK->setEnabled(false);
		return;
	}

   int channelCount = (waveformAiCtrl->getChannelCount() < 16) ? 
      waveformAiCtrl->getChannelCount() : 16;
   int logicChannelCount = waveformAiCtrl->getChannelCount();
	for (int i = 0; i < logicChannelCount; i++)
	{
		ui.cmbChannelStart->addItem(QString("%1").arg(i));
	}

	for (int i = 0; i < channelCount; i++)
	{
		ui.cmbChannelCount->addItem(QString("%1").arg(i + 1));
	}

    Array<ValueRange> *ValueRanges = waveformAiCtrl->getFeatures()->getValueRanges();

	wchar_t			vrgDescription[128];
	MathInterval	ranges;
	ValueUnit		valueUnit;
	for(int i = 0; i < ValueRanges->getCount(); i++)
	{
		errorCode = AdxGetValueRangeInformation(ValueRanges->getItem(i), 
			sizeof(vrgDescription), vrgDescription, &ranges, &valueUnit);
		CheckError(errorCode);
		
		//we filter the Celsius degree for the buffered AI can not support this function.
		if (valueUnit == CelsiusUnit)
		{
			continue;
		}

		QString str = QString::fromWCharArray(vrgDescription);
		ui.cmbValueRange->addItem(str);
	}

	waveformAiCtrl->Dispose();

	//Set the default value.
	ui.cmbChannelStart->setCurrentIndex(0);
	ui.cmbChannelCount->setCurrentIndex(1);
	ui.cmbValueRange->setCurrentIndex(0);
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

	double clockRate = ui.edtClockRatePerChan->text().toDouble();
	int dataCount = ui.edtSectionLength->text().toInt();
	if (clockRate < 1 || clockRate > MAXCLOCKRATE)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("Sorry, the clock rate per channel is invalid"));
		return;
	}

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

    WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();
    ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);
    CheckError(errorCode);

    Array<ValueRange> *ValueRanges = waveformAiCtrl->getFeatures()->getValueRanges();
    configure.deviceName = ui.cmbDevice->currentText();
    configure.channelCount = ui.cmbChannelCount->currentText().toInt();
    configure.channelStart = ui.cmbChannelStart->currentText().toInt();
    configure.valueRange = ValueRanges->getItem(ui.cmbValueRange->currentIndex());
    configure.sectionLength= ui.edtSectionLength->text().toInt();
    configure.clockRatePerChan = ui.edtClockRatePerChan->text().toDouble();

    waveformAiCtrl->Dispose();
    this->accept();
}

void ConfigureDialog::ButtonCancelClicked()
{
	this->reject();
}

void ConfigureDialog::ButtonBrowseClicked()
{
	QString str = QFileDialog::getOpenFileName(this, tr("Open Profile"), "../../profile", tr("Image Files(*.xml)")); 
	ui.txtProfilePath->setText(str);
    configure.profilePath = str.toStdWString().c_str();
}
void ConfigureDialog::RefreshConfigureParameter()
{
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

	WaveformAiCtrl * waveformAiCtrl = WaveformAiCtrl::Create();

	ErrorCode errorCode = waveformAiCtrl->setSelectedDevice(selected);
	CheckError(errorCode);

	ui.edtClockRatePerChan->setText(QString::number(waveformAiCtrl->getConversion()->getClockRate(), 'f',0));
	ui.edtSectionLength->setText(QString::number(waveformAiCtrl->getRecord()->getSectionLength(), 'f', 0));

    waveformAiCtrl->Dispose();
}
