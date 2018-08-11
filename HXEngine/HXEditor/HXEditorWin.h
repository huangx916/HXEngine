#ifndef HXEDITORWIN_H
#define HXEDITORWIN_H

#include <QtWidgets/QMainWindow>
#include "ui_HXEditorWin.h"
#include <QVBoxLayout>
#include "HXGameObject.h"
#include "HXLight.h"
#include "HXICamera.h"
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
	void newScene();
	void createEmpty();
	void loadGameObject();
	void deleteGameObject();
	void exportGameObject();
	void createDirectionLight();
	void createPointLight();
	void createSpotLight();
	void deleteLight();
	void createCamera();
	void deleteCamera();

	void serializeGameObjectRecursive(QTextStream& out, std::vector<HX3D::HXGameObject*>& list, int level);
	void serializeScene(QTextStream& out);
	void serializePrefab(QTextStream& out);

	static void loadSceneCallBack();
	static void updateCallBack();
	static void createGoCallBack(HX3D::HXGameObject* gameObject);
	static void updateGameObject(HX3D::HXGameObject* gameObject);
	static void updateLight(HX3D::HXLight* light);
	static void updateCamera(HX3D::HXICamera* camera);

	Ui::HXEditorWinClass ui;
	QHBoxLayout* m_pMainLayout;

public:
	HXGameWidget* m_pGameWidget;
	HXHierarchyWidget* m_pHierarchyWidget;
	HXInspectorWidget* m_pInspectorWidget;
	HX3D::HXGameObject* m_pCoordArrowGO;
};

#endif // HXEDITORWIN_H
