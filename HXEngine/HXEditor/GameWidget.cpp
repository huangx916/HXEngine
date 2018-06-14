#include "GameWidget.h"

#include "LoadShaders.h"

#include "HXRoot.h"
#include "HXSceneManager.h"
#include "HXGLRenderSystem.h"

GameWidget::GameWidget(QWidget * parent)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start(16);
}

GameWidget::~GameWidget() 
{
	
}

void GameWidget::initializeGL()
{
	glewInit();

	initializeOpenGLFunctions();
	glClearColor(1, 1, 1, 1);

	HXRoot::GetInstance()->Initialize(RenderSystem_GL);
	HXRoot::GetInstance()->InitForEditor();
	HXRoot::GetInstance()->SetDisplayListener(this);
	HXSceneManager::GetInstance()->LoadScene("./scene/DuKangCun.scene");

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