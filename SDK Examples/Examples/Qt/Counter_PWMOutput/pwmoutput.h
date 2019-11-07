#ifndef PWMOUTPUT_H
#define PWMOUTPUT_H

#include <QDialog>
#include <QMovie>
#include "ui_pwmoutput.h"
#include "configuredialog.h"

class PWMOutput : public QDialog
{
	Q_OBJECT

public:
	PWMOutput(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~PWMOutput();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

private:
	Ui::PWMOutputClass ui;
	PwModulatorCtrl* pwModulatorCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QMovie *movie;

private slots:
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
};

#endif // PWMOUTPUT_H
