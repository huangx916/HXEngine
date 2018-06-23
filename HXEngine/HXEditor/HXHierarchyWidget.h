#pragma once
#include <QTreeWidget.h>
#include "HXGameObject.h"
#include "HXLight.h"

Q_DECLARE_METATYPE(HX3D::HXGameObject*)
Q_DECLARE_METATYPE(HX3D::HXLight*)
class HXHierarchyWidget : public QTreeWidget
{
	Q_OBJECT
public:
	typedef void(*FPtr)(HX3D::HXGameObject*);
	typedef void(*FLightPtr)(HX3D::HXLight*);

	HXHierarchyWidget(FPtr gameobjectcallback, FLightPtr lightcallback, QWidget * parent = 0);
	~HXHierarchyWidget();

	void UpdateSceneTree();

private:
	void AddGameObjectLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go);
	void AddLightLeaf(QTreeWidgetItem* parent);

	//void GameObjectChange(QTreeWidgetItem *current, QTreeWidgetItem *previous);
	void TreeWidgetItemOnClick(QTreeWidgetItem *item, int column);

	FPtr clickGameObjectCallback;
	FLightPtr clickLightCallback;
};