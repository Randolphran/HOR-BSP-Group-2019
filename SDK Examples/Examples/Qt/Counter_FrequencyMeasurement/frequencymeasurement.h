#ifndef FREQUENCYMEASUREMENT_H
#define FREQUENCYMEASUREMENT_H

#include <QDialog>
#include <QTimer>
#include "ui_frequencymeasurement.h"
#include "configuredialog.h"	
#include "../common/simplegraph.h"

class FrequencyMeasurement : public QDialog
{
	Q_OBJECT

public:
	FrequencyMeasurement(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~FrequencyMeasurement();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
	void InitializeGraph();
    void InitializeYAxis();
	QString FormatFreqString(double freqHz);

private:
	Ui::FrequencyMeasurementClass ui;
	FreqMeterCtrl* freqMeterCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	SimpleGraph *graph;
	double m_yaxisMax;
   double frequency[1];
	bool isCounterReseted;
	QTimer *timer;

private slots:
	void TimerTicked();
	void timerTrackBarChanged(int value);
	void EnlargeClicked();
	void ShortenClicked();
	void ButtonStartClicked();
	void ButtonConfigureClicked();
	void ButttonPauseClicked();
	void ButtonStopClicked();
};

#endif // FREQUENCYMEASUREMENT_H
