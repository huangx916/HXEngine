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
	for (std::vector<HXITransform*>::iterator itr = gameObjectTreeRoot->GetTransform()->GetChildren().begin(); itr != gameObjectTreeRoot->GetTransform()->GetChildren().end(); ++itr)
	{
		AddGameObjectLeafRecurve(root, (*itr)->gameObject);
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

	std::vector<HXITransform*> childList = go->GetTransform()->GetChildren();
	for (std::vector<HXITransform*>::iterator itr = childList.begin(); itr != childList.end(); ++itr)
	{
		AddGameObjectLeafRecurve(tw, (*itr)->gameObject);
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
			//return;
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
	HXQuaternionS q;
	q.FromEulerDegree(trans->mLocalEuler.x, trans->mLocalEuler.y, trans->mLocalEuler.z);
	HXVector3D vec = HXVector3D(0, 0, 5);
	vec = q.Transform(vec);

	HXGameObject* gameObject = item->data(0, Qt::UserRole).value<HXGameObject*>();
	if (gameObject)
	{
		HXVector3D pos = gameObject->GetTransform()->GetGlobalPosition() + vec;
		trans->SetLocalPosition(pos);
		HXEditorWin::GetInstance()->m_pHierarchyWidget->UpdateCoordArrow(gameObject->GetTransform());
	}
	HXLight* light = item->data(1, Qt::UserRole).value<HXLight*>();
	if (light)
	{
		HXVector3D pos = light->position;
		trans->SetLocalPosition(pos);
		if (light->lightType == LIGHT_DIRECTION)
		{
			trans->SetLocalRotation(light->direct);
		}
		else if (light->lightType == LIGHT_SPOT)
		{
			trans->SetLocalRotation(light->ConeDirection);
		}
	}
}

void HXHierarchyWidget::UpdateCoordArrow(HX3D::HXITransform* trans)
{
	if (trans->gameObject == _CoordArrow)
	{
		return;
	}

	if (_CoordArrow == NULL/* || _EditorCamera == NULL*/)
	{
		return;
	}
	HXICamera* mainCamera = HXSceneManager::GetInstance()->GetMainCamera();

	_CoordArrow->SetActivity(true);

	//_EditorCamera->transform->SetLocalRotation(mainCamera->transform->GetLocalRotation());

	//mainCamera->Update();
	//_EditorCamera->Update();
	//HXSceneManager::GetInstance()->GetGameObjectTreeRoot()->Update();
	
	//_CoordArrow->GetTransform()->SetLocalRotation(trans->GetGlobalRotation());
	
	//HXVector3D pos = mainCamera->WorldToNDCPoint(trans->GetGlobalPosition());
	//pos = _EditorCamera->NDCToWorldPoint(pos);
	//_CoordArrow->GetTransform()->SetLocalPosition(pos);
	//_CoordArrow->GetTransform()->SetLocalPosition(trans->GetGlobalPosition());

	const HXVector3D& posCam = mainCamera->transform->GetLocalPosition();
	const HXVector3D& posGameObject = trans->GetGlobalPosition();
	float x = posCam.x - posGameObject.x;
	float y = posCam.y - posGameObject.y;
	float z = posCam.z - posGameObject.z;
	float distance = sqrt(x * x + y * y + z * z) / 300;
	//_CoordArrow->GetTransform()->SetLocalScale(HXVector3D(distance, distance, distance));


	//_CoordArrow->GetTransform()->parent = trans->parent;
	_CoordArrow->GetTransform()->parent->RemoveChild(_CoordArrow->GetTransform());
	trans->parent->AddChild(_CoordArrow->GetTransform());

	_CoordArrow->GetTransform()->SetLocalPosition(trans->GetLocalPosition());
	_CoordArrow->GetTransform()->SetLocalRotation(trans->GetLocalRotation());
	HXVector3D scale = HXVector3D(distance, distance, distance) / _CoordArrow->GetTransform()->parent->GetGlobalScale();
	_CoordArrow->GetTransform()->SetLocalScale(scale);
	
}

void HXHierarchyWidget::HideCoordArrow()
{
	if (_CoordArrow == NULL/* || _EditorCamera == NULL*/)
	{
		return;
	}
	_CoordArrow->SetActivity(false);
}