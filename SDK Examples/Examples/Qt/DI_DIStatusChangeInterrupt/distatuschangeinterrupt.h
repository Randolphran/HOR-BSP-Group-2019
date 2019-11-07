#ifndef DISTATUSCHANGEINTERRUPT_H
#define DISTATUSCHANGEINTERRUPT_H

#include <QDialog>
#include <QMovie>
#include "configuredialog.h"
#include "ui_distatuschangeinterrupt.h"

class DIStatusChangeInterrupt : public QDialog
{
	Q_OBJECT
public:
	DIStatusChangeInterrupt(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~DIStatusChangeInterrupt();
	void Initialize();
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);

   static void BDAQCALL OnDiSnapEvent(void *sender, DiSnapEventArgs * args, void * userParam);

signals:
	void DataHandler_sg(QString valueString);

private:
	Ui::DIStatusChangeInterruptClass ui;
	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
	InstantDiCtrl * instantDiCtrl;
   int changedNum;	

	QMovie *movie;

private slots:
	void ButtonConfigureClicked();
	void ButtonStartClicked();
	void ButtonStopClicked();

	void DataHandler2(QString valueString);
};

#endif // DISTATUSCHANGEINTERRUPT_H
