#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

struct ConfigureParameter 
{
	QString deviceName;
	int channelCount;
	int channelStart;
	ValueRange valueRange;
	int pointCountPerWave;
	double clockRate;
	const wchar_t* profilePath;
};

class ConfigureDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigureDialog(QWidget *parent = 0);
	~ConfigureDialog();
	void Initailization();
	void CheckError(ErrorCode errorCode);
	ConfigureParameter GetConfigureParameter(){return configure;}

private:
	Ui::ConfigureDialog ui;
	ConfigureParameter configure;

	private slots:
		void DeviceChanged(int index);
		void ButtonOKClicked();
		void ButtonCancelClicked();
		void ButtonBrowseClicked();
};

#endif // CONFIGUREDIALOG_H
