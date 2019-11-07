#ifndef ASYNCHRONOUSONEBUFFEREDAI_H
#define ASYNCHRONOUSONEBUFFEREDAI_H

#include <QtWidgets/QWidget>
#include "ui_asynchronousonebufferedai.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class AI_AsynchronousOneBufferedAi : public QDialog
{
	Q_OBJECT
public:
	AI_AsynchronousOneBufferedAi(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AI_AsynchronousOneBufferedAi();
	void Initialize();
	
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}

	void ConfigureDevice();
	void ConfigureGraph();
	void InitializeList();
	void SetXCord();
	void CheckError(ErrorCode errorCode);

   static void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam);

signals:
	void UpdateButton();

private:
	Ui::AI_AsynchronousOneBufferedAiClass ui;
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
	void ButtonEnable();
};
#endif // ASYNCHRONOUSONEBUFFEREDAI_H
