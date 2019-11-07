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
   UdCounterCtrl* udCounterCtrl = UdCounterCtrl::Create();
   Array<DeviceTreeNode> *supportedDevices = udCounterCtrl->getSupportedDevices();

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
	supportedDevices->Dispose();
	udCounterCtrl->Dispose();
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
	ui.cmbCountingType->clear();

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    UdCounterCtrl* udCounterCtrl = UdCounterCtrl::Create();

	ErrorCode errorCode = udCounterCtrl->setSelectedDevice(selected);
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
    int channelCountMax = udCounterCtrl->getFeatures()->getChannelCountMax();
    Array<CounterCapability> * counterCap;
    int itemCount;

	for (int i = 0; i < channelCountMax; i++) {
		  itemCount = udCounterCtrl->getFeatures()->getCapabilities()->getItem(i)->getCount();
        counterCap = udCounterCtrl->getFeatures()->getCapabilities()->getItem(i);
        for (int j = 0; j < itemCount; j++) {
			   if (UpDownCount == counterCap->getItem(j)) {
				   ui.cmbCounterChannel->addItem(QString("%1").arg(i));	
            }
        }
    }
    ui.cmbCounterChannel->setCurrentIndex(0);

	// Set Counting type for selected device
	int cntTypeCount = udCounterCtrl->getFeatures()->getUdCountingTypes()->getCount();
	Array<CountingType> * counttingType = udCounterCtrl->getFeatures()->getUdCountingTypes();

	wchar_t strType[32] = {0};
	QString typeName = "CountingType";
	const wchar_t * strTypeName = reinterpret_cast<const wchar_t *>(typeName.utf16());
	for (int i = 0; i < cntTypeCount; ++i) {
		AdxEnumToString(strTypeName,counttingType->getItem(i),32,strType);
		ui.cmbCountingType->addItem(QString::fromWCharArray(strType));
	}
	ui.cmbCountingType->setCurrentIndex(0);

    udCounterCtrl->Dispose();
	counttingType->Dispose(); 
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
    UdCounterCtrl* udCounterCtrl = UdCounterCtrl::Create();

	ErrorCode errorCode = udCounterCtrl->setSelectedDevice(selected);
	CheckError(errorCode); 
    Array<CountingType> * counttingType = udCounterCtrl->getFeatures()->getUdCountingTypes();

	configure.deviceName = ui.cmbDevice->currentText();
	configure.channel = ui.cmbCounterChannel->currentText().toInt();
	configure.cntType = counttingType->getItem(ui.cmbCountingType->currentIndex());

	udCounterCtrl->Dispose();
	counttingType->Dispose();
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
