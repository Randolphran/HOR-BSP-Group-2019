#ifndef DIPATTERNMATCHINTERRUPT_H
#define DIPATTERNMATCHINTERRUPT_H

#include <QDialog>
#include <QMovie>
#include "configuredialog.h"
#include "ui_dipatternmatchinterrupt.h"

class DIPatternMatchInterrupt : public QDialog
{
	Q_OBJECT
public:
	DIPatternMatchInterrupt(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~DIPatternMatchInterrupt();
	void Initialize();
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);

   static void BDAQCALL OnDiSnapEvent(void *sender, DiSnapEventArgs * args, void * userParam);

signals:
	void DataHandler_sg(QString valueString);

private:
	Ui::DIPatternMatchInterruptClass ui;
	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
	InstantDiCtrl * instantDiCtrl;

	int matchedNum;
	QMovie *movie;

private slots:
	void ButtonConfigureClicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void DataHandler2(QString valueString);
};

#endif // DIPATTERNMATCHINTERRUPT_H
