#pragma once
#include <QTreeWidget.h>
#include "HXGameObject.h"

class GameObjectTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	GameObjectTreeWidget(QWidget * parent = 0);
	~GameObjectTreeWidget();

	void UpdateGameObjectTree();

private:
	void AddLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go);
};