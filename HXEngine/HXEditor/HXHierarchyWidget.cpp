#include "HXHierarchyWidget.h"
#include "HXSceneManager.h"
#include "HXEditorWin.h"
#include "HXInspectorWidget.h"

using namespace HX3D;

HXHierarchyWidget::HXHierarchyWidget(FPtr gameobjectcallback, FLightPtr lightcallback, QWidget * parent)
	: QTreeWidget(parent)
	, clickGameObjectCallback(NULL)
	, clickLightCallback(NULL)
{
	clickGameObjectCallback = gameobjectcallback;
	clickLightCallback = lightcallback;

	QFont font("Microsoft YaHei", 10, 75);

	//setColumnCount(1);

	//QStringList headers;
	//headers << "Hierarchy";// << "Number";
	//setHeaderLabels(headers);

	QTreeWidgetItem *title = new QTreeWidgetItem;
	title->setFont(0, font);
	title->setText(0, "Hierarchy");
	setHeaderItem(title);
	

	connect(this, &QTreeWidget::currentItemChanged, this, &HXHierarchyWidget::GameObjectChange);
	//connect(this, &QTreeWidget::itemClicked, this, &HXHierarchyWidget::TreeWidgetItemOnClick);
}

HXHierarchyWidget::~HXHierarchyWidget()
{

}

void HXHierarchyWidget::UpdateSceneTree()
{
	QTreeWidgetItem *preRoot = topLevelItem(0);
	delete preRoot;

	QTreeWidgetItem *root = new QTreeWidgetItem(this, QStringList(QString("Scene")));

	HXGameObject* gameObjectTreeRoot = HXSceneManager::GetInstance()->GetGameObjectTreeRoot();
	for (std::vector<HXGameObject*>::iterator itr = gameObjectTreeRoot->GetChildren().begin(); itr != gameObjectTreeRoot->GetChildren().end(); ++itr)
	{
		AddGameObjectLeafRecurve(root, *itr);
	}

	AddLightLeaf(root);

	//QList<QTreeWidgetItem *> rootList;
	//rootList << root;
	//insertTopLevelItems(0, rootList);
	insertTopLevelItem(0, root);
}

void HXHierarchyWidget::OnCreateGameObject(HX3D::HXGameObject* go)
{
	AddGameObjectLeafRecurve(this->currentItem(), go);
}

void HXHierarchyWidget::OnDeleteGameObject()
{
	delete this->currentItem();
	HXEditorWin::GetInstance()->m_pInspectorWidget->OnDeleteGameObject();
}

void HXHierarchyWidget::AddGameObjectLeafRecurve(QTreeWidgetItem* parent, HX3D::HXGameObject* go)
{
	std::string name = go->GetName();
	QTreeWidgetItem* tw = new QTreeWidgetItem(parent, QStringList(QString(name.c_str())));
	QVariant var;
	var.setValue(go);
	tw->setData(0, Qt::UserRole, var);

	std::vector<HXGameObject*> childList = go->GetChildren();
	for (std::vector<HXGameObject*>::iterator itr = childList.begin(); itr != childList.end(); ++itr)
	{
		AddGameObjectLeafRecurve(tw, *itr);
	}
}

void HXHierarchyWidget::AddLightLeaf(QTreeWidgetItem* parent)
{
	for (std::vector<HXLight*>::iterator itr = HXSceneManager::GetInstance()->lightVct.begin(); itr != HXSceneManager::GetInstance()->lightVct.end(); ++itr)
	{
		std::string name = (*itr)->name;
		QTreeWidgetItem* tw = new QTreeWidgetItem(parent, QStringList(QString(name.c_str())));
		QVariant var;
		var.setValue(*itr);
		tw->setData(1, Qt::UserRole, var);
	}
}

void HXHierarchyWidget::GameObjectChange(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	HXGameObject* gameObject = current->data(0, Qt::UserRole).value<HXGameObject*>();
	if (clickGameObjectCallback)
	{
		clickGameObjectCallback(gameObject);
	}
	HXLight* light = current->data(1, Qt::UserRole).value<HXLight*>();
	if (clickLightCallback)
	{
		clickLightCallback(light);
	}
}

//void HXHierarchyWidget::TreeWidgetItemOnClick(QTreeWidgetItem *item, int column)
//{
//	HXGameObject* gameObject = item->data(0, Qt::UserRole).value<HXGameObject*>();
//	if (clickGameObjectCallback)
//	{
//		clickGameObjectCallback(gameObject);
//	}
//	HXLight* light = item->data(1, Qt::UserRole).value<HXLight*>();
//	if (clickLightCallback)
//	{
//		clickLightCallback(light);
//	}
//}