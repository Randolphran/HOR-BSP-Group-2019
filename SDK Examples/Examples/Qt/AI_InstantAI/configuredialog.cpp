#include "configuredialog.h"
#include <QtWidgets/QMessageBox>
#include <QtDebug>
#include <QProcess>
#include <QFileDialog>

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
	Initailization();
}

ConfigureDialog::~ConfigureDialog()
{
	
}

void ConfigureDialog::Initailization()
{
   InstantAiCtrl *instantAiCtrl = InstantAiCtrl::Create();
	Array<DeviceTreeNode>* supportedDevices = instantAiCtrl->getSupportedDevices();

	if (supportedDevices->getCount() == 0)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("No device to support the currently demonstrated function!"));
		QCoreApplication::quit();
	} 
	else
	{
		for (int i = 0; i < supportedDevices->getCount(); i++)
		{
			DeviceTreeNode const &node = supportedDevices->getItem(i);
			qDebug("%d, %ls\n", node.DeviceNumber, node.Description);
			ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
		}
		ui.cmbDevice->setCurrentIndex(0);
	}
	configure.profilePath = L"";
	instantAiCtrl->Dispose();
	supportedDevices->Dispose();
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

    InstantAiCtrl *instantAiCtrl = InstantAiCtrl::Create();
	ErrorCode errorCode = instantAiCtrl->setSelectedDevice(selected);
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

	int channelCount = (instantAiCtrl->getChannelCount() < 16) ? 
		instantAiCtrl->getChannelCount() : 16;
	int logicChannelCount = instantAiCtrl->getChannelCount();

	for (int i = 0; i < logicChannelCount; i++)
	{
		ui.cmbChannelStart->addItem(QString("%1").arg(i));
	}

	for (int i = 0; i < channelCount; i++)
	{
		ui.cmbChannelCount->addItem(QString("%1").arg(i + 1));
	}

	Array<ValueRange>* ValueRanges = instantAiCtrl->getFeatures()->getValueRanges();
	wchar_t		 vrgDescription[128];
	MathInterval ranges;
	for (int i = 0; i < ValueRanges->getCount(); i++)
	{
		errorCode = AdxGetValueRangeInformation(ValueRanges->getItem(i), 
			sizeof(vrgDescription), vrgDescription, &ranges, NULL);
		CheckError(errorCode);
		QString str = QString::fromWCharArray(vrgDescription);
		ui.cmbValueRange->addItem(str);
	}

	instantAiCtrl->Dispose();

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
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

	InstantAiCtrl* instantAiCtrl = InstantAiCtrl::Create();
	ErrorCode errorCode = instantAiCtrl->setSelectedDevice(selected);
	CheckError(errorCode);

	Array<ValueRange>* valueRanges = instantAiCtrl->getFeatures()->getValueRanges();
	configure.deviceName = ui.cmbDevice->currentText();
	configure.channelStart = ui.cmbChannelStart->currentText().toInt();
	configure.channelCount = ui.cmbChannelCount->currentText().toInt();
	configure.valueRange = valueRanges->getItem(ui.cmbValueRange->currentIndex());

	instantAiCtrl->Dispose();
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
