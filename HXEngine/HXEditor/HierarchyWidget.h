#pragma once
#include <QTreeWidget.h>
#include "HXGameObject.h"

class HierarchyWidget : public QTreeWidget
{
	Q_OBJECT
public:
	HierarchyWidget(QWidget * parent = 0);
	~HierarchyWidget();

	void UpdateGameObjectTree();

private:
	void AddLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go);
};