#pragma once
//#include <QWidget>
#include "vgl.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
//#include <QTimer>

class GameWidget : public QOpenGLWidget, protected QOpenGLFunctions// : public QGLWidget
{
	Q_OBJECT

public:
	GameWidget(QWidget * parent = 0);
	~GameWidget();

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();

private:
	GLuint vao;
	GLuint vbo;
	GLuint program;
	void InitTriangle();
	void RenderTriangle();
};
