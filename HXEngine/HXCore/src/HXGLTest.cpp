#include "..\include\HXGLTest.h"
#include "vgl.h"
//#include <GL\glew.h>
#include "LoadShaders.h"
#include <iostream>
#include "HXGLFreeTypeFont.h"

namespace HX3D
{
	unsigned int HXGLTest::VAOs[NumVAOs];
	unsigned int HXGLTest::Buffers[NumBuffers];
	unsigned int HXGLTest::Programs[NumPrograms];
	HXIFreeTypeFont* HXGLTest::font = NULL;
	int HXGLTest::_nWidth = 640;
	int HXGLTest::_nHeight = 480;
	HXGLTest::HXGLTest()
	{
		
	}

	HXGLTest::~HXGLTest()
	{
		if (font)
		{
			delete font;
			font = NULL;
		}
	}

	void HXGLTest::CreateGLWindow(int argc, char* argv[])
	{
		int one = 1;
		char * name = "name";

//#ifdef _DEBUG
//		glutInitContextFlags(GLUT_DEBUG);
//#endif

		glutInitWindowSize(_nWidth, _nHeight);
		glutInitWindowPosition(140, 140);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// Ë«»º´æ
														// glutInitContextVersion(4, 3);
		//glutInitContextProfile(GLUT_CORE_PROFILE);

		glutInit(&one, &name);

		glutCreateWindow("HXGL TEST");

		glutDisplayFunc(Display);

		if (glewInit())
		{
			std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
			exit(EXIT_FAILURE);
		}

		glGenVertexArrays(NumVAOs, VAOs);
		glGenBuffers(NumBuffers, Buffers);

		InitTriangle();
		InitFont();

		glutMainLoop();
	}

	void HXGLTest::Display()
	{
		RenderTriangle();
		RenderFont();

		//glFlush();	// µ¥»º´æ
		glutSwapBuffers();	// Ë«»º´æ
		glutPostRedisplay();
	}

	void HXGLTest::RenderTriangle()
	{
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAOs[Triangles]);
		glUseProgram(Programs[TriangleProgram]);
		const GLuint NumVertices = 6;
		glDrawArrays(GL_TRIANGLES, 0, NumVertices);

		////glFlush();	// µ¥»º´æ
		//glutSwapBuffers();	// Ë«»º´æ
		//glutPostRedisplay();
	}

	void HXGLTest::RenderWireCube()
	{
		glutWireCube(2);
	}

	void HXGLTest::RenderFont()
	{
		if (font)
		{
			font->BeginText();
			font->_DrawText(10, 10, L"´óÉµ±Æ²âÊÔË¹µÙ·ÒË¹µÙ·ÒÊ¤¶à¸ºÉÙ·ÀÊØ´ò·¨", HXCOLOR(255,0,0,255));
			font->_DrawText(10, 30, L"dfsdfÊÇÁ½µØ·Ö¾ÓíÆíÂ·Ü½ø", HXCOLOR(0, 255, 0, 255));
			font->_DrawText(10, 50, L"123ÊÇ·¶µÂÈø·¢sdfd4235", HXCOLOR(0, 0, 255, 255));
			font->_DrawText(10, 70, L"2017-11-21 @bianfeng", HXCOLOR(255, 255, 0, 255));
			font->EndText();
		}
	}

	void HXGLTest::InitTriangle()
	{
		
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
			{ GL_VERTEX_SHADER, "builtin\\triangles.vert"},
			{ GL_FRAGMENT_SHADER, "builtin\\triangles.frag"},
			{ GL_NONE, NULL}
		};

		Programs[TriangleProgram] = LoadShaders(shaders);
		glUseProgram(Programs[TriangleProgram]);

		glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (const void*)(0));
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(sizeof(vertices)));
		glEnableVertexAttribArray(vColor);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		////glDeleteBuffers(NumBuffers, Buffers);
	}

	void HXGLTest::InitFont()
	{
		font = new HXGLFreeTypeFont();
		font->Initialize("default.ttf", 16);
	}
}