#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

using namespace Automation::BDaq;

struct ConfigureParameter 
{
	QString deviceName;
	int selectedPort;
   quint8 enabledChannels;
	quint8 pmValue;
	const wchar_t* profilePath;
};

class ConfigureDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigureDialog(QWidget *parent = 0);
	~ConfigureDialog();
	void Initailization();
	void InitializePortState();
	void CheckError(ErrorCode errorCode);
	ConfigureParameter GetConfigureParameter(){return configure;}

private:
	Ui::ConfigureDialog ui;
	ConfigureParameter configure;

	quint8 enableChannels;
   quint8 pmValue;

	QString strs[2];
	QButtonGroup* buttonGroup0;
	QButtonGroup* buttonGroup1;
	QPushButton* buttons[2][8];
	int buttonsTags[2][8];

private slots:
	void DeviceChanged(int index);
	void cmbDIportChanged(int index);
	void Buttons0Clicked(int id);
	void Buttons1Clicked(int id);
	void ButtonOKClicked();
	void ButtonCancelClicked();
	void ButtonBrowseClicked();
};

#endif // CONFIGUREDIALOG_H
