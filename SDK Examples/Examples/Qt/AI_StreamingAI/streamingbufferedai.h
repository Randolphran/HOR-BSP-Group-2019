#ifndef STREAMINGBUFFEREDAI_H
#define STREAMINGBUFFEREDAI_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include "ui_streamingbufferedai.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class AI_StreamingBufferedAi : public QDialog
{
	Q_OBJECT
public:
	AI_StreamingBufferedAi(QDialog *parent = 0, Qt::WindowFlags flags = 0);
	~AI_StreamingBufferedAi();
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
	Ui::AI_StreamingBufferedAiClass ui;
	SimpleGraph *graph;
	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
    WaveformAiCtrl * waveformAiCtrl;
	double *scaledData;

	static const int sectionCount = 0;	
	int rawDataBufferLength;
	TimeUnit timeUnit;
   double xInc;
	
	private slots:
		void DivValueChanged(int value);
		void ButtonConfigureClicked();
		void ButtonStartClicked();
		void ButtonPauseClicked();
		void ButtonStopClicked();
};

#endif // STREAMINGBUFFEREDAI_H
