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

	this->buttonGroup0 = new QButtonGroup();
	this->buttonGroup0->addButton(ui.btn00, 0);
	this->buttonGroup0->addButton(ui.btn01, 1);
	this->buttonGroup0->addButton(ui.btn02, 2);
	this->buttonGroup0->addButton(ui.btn03, 3);
	this->buttonGroup0->addButton(ui.btn04, 4);
	this->buttonGroup0->addButton(ui.btn05, 5);
	this->buttonGroup0->addButton(ui.btn06, 6);
	this->buttonGroup0->addButton(ui.btn07, 7);
	this->buttonGroup0->setExclusive(false);

	this->buttonGroup1 = new QButtonGroup();
	this->buttonGroup1->addButton(ui.btn10, 0);
	this->buttonGroup1->addButton(ui.btn11, 1);
	this->buttonGroup1->addButton(ui.btn12, 2);
	this->buttonGroup1->addButton(ui.btn13, 3);
	this->buttonGroup1->addButton(ui.btn14, 4);
	this->buttonGroup1->addButton(ui.btn15, 5);
	this->buttonGroup1->addButton(ui.btn16, 6);
	this->buttonGroup1->addButton(ui.btn17, 7);
	this->buttonGroup1->setExclusive(false);

	buttons[0][0] = ui.btn00;
	buttons[0][1] = ui.btn01;
	buttons[0][2] = ui.btn02;
	buttons[0][3] = ui.btn03;
	buttons[0][4] = ui.btn04;
	buttons[0][5] = ui.btn05;
	buttons[0][6] = ui.btn06;
	buttons[0][7] = ui.btn07;

	buttons[1][0] = ui.btn10;
	buttons[1][1] = ui.btn11;
	buttons[1][2] = ui.btn12;
	buttons[1][3] = ui.btn13;
	buttons[1][4] = ui.btn14;
	buttons[1][5] = ui.btn15;
	buttons[1][6] = ui.btn16;
	buttons[1][7] = ui.btn17;

	strs[0] = "background:url(:/DIPatternMatchInterrupt/Resources/ButtonUp.png)";
	strs[1] = "background:url(:/DIPatternMatchInterrupt/Resources/ButtonDown.png)";
	
	connect(ui.cmbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(DeviceChanged(int)));
	connect(ui.cmbDIport, SIGNAL(currentIndexChanged(int)), this, SLOT(cmbDIportChanged(int)));
	connect(buttonGroup0, SIGNAL(buttonClicked(int)), this, SLOT(Buttons0Clicked(int)));
	connect(buttonGroup1, SIGNAL(buttonClicked(int)), this, SLOT(Buttons1Clicked(int)));
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
   InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
   Array<DeviceTreeNode> *supportedDevices = instantDiCtrl->getSupportedDevices();

	if (supportedDevices->getCount() == 0)
	{
		QMessageBox::information(this, tr("Warning Information"), 
			tr("No device to support the currently demonstrated function!"));
		QCoreApplication::quit();
	} else {
		for (int i = 0; i < supportedDevices->getCount(); i++) {
			DeviceTreeNode const &node = supportedDevices->getItem(i);
			qDebug("%d, %ls\n", node.DeviceNumber, node.Description);

			DeviceInformation devInfo(node.Description, ModeRead);
			instantDiCtrl->setSelectedDevice(devInfo);

			Array<DiPmintPort>* diPmintPorts = instantDiCtrl->getDiPmintPorts();
			if (diPmintPorts == NULL) {
                continue;
            }

			ui.cmbDevice->addItem(QString::fromWCharArray(node.Description));
		}
		ui.cmbDevice->setCurrentIndex(0);	
	}
	configure.profilePath = L"";
	instantDiCtrl->Dispose();
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
	ui.cmbDIport->clear();
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());
	
	InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
	ErrorCode errorCode = instantDiCtrl->setSelectedDevice(selected);
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

    //set the DI port
	 Array<DiPmintPort>* diPmintPorts = instantDiCtrl->getDiPmintPorts();
    int PmPortCount = diPmintPorts->getCount();
    int portNumber = 0;
	 for (int i = 0; i < PmPortCount; i++) {
		 portNumber = diPmintPorts->getItem(i).getPort();
		 ui.cmbDIport->addItem(QString("%1").arg(portNumber));
	}

    ui.cmbDIport->setCurrentIndex(0);
    instantDiCtrl->Dispose();  
	 InitializePortState();
}

void ConfigureDialog::cmbDIportChanged(int index) {
	InitializePortState();
}

void ConfigureDialog::InitializePortState() {
	enableChannels = 0;
   pmValue = 0xFF;

	ui.txtenableChan->setText(QString::number(enableChannels, 16).toUpper());
	ui.edtpmValue->setText(QString::number(pmValue, 16).toUpper());

	for (int i = 0; i < 8; i++) {
		buttons[0][i]->setStyleSheet(strs[0]);
		buttonsTags[0][i] = 0;
	}

	for (int i = 0; i < 8; i++) {
		buttons[1][i]->setStyleSheet(strs[1]);
		buttonsTags[1][i] = 1;
	}

}

void ConfigureDialog::Buttons0Clicked(int id) {
	int i = 0, data = 1, bitValue;

	bitValue = buttonsTags[0][id];

	while (i < id) {
        data = data * 2;
        i++;
    }

	if (bitValue == 0) {
		enableChannels = enableChannels + data;
		buttons[0][id]->setStyleSheet(strs[1]);
		buttonsTags[0][id] = 1;
	} else {
		enableChannels = enableChannels - data;
		buttons[0][id]->setStyleSheet(strs[0]);
		buttonsTags[0][id] = 0;
	}

	ui.txtenableChan->setText(QString::number(enableChannels, 16).toUpper());
}

void ConfigureDialog::Buttons1Clicked(int id) {
	int i = 0, data = 1, bitValue;

	bitValue = buttonsTags[1][id];

	while (i < id) {
        data = data * 2;
        i++;
    }

	if (bitValue == 0) {
		pmValue = pmValue + data;
		buttons[1][id]->setStyleSheet(strs[1]);
		buttonsTags[1][id] = 1;
	} else {
		pmValue = pmValue - data;
		buttons[1][id]->setStyleSheet(strs[0]);
		buttonsTags[1][id] = 0;
	}
	ui.edtpmValue->setText(QString::number(pmValue, 16).toUpper());
}

void ConfigureDialog::ButtonOKClicked()
{
	if (ui.cmbDevice->count() == 0)
	{
		QCoreApplication::quit();
	}

	if (this->enableChannels == 0) {
		QMessageBox::information(this, "Warning Information", "Please enable at lest one channel!");
		return;
	}
    std::wstring description = ui.cmbDevice->currentText().toStdWString();
    DeviceInformation selected(description.c_str());

	InstantDiCtrl * instantDiCtrl = InstantDiCtrl::Create();
	ErrorCode errorCode = instantDiCtrl->setSelectedDevice(selected);
	CheckError(errorCode); 

	configure.deviceName = ui.cmbDevice->currentText();
	configure.selectedPort = ui.cmbDIport->currentText().toInt();
	configure.enabledChannels = this->enableChannels;
	configure.pmValue = this->pmValue;

	instantDiCtrl->Dispose();
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
	configure.profilePath = reinterpret_cast<const wchar_t *>(str.utf16());
}
