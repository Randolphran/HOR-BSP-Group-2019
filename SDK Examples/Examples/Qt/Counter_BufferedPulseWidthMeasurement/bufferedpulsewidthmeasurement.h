#ifndef BUFFEREDPULSEWIDTHMEASUREMENT_H
#define BUFFEREDPULSEWIDTHMEASUREMENT_H

#include <QDialog>
#include "ui_bufferedpulsewidthmeasurement.h"
#include "configuredialog.h"

class BufferedPulseWidthMeasurement : public QDialog
{
	Q_OBJECT
signals:
    void refreshUI(int);
    void refreshStatus(int);

public:
    BufferedPulseWidthMeasurement(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~BufferedPulseWidthMeasurement();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
    void ChannelStatusStringChange(int32 channel, QString string);
    void DisplayChannelStatus(int channel);
    void DisplayChannelValue(int channel);
    void CopyChannelData(int channel);
    static void BDAQCALL OnBfdPwMeterEvent(void *sender, BfdCntrEventArgs *args, void * userParam);
    static void BDAQCALL OnBfdPWMeterStoppedEvent(void *sender, BfdCntrEventArgs *args, void * userParam);

private:
    Ui::BufferedPulseWidthMeasurementClass ui;
    BufferedPwMeterCtrl* bfdPwMeterCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
    PulseWidth* dataBuf;
    PulseWidth** chs_dataBuf;
    QString* chs_Status;

    int8*  channelEnable;
    int32  sectionLength;
    int32  sectionCount;
    int32  samples;
    int32  eventChannel;  // event occured channel
    int32  displayedChannel; // which channel' value want to display.
    int32  channelCountMax;

    bool isRunning;
    bool haveData;

private slots:
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
    void onRefreshUI(int);
    void onRefreshStatus(int);
    void onDisplayedChannelChanged();
};

#endif // BUFFEREDPULSEWIDTHMEASUREMENT_H
