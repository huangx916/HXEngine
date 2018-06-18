#include "HXGameWidget.h"

//#include "LoadShaders.h"

#include "HXRoot.h"
#include "HXSceneManager.h"
#include "HXGLRenderSystem.h"
#include "HXResourceManager.h"
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



void HXGameWidget::OnDisplay(bool shadow)
{
	HXSceneManager::GetInstance()->OnDisplay(shadow);
}

void HXGameWidget::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	HXSceneManager::GetInstance()->OnViewPortResize(nScreenWidth, nScreenHeight);
}