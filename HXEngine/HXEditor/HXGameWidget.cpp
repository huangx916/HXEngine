#include "HXGameWidget.h"

//#include "LoadShaders.h"

#include "HXRoot.h"
#include "HXSceneManager.h"
#include "HXGLRenderSystem.h"
#include "HXResourceManager.h"
#include "HXICamera.h"
#include <QMessageBox.h>
#include "HXEditorWin.h"
#include "HXInspectorWidget.h"
#include "HXHierarchyWidget.h"

HXGameWidget::HXGameWidget(QWidget * parent)
 : QOpenGLWidget(parent)
, bLoadScene(false)
, bLoadGameObject(false)
, loadCallback(NULL)
, updateCallback(NULL)
, createGoCallback(NULL)
, gameObjectFather(NULL)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start(16);
}

HXGameWidget::~HXGameWidget()
{
	
}

QString HXGameWidget::GetCurScene()
{
	return scenePath;
}

void HXGameWidget::LoadScene(QString path, FPtr onLoad, FPtr onUpdate, FPtrGo onCreate)
{
	scenePath = path;
	bLoadScene = true;
	loadCallback = onLoad;
	updateCallback = onUpdate;
	createGoCallback = onCreate;
}

void HXGameWidget::LoadGameObject(HXGameObject* father, QString path)
{
	gameObjectFather = father;
	gameObjectPath = path;
	bLoadGameObject = true;
}

void HXGameWidget::initializeGL()
{
	glewInit();

	initializeOpenGLFunctions();

	HXRoot::GetInstance()->Initialize(RenderSystem_GL);
	HXRoot::GetInstance()->InitForEditor();
	HXRoot::GetInstance()->SetDisplayListener(this);
	//HXSceneManager::GetInstance()->LoadScene("./scene/DuKangCun.scene");
	

	//QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
	//glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
}

void HXGameWidget::resizeGL(int w, int h)
{
	//glViewport(0, 0, w, h);
	HXRenderSystem::Reshape(w, h);
	update();
}

void HXGameWidget::paintGL()
{
	if (bLoadScene)
	{
		// QT OpenGL相关处理(如:模型加载后的VBO生成等)必须在继承QOpenGLWidget的函数里处理
		bLoadScene = false;
		HXSceneManager::GetInstance()->UnLoadScene();
		HXResourceManager::GetInstance()->UnLoadAll();
		HXSceneManager::GetInstance()->LoadScene(scenePath.toStdString());
		if (loadCallback != NULL)
		{
			loadCallback();
		}
	}
	if (bLoadGameObject)
	{
		bLoadGameObject = false;
		HXGameObject* go = HXSceneManager::GetInstance()->CreateGameObjectFromPrefab(gameObjectFather, gameObjectPath.toStdString());
		if (createGoCallback != NULL && go != NULL)
		{
			createGoCallback(go);
		}
	}
	
	if (updateCallback)
	{
		updateCallback();
	}
	
	HXGLRenderSystem::RenderScene();
}

void HXGameWidget::mouseMoveEvent(QMouseEvent *event)
{
	HXRenderSystem::MouseMotion(event->localPos().x(), event->localPos().y());
}

void HXGameWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		HXRenderSystem::Mouse(0, 0, event->localPos().x(), event->localPos().y());
		setFocus();
	}
	else if (event->button() == Qt::RightButton)
	{
		HXRenderSystem::Mouse(2, 0, event->localPos().x(), event->localPos().y());
	}
	else if (event->button() == Qt::MidButton)
	{
		HXRenderSystem::Mouse(1, 0, event->localPos().x(), event->localPos().y());
	}
}

void HXGameWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		HXRenderSystem::Mouse(0, 1, event->localPos().x(), event->localPos().y());
	}
	else if (event->button() == Qt::RightButton)
	{
		HXRenderSystem::Mouse(2, 1, event->localPos().x(), event->localPos().y());
	}
	else if (event->button() == Qt::MidButton)
	{
		HXRenderSystem::Mouse(1, 1, event->localPos().x(), event->localPos().y());
	}
}

void HXGameWidget::wheelEvent(QWheelEvent* event)
{
	if (event->delta() > 0)
	{
		HXRenderSystem::Mouse(3, 0, 0, 0);
	}
	else
	{
		HXRenderSystem::Mouse(4, 0, 0, 0);
	}
}

void HXGameWidget::keyPressEvent(QKeyEvent *event)
{
	HXRenderSystem::Keyboard(event->key(), 0, 0);
}

void HXGameWidget::keyReleaseEvent(QKeyEvent *event)
{
	//HXRenderSystem::Keyboard(event->key(), 0, 0);
}

void HXGameWidget::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	
}

void HXGameWidget::OnKeyboard(unsigned char key, int x, int y)
{
	/*if (key == 'f' || key == 'F')
	{
		if (HXSceneManager::GetInstance()->fog)
		{
			HXSceneManager::GetInstance()->UseFog(!HXSceneManager::GetInstance()->fog->useFog);
		}
	}*/
}

void HXGameWidget::OnMouseMove(int nButton, int deltaX, int deltaY)
{
	HXICamera* camera = NULL;
	if (HXEditorWin::GetInstance()->m_pInspectorWidget->selectedCamera)
	{
		camera = HXEditorWin::GetInstance()->m_pInspectorWidget->selectedCamera;
	}
	else if (HXSceneManager::GetInstance()->GetMainCamera())
	{
		camera = HXSceneManager::GetInstance()->GetMainCamera();
	}
	if (camera == NULL)
	{
		return;
	}

	if (nButton == 0)
	{
		// 左键按下状态
		camera->move(HXVector3D((deltaX) / 10.0f, -float(deltaY) / 10.0f, 0));
	}
	else if (nButton == 2)
	{
		// 右键按下状态
		//std::cout << "x = " << deltaX << ";     y = " << deltaY << std::endl;
		camera->yaw(float(deltaX) / 10.0f);
		camera->pitch(float(deltaY) / 10.0f);
	}

	HXGameObject* curGameobject = HXEditorWin::GetInstance()->m_pInspectorWidget->selectedGameObject;
	if (curGameobject)
	{
		HXEditorWin::GetInstance()->m_pHierarchyWidget->UpdateCoordArrow(curGameobject->GetTransform());
	}
}

void HXGameWidget::OnMouseWheel(float fDistance)
{
	HXICamera* camera = NULL;
	if (HXEditorWin::GetInstance()->m_pInspectorWidget->selectedCamera)
	{
		camera = HXEditorWin::GetInstance()->m_pInspectorWidget->selectedCamera;
	}
	else if (HXSceneManager::GetInstance()->GetMainCamera())
	{
		camera = HXSceneManager::GetInstance()->GetMainCamera();
	}
	if (camera == NULL)
	{
		return;
	}

	camera->move(HXVector3D(0, 0, -fDistance));

	HXGameObject* curGameobject = HXEditorWin::GetInstance()->m_pInspectorWidget->selectedGameObject;
	if (curGameobject)
	{
		HXEditorWin::GetInstance()->m_pHierarchyWidget->UpdateCoordArrow(curGameobject->GetTransform());
	}
}