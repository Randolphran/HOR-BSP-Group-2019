#ifndef ASYNONEBUFFEREDAI_TDTR_H
#define ASYNONEBUFFEREDAI_TDTR_H

#include <QtWidgets/QDialog>
#include "ui_asynonebufferedai_tdtrtp.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class AsynOneBufferedAI_TDtrtp : public QDialog
{
	Q_OBJECT
public:
	AsynOneBufferedAI_TDtrtp(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AsynOneBufferedAI_TDtrtp();
	void Initialize();
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}
	void ConfigureDevice();
	void ConfigureGraph();
	void ConfigureGraph(int samplesCountPerChan);
	void InitializeList();
	void SetXCord();
	void CheckError(ErrorCode errorCode);
   void SetTriggerPointFlagLoacation(int delayCount);
   int  GetArrowXCordRelativeWidth(int dataCount, int delayCount, int pixelCount);

   static void BDAQCALL OnStoppedEvent(void *sender, BfdAiEventArgs *args, void *userParam); 
signals:
	void UpdateButton();
   void UpdateGraph(int samplesCountPerChan);
   void updateTriggerFlag();

private:
	Ui::AsynOneBufferedAI_TDtrClass ui;
	SimpleGraph *graph;
	ConfigureDialog *configureDialog;
	ConfigureParameter configure;
   WaveformAiCtrl * waveformAiCtrl;
	double *scaledData;
	TimeUnit timeUnit;
	static const int sectionCount = 1;

   int dataReadyCount;
   bool isTriggerSupported;
   bool isSourceNone;

private slots:
	void ShiftValueChanged(int value);
	void DivValueChanged(int value);
	void ButtonConfigureClicked();
	void ButtonGetDataClicked();

	void ButtonEnable();
   void GraphInitialize(int samplesCountPerChan);
   void TriggerFlag();
};

#endif // ASYNONEBUFFEREDAI_TDTR_H
