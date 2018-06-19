#ifndef HXEDITORWIN_H
#define HXEDITORWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_HXEditorWin.h"
#include <QVBoxLayout>
#include "HXGameObject.h"
#include <QTextStream.h>

class HXGameWidget;
class HXHierarchyWidget;
class HXInspectorWidget;
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
	void saveScene();
	void loadGameObject();

	void serializeScene(QTextStream& out);

	static void updateHierarchy();
	static void updateInspector(HX3D::HXGameObject* gameObject);

	Ui::HXEditorWinClass ui;
	QHBoxLayout* m_pMainLayout;

	HXGameWidget* m_pGameWidget;
	HXHierarchyWidget* m_pHierarchyWidget;
	HXInspectorWidget* m_pInspectorWidget;
};

#endif // HXEDITORWIN_H
