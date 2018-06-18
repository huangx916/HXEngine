#include "HXGameWidget.h"

//#include "LoadShaders.h"

#include "HXRoot.h"
#include "HXSceneManager.h"
#include "HXGLRenderSystem.h"
#include "HXResourceManager.h"
#include "HXICamera.h"
#include <QMessageBox.h>

HXGameWidget::HXGameWidget(QWidget * parent)
 : QOpenGLWidget(parent)
, bLoadScene(false)
, bLoadGameObject(false)
, loadCallback(NULL)
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

void HXGameWidget::LoadScene(QString path, FPtr callback)
{
	scenePath = path;
	bLoadScene = true;
	loadCallback = callback;
}

void HXGameWidget::LoadGameObject(QString path)
{
	gameObjectPath = path;
	bLoadGameObject = true;
}

void HXGameWidget::initializeGL()
{
	glewInit();

	initializeOpenGLFunctions();
	glClearColor(1, 1, 1, 1);

	HXRoot::GetInstance()->Initialize(RenderSystem_GL);
	HXRoot::GetInstance()->InitForEditor();
	HXRoot::GetInstance()->SetDisplayListener(this);
	//HXSceneManager::GetInstance()->LoadScene("./scene/DuKangCun.scene");
	

	//QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
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
		HXSceneManager::GetInstance()->LoadGameObjectInEditor(gameObjectPath.toStdString());
		if (loadCallback != NULL)
		{
			loadCallback();
		}
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




void HXGameWidget::OnDisplay(bool shadow)
{
	HXSceneManager::GetInstance()->OnDisplay(shadow);
}

void HXGameWidget::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	HXSceneManager::GetInstance()->OnViewPortResize(nScreenWidth, nScreenHeight);
}

void HXGameWidget::OnKeyboard(unsigned char key, int x, int y)
{
	/*if (key == 'w' || key == 'W')
	{
	HXSceneManager::GetInstance()->GetMainCamera()->Forward(1);
	}
	if (key == 's' || key == 'S')
	{
	HXSceneManager::GetInstance()->GetMainCamera()->Forward(-1);
	}
	if (key == 'a' || key == 'A')
	{
	HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(-1, 0, 0));
	}
	if (key == 'd' || key == 'D')
	{
	HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(1, 0, 0));
	}*/
	if (key == 'f' || key == 'F')
	{
		if (HXSceneManager::GetInstance()->fog)
		{
			HXSceneManager::GetInstance()->UseFog(!HXSceneManager::GetInstance()->fog->useFog);
		}
	}
}

void HXGameWidget::OnMouseMove(int nButton, int deltaX, int deltaY)
{
	if (HXSceneManager::GetInstance()->GetMainCamera() == NULL)
	{
		return;
	}
	if (nButton == 0)
	{
		// 左键按下状态
		//HXSceneManager::GetInstance()->GetMainCamera()->MoveHorizon(float(deltaX) / 10.0f);
		//HXSceneManager::GetInstance()->GetMainCamera()->MoveVertical(float(deltaY) / 10.0f);
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D((deltaX) / 10.0f, 0, 0));
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(0, -float(deltaY) / 10.0f, 0));
	}
	else if (nButton == 2)
	{
		// 右键按下状态
		//std::cout << "x = " << deltaX << ";     y = " << deltaY << std::endl;
		HXSceneManager::GetInstance()->GetMainCamera()->yaw(float(deltaX) / 10.0f);
		//HXSceneManager::GetInstance()->GetMainCamera()->YawLockTarget(float(deltaX) / 5.0f);
		HXSceneManager::GetInstance()->GetMainCamera()->pitch(float(deltaY) / 10.0f);
		//HXSceneManager::GetInstance()->GetMainCamera()->PitchLockTarget(float(deltaY) / 5.0f);
	}
}

void HXGameWidget::OnMouseWheel(float fDistance)
{
	if (HXSceneManager::GetInstance()->GetMainCamera() == NULL)
	{
		return;
	}
	//HXSceneManager::GetInstance()->GetMainCamera()->Forward(fDistance);
	HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(0, 0, -fDistance));
}