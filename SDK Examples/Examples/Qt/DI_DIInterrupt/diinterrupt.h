#ifndef DIINTERRUPT_H
#define DIINTERRUPT_H

#include <QDialog>
#include <QMovie>
#include "configuredialog.h"
#include "ui_diinterrupt.h"

class DIInterrupt : public QDialog
{
	Q_OBJECT
public:
	DIInterrupt(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~DIInterrupt();

	void Initialize();
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);

   static void BDAQCALL OnDiSnapEvent(void * sender, DiSnapEventArgs * args, void *userParam);
signals:
	void DataHandler_sg(qint32 srcNum, QString valueString);

private:
	Ui::DIInterruptClass ui;

	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
	InstantDiCtrl * instantDiCtrl;

	QMovie *movie;

private slots:
	void ButtonConfigureClicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void DataHandler2(qint32 srcNum, QString valueString);
};

#endif // DIINTERRUPT_H
