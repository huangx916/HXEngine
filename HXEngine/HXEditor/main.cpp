#include "HXEditorWin.h"
#include <QApplication>
//#include <QStyleFactory>
//#include "vgl.h"

int main(int argc, char *argv[])
{
	/*QStringList lt = QStyleFactory::keys();
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	QApplication::setPalette(QApplication::style()->standardPalette());*/
	QApplication a(argc, argv);
	//glutInit(&argc, argv);
	HXEditorWin::GetInstance()->show();

	return a.exec();
}
