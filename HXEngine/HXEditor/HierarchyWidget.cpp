#include "HierarchyWidget.h"
#include "HXSceneManager.h"

using namespace HX3D;

HierarchyWidget::HierarchyWidget(QWidget * parent) : QTreeWidget(parent)
{
	//setColumnCount(1);

	QStringList headers;
	headers << "Hierarchy";// << "Number";
	setHeaderLabels(headers);

	//QTreeWidgetItem *root = new QTreeWidgetItem(this, QStringList(QString("Root")));

	//new QTreeWidgetItem(root, QStringList(QString("Leaf 1")));
	//QTreeWidgetItem *leaf2 = new QTreeWidgetItem(root, QStringList(QString("Leaf 2")));
	////leaf2->setCheckState(0, Qt::Checked);

	//QList<QTreeWidgetItem *> rootList;
	//rootList << root;
	//insertTopLevelItems(0, rootList);
}

HierarchyWidget::~HierarchyWidget()
{

}

void HierarchyWidget::UpdateGameObjectTree()
{
	QTreeWidgetItem *preRoot = topLevelItem(0);
	delete preRoot;

	QTreeWidgetItem *root = new QTreeWidgetItem(this, QStringList(QString("Scene")));

	std::vector<HXGameObject*> gameObjectList = HXSceneManager::GetInstance()->GetGameObjectList();
	for (std::vector<HXGameObject*>::iterator itr = gameObjectList.begin(); itr != gameObjectList.end(); ++itr)
	{
		AddLeafRecurve(root, *itr);
	}

	//QList<QTreeWidgetItem *> rootList;
	//rootList << root;
	//insertTopLevelItems(0, rootList);
	insertTopLevelItem(0, root);
}

void HierarchyWidget::AddLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go)
{
	std::string name = go->GetName();
	QTreeWidgetItem* tw = new QTreeWidgetItem(parent, QStringList(QString(name.c_str())));
	std::vector<HXGameObject*> childList = go->GetChildren();
	for (std::vector<HXGameObject*>::iterator itr = childList.begin(); itr != childList.end(); ++itr)
	{
		AddLeafRecurve(tw, *itr);
	}
}