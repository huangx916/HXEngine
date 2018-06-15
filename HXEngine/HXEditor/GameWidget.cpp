#include "GameWidget.h"

#include "LoadShaders.h"

#include "HXRoot.h"
#include "HXSceneManager.h"
#include "HXGLRenderSystem.h"
#include "HXResourceManager.h"

GameWidget::GameWidget(QWidget * parent) : bLoadScene(false)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start(16);
}

GameWidget::~GameWidget() 
{
	
}

void GameWidget::LoadScene(QString path)
{
	scenePath = path;
	bLoadScene = true;
}

void GameWidget::initializeGL()
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

void GameWidget::resizeGL(int w, int h)
{
	//glViewport(0, 0, w, h);
	HXRenderSystem::Reshape(w, h);
	update();
}

void GameWidget::paintGL()
{
	if (bLoadScene)
	{
		// QT OpenGL相关处理(如:模型加载后的VBO生成等)必须在继承QOpenGLWidget的函数里处理
		bLoadScene = false;
		HXSceneManager::GetInstance()->UnLoadScene();
		HXResourceManager::GetInstance()->UnLoadAll();
		HXSceneManager::GetInstance()->LoadScene(scenePath.toStdString());
	}
	HXGLRenderSystem::RenderScene();
}



void GameWidget::OnDisplay(bool shadow)
{
	HXSceneManager::GetInstance()->OnDisplay(shadow);
}

void GameWidget::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	HXSceneManager::GetInstance()->OnViewPortResize(nScreenWidth, nScreenHeight);
}