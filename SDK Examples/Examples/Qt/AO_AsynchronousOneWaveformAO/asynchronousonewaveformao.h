#ifndef ASYNCHRONOUSONEWAVEFORMAO_H
#define ASYNCHRONOUSONEWAVEFORMAO_H

#include <QDialog>
#include <QCloseEvent>
#include "ui_asynchronousonewaveformao.h"
#include "configuredialog.h"
#include "../common/WaveformGenerator.h"

class AsynchronousOneWaveformAO : public QDialog
{
	Q_OBJECT
public:
	AsynchronousOneWaveformAO(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~AsynchronousOneWaveformAO();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
	void ConfigurePanel();
	void InitialButtons();

   static void BDAQCALL OnStoppedEvent(void *sender, BfdAoEventArgs * args, void * userParam);
signals:
	void stopppedHandler();

protected:
	void closeEvent(QCloseEvent* e);

private:
	Ui::AsynchronousOneWaveformAOClass ui;
	ConfigureDialog* configDialog;
	ConfigureParameter configure;
	BufferedAoCtrl * bfdAoCtrl;
	double* dataScaled;
	WaveformParameter m_waveParam[2];
	WaveformGenerator *waveformGenerator;
	bool m_waveSeled[2];
	QPushButton* buttons[6];
	bool formCloseFlag;

	QString strs[6];
	QButtonGroup* buttonGroup1;

private slots:
	void ButtonConfigureClicked();
	void ButtonStartClicked();
	void WaveButtonClicked(int id);
	void stopped();
};

#endif // ASYNCHRONOUSONEWAVEFORMAO_H
