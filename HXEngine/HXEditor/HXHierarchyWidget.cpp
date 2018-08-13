#include "HXHierarchyWidget.h"
#include "HXSceneManager.h"
#include "HXEditorWin.h"
#include "HXInspectorWidget.h"

using namespace HX3D;

HXHierarchyWidget::HXHierarchyWidget(FPtr gameobjectcallback, FLightPtr lightcallback, FCameraPtr cameracallback, QWidget * parent)
	: QTreeWidget(parent)
	, clickGameObjectCallback(NULL)
	, clickLightCallback(NULL)
	, clickCameraCallback(NULL)
	, lightRoot(NULL)
	, cameraRoot(NULL)
	, _EditorCamera(NULL)
	, _CoordArrow(NULL)
{
	clickGameObjectCallback = gameobjectcallback;
	clickLightCallback = lightcallback;
	clickCameraCallback = cameracallback;

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
	connect(this, &QTreeWidget::itemDoubleClicked, this, &HXHierarchyWidget::TreeWidgetItemOnDoubleClick);
}

HXHierarchyWidget::~HXHierarchyWidget()
{

}

void HXHierarchyWidget::UpdateSceneTree()
{
	QTreeWidgetItem *preRoot = topLevelItem(0);
	delete preRoot;
	_EditorCamera = NULL;
	_CoordArrow = NULL;

	QTreeWidgetItem *root = new QTreeWidgetItem(this, QStringList(QString("Scene")));

	cameraRoot = new QTreeWidgetItem(root, QStringList(QString("CameraList")));

	lightRoot = new QTreeWidgetItem(root, QStringList(QString("LightList")));

	HXGameObject* gameObjectTreeRoot = HXSceneManager::GetInstance()->GetGameObjectTreeRoot();
	for (std::vector<HXGameObject*>::iterator itr = gameObjectTreeRoot->GetChildren().begin(); itr != gameObjectTreeRoot->GetChildren().end(); ++itr)
	{
		AddGameObjectLeafRecurve(root, *itr);
	}

	AddCameraLeaf(cameraRoot);

	AddLightLeaf(lightRoot);

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

	if (name == "_CoordArrow")
	{
		_CoordArrow = go;
		_CoordArrow->SetActivity(false);
		return;
	}

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

void HXHierarchyWidget::OnCreateLight(HX3D::HXLight* light)
{
	if (lightRoot)
	{
		QTreeWidgetItem* tw = new QTreeWidgetItem(lightRoot, QStringList(QString(light->name.c_str())));
		QVariant var;
		var.setValue(light);
		tw->setData(1, Qt::UserRole, var);
	}
}

void HXHierarchyWidget::OnDeleteLight()
{
	delete this->currentItem();
	HXEditorWin::GetInstance()->m_pInspectorWidget->OnDeleteLight();
}

void HXHierarchyWidget::OnCreateCamera(HX3D::HXICamera* camera)
{
	if (cameraRoot)
	{
		QTreeWidgetItem* tw = new QTreeWidgetItem(cameraRoot, QStringList(QString(camera->name.c_str())));
		QVariant var;
		var.setValue(camera);
		tw->setData(2, Qt::UserRole, var);
	}
}

void HXHierarchyWidget::OnDeleteCamera()
{
	delete this->currentItem();
	HXEditorWin::GetInstance()->m_pInspectorWidget->OnDeleteCamera();
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

void HXHierarchyWidget::AddCameraLeaf(QTreeWidgetItem* parent)
{
	for (std::vector<HXICamera*>::iterator itr = HXSceneManager::GetInstance()->cameraVct.begin(); itr != HXSceneManager::GetInstance()->cameraVct.end(); ++itr)
	{
		std::string name = (*itr)->name;
		if (name == "_EditorCamera")
		{
			_EditorCamera = (*itr);
			return;
		}

		QTreeWidgetItem* tw = new QTreeWidgetItem(parent, QStringList(QString(name.c_str())));
		QVariant var;
		var.setValue(*itr);
		tw->setData(2, Qt::UserRole, var);
	}
}

void HXHierarchyWidget::GameObjectChange(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	if (current)
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
		HXICamera* camera = current->data(2, Qt::UserRole).value<HXICamera*>();
		if (clickCameraCallback)
		{
			clickCameraCallback(camera);
		}
	}
}

void HXHierarchyWidget::TreeWidgetItemOnDoubleClick(QTreeWidgetItem *item, int column)
{
	HXITransform* trans = HXSceneManager::GetInstance()->GetMainCamera()->transform;
	HXQuaternion q;
	q.FromEulerDegree(trans->mEulerDegree.x, trans->mEulerDegree.y, trans->mEulerDegree.z);
	HXVector3D vec = HXVector3D(0, 0, 5);
	vec = q.Transform(vec);

	HXGameObject* gameObject = item->data(0, Qt::UserRole).value<HXGameObject*>();
	if (gameObject)
	{
		HXVector3D pos = gameObject->GetTransform()->GetPosition() + vec;
		trans->SetPosition(pos);
	}
	HXLight* light = item->data(1, Qt::UserRole).value<HXLight*>();
	if (light)
	{
		HXVector3D pos = light->position;
		trans->SetPosition(pos);
		if (light->lightType == LIGHT_DIRECTION)
		{
			trans->SetRotation(light->direct);
		}
		else if (light->lightType == LIGHT_SPOT)
		{
			trans->SetRotation(light->ConeDirection);
		}
	}
}

void HXHierarchyWidget::UpdateCoordArrow(HX3D::HXITransform* trans)
{
	if (_CoordArrow == NULL || _EditorCamera == NULL)
	{
		return;
	}
	HXICamera* mainCamera = HXSceneManager::GetInstance()->GetMainCamera();

	_CoordArrow->SetActivity(true);

	_EditorCamera->transform->SetRotation(mainCamera->transform->GetRotation());
	_CoordArrow->GetTransform()->SetRotation(trans->GetRotation());

	mainCamera->Update();
	_EditorCamera->Update();

	HXVector3D pos = mainCamera->WorldToNDCPoint(trans->GetPosition());
	pos = _EditorCamera->NDCToWorldPoint(pos);
	_CoordArrow->GetTransform()->SetPosition(pos);
}

void HXHierarchyWidget::HideCoordArrow()
{
	if (_CoordArrow == NULL || _EditorCamera == NULL)
	{
		return;
	}
	_CoordArrow->SetActivity(false);
}