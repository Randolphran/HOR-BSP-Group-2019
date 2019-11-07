#include "configuredialog.h"
#include <QMessageBox>
#include <QtDebug>
#include <Qprocess>
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
	connect(ui.cmbModuleIndex, SIGNAL(clicked()), this, SLOT(ModuleIndexChanged(int)));
	connect(ui.btnBrowse, SIGNAL(clicked()), this, SLOT(ButtonBrowseClicked()));
	
   Initailization();
}

ConfigureDialog::~ConfigureDialog()
{
	
}

void ConfigureDialog::Initailization()
{
   TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
    Array<DeviceTreeNode> *supportedDevices = timerPulseCtrl->getSupportedDevices();

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
	timerPulseCtrl->Dispose();
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
	ui.cmbModuleIndex->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

	TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();
	Array<DeviceTreeNode> *supportedDevices = timerPulseCtrl->getSupportedDevices();

	// Set ModulesIndex combo box
	DeviceTreeNode devNode = supportedDevices->getItem(ui.cmbDevice->currentIndex());
	int k = 0;
	for (int j = 0; j < 8; j++) {
		k = devNode.ModulesIndex[j];
		if (k != -1) {
			ui.cmbModuleIndex->addItem(QString("%1").arg(k));
		} else {
			break;
		}
	}
	ui.cmbModuleIndex->setCurrentIndex(0);

	ErrorCode errorCode = Success;
	selected.ModuleIndex = ui.cmbModuleIndex->currentIndex();
	errorCode = timerPulseCtrl->setSelectedDevice(selected);
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
    int channelCountMax = timerPulseCtrl->getFeatures()->getChannelCountMax();
    Array<CounterCapability> * counterCap;
    int itemCount;

	for (int i = 0; i < channelCountMax; i++) {
		   itemCount = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
         counterCap = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i);
         for (int j = 0; j < itemCount; j++) {
			   if (TimerPulse == counterCap->getItem(j)) {
				ui.cmbCounterChannel->addItem(QString("%1").arg(i));	
            }
        }
    }
    ui.cmbCounterChannel->setCurrentIndex(0);

   timerPulseCtrl->Dispose();
	supportedDevices->Dispose();
}

void ConfigureDialog::ModuleIndexChanged(int index) {
	ui.cmbCounterChannel->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

	TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();

	ErrorCode errorCode = Success;
	selected.ModuleIndex = ui.cmbModuleIndex->currentIndex();
	errorCode = timerPulseCtrl->setSelectedDevice(selected);
	CheckError(errorCode); 
	
	// Set channel start combo box
    int channelCountMax = timerPulseCtrl->getFeatures()->getChannelCountMax();
    Array<CounterCapability> * counterCap;
    int itemCount;

	for (int i = 0; i < channelCountMax; i++) {
		   itemCount = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
         counterCap = timerPulseCtrl->getFeatures()->getCapabilities()->getItem(i);
        for (int j = 0; j < itemCount; j++) {
			   if (TimerPulse == counterCap->getItem(j)) {
				ui.cmbCounterChannel->addItem(QString("%1").arg(i));	
            }
        }
    }
    ui.cmbCounterChannel->setCurrentIndex(0);

    timerPulseCtrl->Dispose();
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
	TimerPulseCtrl* timerPulseCtrl = TimerPulseCtrl::Create();

	ErrorCode errorCode = timerPulseCtrl->setSelectedDevice(selected);
	CheckError(errorCode); 

	configure.deviceName = ui.cmbDevice->currentText();
	configure.channel = ui.cmbCounterChannel->currentText().toInt();
	configure.moduleIndex = ui.cmbModuleIndex->currentText().toInt();

	timerPulseCtrl->Dispose();
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
