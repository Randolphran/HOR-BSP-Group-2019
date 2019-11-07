#ifndef PULSEOUTPUTWITHTIMERINTERRUPT_H
#define PULSEOUTPUTWITHTIMERINTERRUPT_H

#include <QDialog>
#include <QMovie>
#include "ui_pulseoutputwithtimerinterrupt.h"
#include "configuredialog.h"

class PulseOutputwithTimerInterrupt : public QDialog
{
	Q_OBJECT
public:
	PulseOutputwithTimerInterrupt(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~PulseOutputwithTimerInterrupt();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
 
   static void BDAQCALL OnCounterEvent(void *sender, CntrEventArgs *args, void * userParam);

private:
	Ui::PulseOutputwithTimerInterruptClass ui;
	TimerPulseCtrl* timerPulseCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	int eventCount;
	QMovie *movie;

private slots:
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
};

#endif // PULSEOUTPUTWITHTIMERINTERRUPT_H
