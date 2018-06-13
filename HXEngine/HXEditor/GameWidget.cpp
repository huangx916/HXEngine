#include "GameWidget.h"

#include "LoadShaders.h"

#include "HXRoot.h"
#include "HXSceneManager.h"
using namespace HX3D;

GameWidget::GameWidget(QWidget * parent)
{
	
}

GameWidget::~GameWidget() 
{
	
}

void GameWidget::initializeGL()
{
	glewInit();

	initializeOpenGLFunctions();
	glClearColor(1, 1, 1, 1);

	//InitTriangle();

	HXRoot::GetInstance()->Initialize(RenderSystem_GL);
	HXRoot::GetInstance()->InitForEditor();
	HXSceneManager::GetInstance()->LoadScene("./scene/DuKangCun.scene");
}

void GameWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GameWidget::paintGL()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glColor3f(1, 0, 0);
	//glutWireSphere(1, 20, 20);
	//RenderTriangle();

	HXSceneManager::GetInstance()->OnDisplay(true);
	HXSceneManager::GetInstance()->OnDisplay(false);
}

void GameWidget::InitTriangle()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	const GLuint NumVertices = 6;
	GLfloat vertices[NumVertices][2] = {
		{ -0.90, -0.90 },	// Triangle 1
		{ 0.85, -0.90 },
		{ -0.90,  0.85 },

		{ 0.90, -0.85 },	// Triangle 2
		{ 0.90,  0.90 },
		{ -0.85,  0.90 }
	};

	GLfloat colors[NumVertices][4] = {
		{ 1,1,1,1 },
		{ 1,0,0,1 },
		{ 0,1,0,1 },

		{ 1,1,1,1 },
		{ 1,0,0,1 },
		{ 0,0,1,1 }
	};

	int nSize = sizeof(vertices);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "shader\\triangles.vert" },
		{ GL_FRAGMENT_SHADER, "shader\\triangles.frag" },
		{ GL_NONE, NULL }
	};

	program = LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(sizeof(vertices)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameWidget::RenderTriangle()
{
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glBindVertexArray(vao);
	glUseProgram(program);
	const GLuint NumVertices = 6;
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}