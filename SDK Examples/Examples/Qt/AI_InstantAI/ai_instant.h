#ifndef AI_INSTANT_H
#define AI_INSTANT_H

#include <QtWidgets/QDialog>
#include <QtCore/QtCore>
#include <QTimer>
#include "ui_ai_instant.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class AI_Instant : public QDialog
{
	Q_OBJECT

public:
	AI_Instant(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AI_Instant();

	void Initialize();
	void ConfigureDevice();
	void ConfigureGraph();
	void CheckError(ErrorCode errorCode);
	void RefreshList();
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

private:
	Ui::AI_InstantFrame ui;
	SimpleGraph *graph;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	InstantAiCtrl *instantAiCtrl;
	double scaledData[16];
	QTimer *timer;

private slots:
	void TimerTicked();
	void SliderValueChanged(int value);
	void ButtonStartClicked();
	void ButtonConfigureClicked();
	void ButttonPauseClicked();
	void ButtonStopClicked();
};

#endif // AI_INSTANT_H
