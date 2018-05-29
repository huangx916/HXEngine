#ifndef HXEDITORWIN_H
#define HXEDITORWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_HXEditorWin.h"

class HXEditorWin : public QMainWindow
{
	Q_OBJECT

public:
	HXEditorWin(QWidget *parent = 0);
	~HXEditorWin();

private:
	Ui::HXEditorWinClass ui;
};

#endif // HXEDITORWIN_H
