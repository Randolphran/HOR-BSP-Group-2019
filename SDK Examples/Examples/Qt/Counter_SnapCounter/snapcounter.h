#ifndef SNAPCOUNTER_H
#define SNAPCOUNTER_H

#include <QDialog>
#include <QTimer>
#include "ui_snapcounter.h"
#include "configuredialog.h"

class SnapCounter : public QDialog
{
	Q_OBJECT
public:
	SnapCounter(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~SnapCounter();
	void Initialize();
	void ConfigureDevice();
	void ConfiguratePanel();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

   static void BDAQCALL OnCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam);
	
   void EventIDtoString(EventId id,QString &str);
	void CheckTimerUsingParam(EventId id,int & timerChan,bool & isTimerUsing);

private:
	Ui::SnapCounterClass ui;
	UdCounterCtrl* udCounterCtrl;
	TimerPulseCtrl *m_timerPulseCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QTimer *timer;

	bool m_isTimerUsing;
   int  m_snapCount;

	QList<QListWidgetItem *> aryListBoxSrcSel;

private slots:
	void TimerTicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
	void SnapSrcSelChanged();
};

#endif // SNAPCOUNTER_H
