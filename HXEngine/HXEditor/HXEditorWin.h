#ifndef HXEDITORWIN_H
#define HXEDITORWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_HXEditorWin.h"

#include <QVBoxLayout>

class GameWidget;
class HXEditorWin : public QMainWindow
{
	Q_OBJECT

public:
	HXEditorWin(QWidget *parent = 0);
	~HXEditorWin();

private:
	Ui::HXEditorWinClass ui;

	GameWidget* m_pGameWidget;
	QVBoxLayout* m_pCentralLayout;
};

#endif // HXEDITORWIN_H
