#ifndef DELAYEDPULSEGENERATION_H
#define DELAYEDPULSEGENERATION_H

#include <QDialog>
#include <QMovie>
#include "ui_delayedpulsegeneration.h"
#include "configuredialog.h"

class DelayedPulseGeneration : public QDialog
{
	Q_OBJECT

public:
	DelayedPulseGeneration(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~DelayedPulseGeneration();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
 
   static void BDAQCALL OnCounterEvent(void *sender, CntrEventArgs *args, void * userParam);

private:
	Ui::DelayedPulseGenerationClass ui;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	OneShotCtrl * oneShotCtrl;
   int DelayedPulseCount;
   int countOfValue;
	QMovie *movie;

signals:
   void DelayCountValue();

private slots:
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked(); 
   void TextDelayCount();
};

#endif // DELAYEDPULSEGENERATION_H
