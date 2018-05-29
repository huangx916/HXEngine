#include "HXEditorWin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HXEditorWin w;
	w.show();
	return a.exec();
}
