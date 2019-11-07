#ifndef PULSEWIDTHMEASUREMENT_H
#define PULSEWIDTHMEASUREMENT_H

#include <QDialog>
#include <QTimer>
#include "ui_pulsewidthmeasurement.h"
#include "configuredialog.h"

class PulseWidthMeasurement : public QDialog
{
	Q_OBJECT

public:
	PulseWidthMeasurement(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~PulseWidthMeasurement();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

private:
	Ui::PulseWidthMeasurementClass ui;
	PwMeterCtrl* pwMeterCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QTimer *timer;
	bool ECisRunning;
   bool isPwMeterReset;

private slots:
	void TimerTicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked(); 
};

#endif // PULSEWIDTHMEASUREMENT_H
