#include "asynonebufferedai_tdtp.h"
#include "configuredialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AsynOneBufferedAI_TDtp w;
	ConfigureDialog dialog;
	int resultDialog = dialog.exec();
	if (resultDialog == QDialog::Rejected) {
		a.exit(0);
		return 0;
	} else if (resultDialog == QDialog::Accepted) {
		w.SetConfigureDialog(&dialog);
		w.SetConfigureParameter(dialog.GetConfigureParameter());
		w.Initialize();
		w.show();
	}
	return a.exec();
}
