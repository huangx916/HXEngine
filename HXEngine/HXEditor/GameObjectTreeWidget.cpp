#include "GameObjectTreeWidget.h"

GameObjectTreeWidget::GameObjectTreeWidget(QWidget * parent) : QTreeWidget(parent)
{
	setColumnCount(1);

	QTreeWidgetItem *root = new QTreeWidgetItem(this, QStringList(QString("Root")));

	new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
	QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
	leaf2->setCheckState(0, Qt::Checked);

	QList<QTreeWidgetItem *> rootList;
	rootList << root;
	insertTopLevelItems(0, rootList);
}

GameObjectTreeWidget::~GameObjectTreeWidget()
{

}