#ifndef SYNCHRONOUSONEBUFFEREDAI_H
#define SYNCHRONOUSONEBUFFEREDAI_H

#include <QtWidgets/QWidget>
#include "ui_synchronousonebufferedai.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class AI_SynchronousOneBufferedAi : public QDialog
{
	Q_OBJECT

public:
	AI_SynchronousOneBufferedAi(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AI_SynchronousOneBufferedAi();
	void Initialize();
	
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}

private:
	void ConfigureDevice();
	void ConfigureGraph();
	void InitializeList();
	void SetXCord();
	void CheckError(ErrorCode errorCode);

private:
	Ui::AI_SynchronousOneBufferedAiClass ui;
	SimpleGraph *graph;
	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
   WaveformAiCtrl * waveformAiCtrl;
	double *scaledData;
	TimeUnit timeUnit;

	static const int sectionCount = 1;

private slots:
	void ShiftValueChanged(int value);
	void DivValueChanged(int value);
	void ButtonConfigureClicked();
	void ButtonGetDataClicked();
};

#endif // SYNCHRONOUSONEBUFFEREDAI_H
