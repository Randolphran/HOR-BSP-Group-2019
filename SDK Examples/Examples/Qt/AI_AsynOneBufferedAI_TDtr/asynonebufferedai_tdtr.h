#ifndef ASYNONEBUFFEREDAI_TDTR_H
#define ASYNONEBUFFEREDAI_TDTR_H

#include <QtWidgets/QDialog>
#include "ui_asynonebufferedai_tdtr.h"
#include "../common/simplegraph.h"
#include "configuredialog.h"

class AsynOneBufferedAI_TDtr : public QDialog
{
	Q_OBJECT
public:
	AsynOneBufferedAI_TDtr(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AsynOneBufferedAI_TDtr();
	void Initialize();
	void SetConfigureDialog(ConfigureDialog * dialog){configureDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){configure = value;}
	void ConfigureDevice();
	void ConfigureGraph();
	void InitializeList();
	void SetXCord();
	void CheckError(ErrorCode errorCode);

   static void BDAQCALL OnStoppedEvent(void *sender, BfdAiEventArgs *args, void * userParam);

signals:
	void UpdateButton();

private:
	Ui::AsynOneBufferedAI_TDtrClass ui;
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

#endif // ASYNONEBUFFEREDAI_TDTR_H
