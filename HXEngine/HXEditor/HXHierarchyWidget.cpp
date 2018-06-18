#include "HXHierarchyWidget.h"
#include "HXSceneManager.h"

using namespace HX3D;

HXHierarchyWidget::HXHierarchyWidget(FPtr callback, QWidget * parent) : QTreeWidget(parent), clickCallback(NULL)
{
	clickCallback = callback;

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

	//connect(this, &QTreeWidget::currentItemChanged, this, &HXHierarchyWidget::GameObjectChange);
	connect(this, &QTreeWidget::itemClicked, this, &HXHierarchyWidget::GameObjectClick);
}

HXHierarchyWidget::~HXHierarchyWidget()
{

}

void HXHierarchyWidget::UpdateGameObjectTree()
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

void HXHierarchyWidget::AddLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go)
{
	std::string name = go->GetName();
	QTreeWidgetItem* tw = new QTreeWidgetItem(parent, QStringList(QString(name.c_str())));
	QVariant var;
	var.setValue(go);
	tw->setData(0, Qt::UserRole, var);

	std::vector<HXGameObject*> childList = go->GetChildren();
	for (std::vector<HXGameObject*>::iterator itr = childList.begin(); itr != childList.end(); ++itr)
	{
		AddLeafRecurve(tw, *itr);
	}
}

//void HXHierarchyWidget::GameObjectChange(QTreeWidgetItem *current, QTreeWidgetItem *previous)
//{
//	HXGameObject* gameObject = current->data(0, Qt::UserRole).value<HXGameObject*>();
//	int test = 0;
//}

void HXHierarchyWidget::GameObjectClick(QTreeWidgetItem *item, int column)
{
	HXGameObject* gameObject = item->data(0, Qt::UserRole).value<HXGameObject*>();
	int test = 0;
	if (clickCallback)
	{
		clickCallback(gameObject);
	}
}