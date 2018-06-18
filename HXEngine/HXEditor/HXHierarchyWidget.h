#pragma once
#include <QTreeWidget.h>
#include "HXGameObject.h"

Q_DECLARE_METATYPE(HX3D::HXGameObject*)
class HXHierarchyWidget : public QTreeWidget
{
	Q_OBJECT
public:
	typedef void(*FPtr)(HX3D::HXGameObject*);

	HXHierarchyWidget(FPtr callback, QWidget * parent = 0);
	~HXHierarchyWidget();

	void UpdateGameObjectTree();

private:
	void AddLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go);

	//void GameObjectChange(QTreeWidgetItem *current, QTreeWidgetItem *previous);
	void GameObjectClick(QTreeWidgetItem *item, int column);

	FPtr clickCallback;
};