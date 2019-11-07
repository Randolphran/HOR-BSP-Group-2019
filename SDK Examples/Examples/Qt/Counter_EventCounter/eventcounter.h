#ifndef EVENTCOUNTER_H
#define EVENTCOUNTER_H

#include <QDialog>
#include <QTimer>
#include "ui_eventcounter.h"
#include "configuredialog.h"

class EventCounter : public QDialog
{
	Q_OBJECT

public:
	EventCounter(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~EventCounter();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

private:
	Ui::EventCounterClass ui;
	EventCounterCtrl* eventCounterCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QTimer *timer;
	bool ECisRunning;
    bool isEventCountingReset;

private slots:
	void TimerTicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
};

#endif // EVENTCOUNTER_H
