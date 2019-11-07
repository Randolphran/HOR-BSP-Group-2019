#ifndef CONTINUECOMPARE_H
#define CONTINUECOMPARE_H

#include <QDialog>
#include <QTimer>
#include "ui_continuecompare.h"
#include "configuredialog.h"

enum TabSel {
	dispersed = 0,
	lined
};

struct LineTabParam {
	quint64 firstValue;
	quint64 increment;
	quint64 count;
};

class ContinueCompare : public QDialog
{
	Q_OBJECT
public:
	ContinueCompare(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~ContinueCompare();

	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}

	void CreateDisperseTable(int tabIndex, int CompTab[]);
	void CreateLineTable(int tabIndex, LineTabParam& param);

   static void BDAQCALL OnUdCounterEvent(void * sender, UdCntrEventArgs * args, void * userParam);

private:
	Ui::ContinueCompareClass ui;
	UdCounterCtrl* udCounterCtrl;
	ConfigureDialog *configDialog;
	ConfigureParameter configure;
	QTimer *timer;

	void EnableCompareTable(bool enabled);

public:
	int  m_tabIndex;
	TabSel m_contCompTabSel;
   int m_matchCount;
   int m_endCount;
	int m_counterValue;

private slots:
	void TimerTicked();
	void ButtonStartClicked();
	void ButtonStopClicked();
	void ButtonConfigureClicked();
};

#endif // CONTINUECOMPARE_H
