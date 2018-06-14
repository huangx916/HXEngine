#pragma once
#include "vgl.h"

class TestTriangle
{
public:
	GLuint vao;
	GLuint vbo;
	GLuint program;
	void InitTriangle();
	void RenderTriangle();
};