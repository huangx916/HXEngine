#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class GameWidget : public QOpenGLWidget, protected QOpenGLFunctions 
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
	
};
