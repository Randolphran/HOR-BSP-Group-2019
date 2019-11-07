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
    PwMeterCtrl* pwMeterCtrl = PwMeterCtrl::Create();
    Array<DeviceTreeNode> *supportedDevices = pwMeterCtrl->getSupportedDevices();

	if (supportedDevices->getCount() == 0)
	{
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
	pwMeterCtrl->Dispose();
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
    ui.cmbCounterChannel->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    PwMeterCtrl* pwMeterCtrl = PwMeterCtrl::Create();

	ErrorCode errorCode = pwMeterCtrl->setSelectedDevice(selected);
	ui.btnOK->setEnabled(true);
	if (errorCode != Success){
		QString str;
        QString des = QString::fromStdWString(description);
		str.sprintf("Error:the error code is 0x%x\n\
                   The %s is busy or not exit in computer now.\n\
                   Select other device please!", errorCode, des.toUtf8().data());
		QMessageBox::information(this, "Warning Information", str);
		ui.btnOK->setEnabled(false);
		return;
	}

	// Set channel start combo box
    int channelCountMax = pwMeterCtrl->getFeatures()->getChannelCountMax();
    Array<CounterCapability> * counterCap;
    int itemCount;

	for (int i = 0; i < channelCountMax; i++) {
		itemCount = pwMeterCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
        counterCap = pwMeterCtrl->getFeatures()->getCapabilities()->getItem(i);
        for (int j = 0; j < itemCount; j++) {
			if (InstantPwmIn == counterCap->getItem(j)) {
				ui.cmbCounterChannel->addItem(QString("%1").arg(i));	
            }
        }
    }
    ui.cmbCounterChannel->setCurrentIndex(0);
    pwMeterCtrl->Dispose();  
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    PwMeterCtrl* pwMeterCtrl = PwMeterCtrl::Create();

	ErrorCode errorCode = pwMeterCtrl->setSelectedDevice(selected);
	CheckError(errorCode); 

	configure.deviceName = ui.cmbDevice->currentText();
	configure.channel = ui.cmbCounterChannel->currentText().toInt();
	
	pwMeterCtrl->Dispose();
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
