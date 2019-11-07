#ifndef UPDOWNCOUNTER_H
#define UPDOWNCOUNTER_H

#include <QDialog>
#include <QTimer>
#include "ui_updowncounter.h"
#include "configuredialog.h"

class UpDownCounter : public QDialog
{
	Q_OBJECT

public:
	UpDownCounter(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~UpDownCounter();

	void Initialize();
	void ConfigureDevice();
	void ConfiguratePanel();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

private:
	Ui::UpDownCounterClass ui;
	UdCounterCtrl* udCounterCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QTimer *timer;

	QButtonGroup* buttonGroup1;

	quint32 cntrValue;

private slots:
	void TimerTicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
	void ButtonResetValueClicked();
	void ResetIndexChged(int);
	void CmbResetValueChanged();
};

#endif // UPDOWNCOUNTER_H
