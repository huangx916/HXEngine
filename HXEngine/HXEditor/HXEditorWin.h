#ifndef HXEDITORWIN_H
#define HXEDITORWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_HXEditorWin.h"
#include <QVBoxLayout>

class GameWidget;
class HierarchyWidget;
class HXEditorWin : public QMainWindow
{
	Q_OBJECT

public:
	static HXEditorWin* GetInstance();
	~HXEditorWin();
private:
	HXEditorWin(QWidget *parent = 0);
	static HXEditorWin* m_pInstance;

	void loadScene();
	void loadGameObject();

	static void updateHierarchy();

	Ui::HXEditorWinClass ui;
	QHBoxLayout* m_pMainLayout;

	GameWidget* m_pGameWidget;
	HierarchyWidget* m_pGameObjectTreeWidget;
};

#endif // HXEDITORWIN_H
