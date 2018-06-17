#pragma once
#include <QTreeWidget.h>

class GameObjectTreeWidget : public QTreeWidget
{
	Q_OBJECT
public:
	GameObjectTreeWidget(QWidget * parent = 0);
	~GameObjectTreeWidget();

};