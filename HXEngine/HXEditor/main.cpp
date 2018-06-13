#include "HXEditorWin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//glutInit(&argc, argv);
	HXEditorWin w;
	w.show();

	return a.exec();
}
