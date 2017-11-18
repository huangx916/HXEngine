#include "..\include\HXGLTest.h"
#include "vgl.h"
//#include <GL\glew.h>
#include "LoadShaders.h"
#include <iostream>

namespace HX3D
{
	unsigned int HXGLTest::VAOs[NumVAOs];

	HXGLTest::HXGLTest()
	{
	}


	HXGLTest::~HXGLTest()
	{
	}


	void HXGLTest::Display()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAOs[Triangles]);
		const GLuint NumVertices = 6;
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		//glFlush();	// µ¥»º´æ
		glutSwapBuffers();	// Ë«»º´æ
		glutPostRedisplay();
	}
	void HXGLTest::CreateGLWindow(int argc, char* argv[])
	{
		int one = 1;
		char * name = "name";

#ifdef _DEBUG
		glutInitContextFlags(GLUT_DEBUG);
#endif

		glutInitWindowSize(512, 512);
		glutInitWindowPosition(140, 140);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	// Ë«»º´æ
		// glutInitContextVersion(4, 3);
		glutInitContextProfile(GLUT_CORE_PROFILE);

		glutInit(&one, &name);
		
		glutCreateWindow("HXGL WINDOW");

		glutDisplayFunc(Display);

		if (glewInit())
		{
			std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
			exit(EXIT_FAILURE);
		}

		Init();

		glutMainLoop();
	}

	void HXGLTest::Init()
	{
		glGenVertexArrays(NumVAOs, VAOs);
		glBindVertexArray(VAOs[Triangles]);

		const GLuint NumVertices = 6;
		GLfloat vertices[NumVertices][2] = {
			{-0.90, -0.90},	// Triangle 1
			{ 0.85, -0.90},
			{-0.90,  0.85},

			{ 0.90, -0.85},	// Triangle 2
			{ 0.90,  0.90},
			{-0.85,  0.90}
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

		glGenBuffers(NumBuffers, Buffers);
		glBindBuffer(GL_ARRAY_BUFFER ,Buffers[ArrayBuffer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

		/*char* pCurDir = new char[256];
		::GetCurrentDirectory(256, pCurDir);
		std::string strPath = pCurDir;
		delete pCurDir;

		char* pCurDir1 = new char[256];
		::GetModuleFileName(NULL, pCurDir1,256);
		std::string strPath1 = pCurDir1;
		delete pCurDir1;*/

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "shader\\triangles.vert"},
			{ GL_FRAGMENT_SHADER, "shader\\triangles.frag"},
			{ GL_NONE, NULL}
		};

		GLuint program = LoadShaders(shaders);
		glUseProgram(program);

		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (const void*)(0));
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(sizeof(vertices)));
		glEnableVertexAttribArray(vColor);
	}

	
}