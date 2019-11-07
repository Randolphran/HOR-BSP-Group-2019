#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "ui_configuredialog.h"
#include "../../../inc/bdaqctrl.h"

#define ProfileConfigre    0
#define ManualConfigure    1

using namespace Automation::BDaq;

struct ConfigureParameter 
{
    QString             deviceName;
    const wchar_t*      profilePath;
    int                 channelStart;
    int                 channelCount;
    int8*               channelEnable;
    int32               sectionLength;
    int                 sectionCount;
    SignalDrop          clkSource;
    SignalCountingType  cntType;

    //for Trigger
    double          trgLevel;
    SignalDrop      trgSource;
    ActiveSignal    trgEdge;
    TriggerAction   trgAction;

    bool            configMode; //load profile or manual configure parameters.
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
    void InitialChannelCheckBox();
    void RefreshConfigureParameter();

    int32 Max_Channel_Count;
    BufferedUdCounterCtrl* m_bfdUdCounterCtrl;

private:
	Ui::ConfigureDialog ui;
	ConfigureParameter configure;
    QHBoxLayout* m_hBoxLayout;

private slots:
    void DeviceChanged();
	void ButtonOKClicked();
	void ButtonCancelClicked();
	void ButtonBrowseClicked();
    void TrgSourceChanged();
    void onLoadProfileClicked();
    void onManualConfigureClicked();
    void onChannelChecked(bool isChecked);
};

#endif // CONFIGUREDIALOG_H
