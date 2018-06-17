#ifndef HXEDITORWIN_H
#define HXEDITORWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_HXEditorWin.h"
#include <QVBoxLayout>

class GameWidget;
class GameObjectTreeWidget;
class HXEditorWin : public QMainWindow
{
	Q_OBJECT

public:
	HXEditorWin(QWidget *parent = 0);
	~HXEditorWin();

private:
	void loadScene();
	void loadGameObject();

	Ui::HXEditorWinClass ui;
	QHBoxLayout* m_pMainLayout;

	GameWidget* m_pGameWidget;
	GameObjectTreeWidget* m_pGameObjectTreeWidget;
};

#endif // HXEDITORWIN_H
