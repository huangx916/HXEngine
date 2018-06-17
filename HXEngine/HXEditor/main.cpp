#include "HXEditorWin.h"
#include <QApplication>
//#include "vgl.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//glutInit(&argc, argv);
	HXEditorWin::GetInstance()->show();

	return a.exec();
}
