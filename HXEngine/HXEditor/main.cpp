#include "HXEditorWin.h"
#include <QApplication>
//#include <QStyleFactory>
//#include "vgl.h"
#include <QFile>
#include "HXWinWrap.h"

int main(int argc, char *argv[])
{
	/*QStringList lt = QStyleFactory::keys();
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	QApplication::setPalette(QApplication::style()->standardPalette());*/
	QApplication a(argc, argv);
	//glutInit(&argc, argv);
	QFile qss(":/stylesheet.qss");
	qss.open(QFile::ReadOnly);
	a.setStyleSheet(qss.readAll());
	qss.close();
	//HXEditorWin::GetInstance()->show();
	HXWinWrap ww;
	ww.show();

	return a.exec();
}
