#ifndef STREAMINGAI_TDTR_H
#define STREAMINGAI_TDTR_H

#include <QDialog>
#include <QMessageBox>
#include "ui_streamingai_retrigger.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class StreamingAI_Retrigger : public QDialog
{
	Q_OBJECT
public:
	StreamingAI_Retrigger(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~StreamingAI_Retrigger();
	void Initialize();

	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}

	void ConfigureDevice();
	void ConfigureGraph();
	void InitializeList();
	void SetXCord();
	void CheckError(ErrorCode errorCode);

   static void BDAQCALL OnDataReadyEvent(void * sender, BfdAiEventArgs * args, void * userParam);
   static void BDAQCALL OnOverRunEvent(void * sender, BfdAiEventArgs * args, void * userParam);
   static void BDAQCALL OnCacheOverflowEvent(void * sender, BfdAiEventArgs * args, void * userParam);
   static void BDAQCALL OnStoppedEvent(void * sender, BfdAiEventArgs * args, void * userParam);

private:
	Ui::StreamingAI_Retrigger ui;
	SimpleGraph *graph;
	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
   WaveformAiCtrl * waveformAiCtrl;
	double *scaledData;
	
	int rawDataBufferLength;
	TimeUnit timeUnit;

   double xInc;
	static const int sectionCount = 0;

private slots:
	void DivValueChanged(int value);
	void ButtonConfigureClicked();
	void ButtonStartClicked();
	void ButtonPauseClicked();
	void ButtonStopClicked();
};

#endif // STREAMINGAI_TDTR_H
