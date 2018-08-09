#pragma once
#include <QTreeWidget.h>
#include "HXGameObject.h"
#include "HXLight.h"
#include "HXICamera.h"

Q_DECLARE_METATYPE(HX3D::HXGameObject*)
Q_DECLARE_METATYPE(HX3D::HXLight*)
Q_DECLARE_METATYPE(HX3D::HXICamera*)
class HXHierarchyWidget : public QTreeWidget
{
	Q_OBJECT
public:
	typedef void(*FPtr)(HX3D::HXGameObject*);
	typedef void(*FLightPtr)(HX3D::HXLight*);
	typedef void(*FCameraPtr)(HX3D::HXICamera*);

	HXHierarchyWidget(FPtr gameobjectcallback, FLightPtr lightcallback, FCameraPtr cameracallback, QWidget * parent = 0);
	~HXHierarchyWidget();

	void UpdateSceneTree();
	void OnCreateGameObject(HX3D::HXGameObject* go);
	void OnDeleteGameObject();
	void OnCreateLight(HX3D::HXLight* light);
	void OnDeleteLight();

private:
	void AddGameObjectLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go);
	void AddLightLeaf(QTreeWidgetItem* parent);
	void AddCameraLeaf(QTreeWidgetItem* parent);

	void GameObjectChange(QTreeWidgetItem *current, QTreeWidgetItem *previous);
	void TreeWidgetItemOnDoubleClick(QTreeWidgetItem *item, int column);

	FPtr clickGameObjectCallback;
	FLightPtr clickLightCallback;
	FCameraPtr clickCameraCallback;

	QTreeWidgetItem* lightRoot;
	QTreeWidgetItem* cameraRoot;
};