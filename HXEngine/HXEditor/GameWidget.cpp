#include "GameWidget.h"

GameWidget::GameWidget(QWidget * parent)
{
	
}

GameWidget::~GameWidget() {
	
}

void GameWidget::initializeGL()
{
	initializeOpenGLFunctions();
	glClearColor(1, 0, 0, 1);
}

void GameWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GameWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}