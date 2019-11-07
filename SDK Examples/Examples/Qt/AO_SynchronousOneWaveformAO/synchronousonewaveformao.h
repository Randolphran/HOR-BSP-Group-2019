#ifndef SYNCHRONOUSONEWAVEFORMAO_H
#define SYNCHRONOUSONEWAVEFORMAO_H

#include <QDialog>
#include "ui_synchronousonewaveformao.h"
#include "configuredialog.h"
#include "../common/WaveformGenerator.h"

class SynchronousOneWaveformAO : public QDialog
{
	Q_OBJECT

public:
	SynchronousOneWaveformAO(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~SynchronousOneWaveformAO();
	void Initialize();
	void ConfigureDevice();
	void CheckError(ErrorCode errorCode);
	void SetConfigureDialog(ConfigureDialog *dialog){this->configDialog = dialog;}
	void SetConfigureParameter(ConfigureParameter value){this->configure = value;}
	void ConfigurePanel();
	void InitialButtons();

private:
	Ui::SynchronousOneWaveformAOClass ui;
	ConfigureDialog* configDialog;
	ConfigureParameter configure;
	BufferedAoCtrl * bfdAoCtrl;

	double* dataScaled;
	WaveformParameter m_waveParam[2];
	WaveformGenerator *waveformGenerator;
	bool m_waveSeled[2];
	QPushButton* buttons[6];

	QString strs[6];
	QButtonGroup* buttonGroup1;

private slots:
	void ButtonConfigureClicked();
	void ButtonStartClicked();
	void WaveButtonClicked(int id);
};

#endif // SYNCHRONOUSONEWAVEFORMAO_H
