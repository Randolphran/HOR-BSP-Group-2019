#include "distatuschangeinterrupt.h"
#include <QMessageBox>

DIStatusChangeInterrupt::DIStatusChangeInterrupt(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	//Set the minimum and close button of the main frame.
	this->setWindowFlags(Qt::WindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint));

	ui.eventDataList->setRowCount(0);
	ui.eventDataList->setColumnCount(2);
	ui.eventDataList->setColumnWidth(0, ui.eventDataList->width() / 3);
	ui.eventDataList->setColumnWidth(1, ui.eventDataList->width() * 2 / 3 - 2);

	movie = new QMovie(":/DIStatusChangeInterrupt/Resources/tambour.gif");
	ui.gifViewer->setMovie(movie);
	movie->start();
	movie->stop();

   instantDiCtrl = InstantDiCtrl::Create();
   instantDiCtrl->addChangeOfStateHandler(OnDiSnapEvent, this);

	ui.btnStop->setEnabled(false);

	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(ButtonStartClicked()));
	connect(ui.btnStop, SIGNAL(clicked()), this, SLOT(ButtonStopClicked()));
	connect(ui.btnConfig, SIGNAL(clicked()), this, SLOT(ButtonConfigureClicked()));

	connect(this, SIGNAL(DataHandler_sg(QString)), this, SLOT(DataHandler2(QString)));
}

DIStatusChangeInterrupt::~DIStatusChangeInterrupt()
{

}

void DIStatusChangeInterrupt::Initialize() {
	//set the title of the form.
	setWindowTitle(tr("DI Status Change Interrupt - Run(") + configure.deviceName + tr(")"));

	ConfigureDevice();
}

void DIStatusChangeInterrupt::ConfigureDevice() {
    std::wstring description = configure.deviceName.toStdWString();
    DeviceInformation selected(description.c_str());

	ErrorCode errorCode = Success;
	errorCode = instantDiCtrl->setSelectedDevice(selected);
	CheckError(errorCode);
	errorCode = instantDiCtrl->LoadProfile(configure.profilePath);
	CheckError(errorCode);

	QStringList strs;
	strs << tr(" Changed No#") << tr("DI ports value (Port 0~") + QString("%1").arg(instantDiCtrl->getPortCount() - 1) + tr(")");
	ui.eventDataList->setHorizontalHeaderLabels(strs);

	Array<DiCosintPort>* diCosintPorts = instantDiCtrl->getDiCosintPorts();
   int scPorts = diCosintPorts->getCount();
   for (int i = 0; i < scPorts; i++) {
        if (diCosintPorts->getItem(i).getPort() == configure.selectedPort) {
            instantDiCtrl->getDiCosintPorts()->getItem(i).setMask(configure.enabledChannels);
        }
    }
}

void DIStatusChangeInterrupt::CheckError(ErrorCode errorCode) {
    if (BioFailed(errorCode))
	{
		QString message = tr("Sorry, there are some errors occurred, Error Code: 0x") +
			QString::number(errorCode, 16).right(8).toUpper();
		QMessageBox::information(this, "Warning Information", message);
	}
}

void DIStatusChangeInterrupt::DataHandler2(QString valueString) {
	if (ui.eventDataList->rowCount() >= 8) {
		ui.eventDataList->removeRow(0);
	}

	int row = ui.eventDataList->rowCount();
	ui.eventDataList->insertRow(row);

	changedNum++;
	QTableWidgetItem *item0 = new QTableWidgetItem(QString("%1").arg(changedNum));
	item0->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	ui.eventDataList->setItem(row, 0, item0);

	QTableWidgetItem *item1 = new QTableWidgetItem(valueString);
	item1->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
	ui.eventDataList->setItem(row, 1, item1);

	ui.eventDataList->resizeRowsToContents();
}

void DIStatusChangeInterrupt::ButtonStartClicked() {
	ErrorCode errorCode = Success;
   this->changedNum = 0;

	ui.eventDataList->setRowCount(0);

	errorCode = instantDiCtrl->SnapStart();
   if (errorCode != Success) {
      CheckError(errorCode);
		QCoreApplication::exit(0);
    }

	movie->start();

	ui.btnStart->setEnabled(false);
	ui.btnConfig->setEnabled(false);
	ui.btnStop->setEnabled(true);
}

void DIStatusChangeInterrupt::ButtonStopClicked() {
	movie->stop();

	ErrorCode errorCode = Success;
	errorCode = instantDiCtrl->SnapStop();
	if (errorCode != Success) {
      CheckError(errorCode);
		QCoreApplication::exit(0);
    }

	ui.btnStart->setEnabled(true);
	ui.btnConfig->setEnabled(true);
	ui.btnStop->setEnabled(false);
}

void DIStatusChangeInterrupt::ButtonConfigureClicked() {
	int dialogResult = configureDialog->exec();
	if (dialogResult == QDialog::Accepted) {
		configure = configureDialog->GetConfigureParameter();
		Initialize();
	}	
}

void DIStatusChangeInterrupt::OnDiSnapEvent(void *sender, DiSnapEventArgs * args, void * userParam)
{
   DIStatusChangeInterrupt * uParam = (DIStatusChangeInterrupt *) userParam;
   QString valueString = "";
   for (int i = 0; i < args->Length; i++) {
      valueString = valueString + QString::number(args->PortData[i], 16).toUpper();

      if (i < args->Length - 1) {
         valueString = valueString + tr(", ");
      }
   }
   emit uParam->DataHandler_sg(valueString);
}
