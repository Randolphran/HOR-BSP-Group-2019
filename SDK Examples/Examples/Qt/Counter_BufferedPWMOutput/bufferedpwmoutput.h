#ifndef PWMOUTPUT_H
#define PWMOUTPUT_H

#include <QDialog>
#include <QMovie>
#include "ui_bufferedpwmoutput.h"
#include "configuredialog.h"

class BufferedPWMOutput : public QDialog
{
	Q_OBJECT

public:
    BufferedPWMOutput(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~BufferedPWMOutput();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
    //static void BDAQCALL OnBfdCntrEvent(void *sender, BfdCntrEventArgs *args, void * userParam);

private:
    Ui::BufferedPWMOutputClass ui;
    BufferedPwModulatorCtrl* bfdPwModulatorCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QMovie *movie;
    int8*  channelEnable;
    int32  intervalCount;
    int32  samples;
    int32  channelCountMax;
    PulseWidth* pulseWidth;

private slots:
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
};

#endif // PWMOUTPUT_H
