#include "TestTriangle.h"
#include "LoadShaders.h"

void TestTriangle::InitTriangle()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	const GLuint NumVertices = 6;
	GLfloat vertices[NumVertices][2] = {
		{ -0.90f, -0.90f },	// Triangle 1
		{ 0.85f, -0.90f },
		{ -0.90f,  0.85f },

		{ 0.90f, -0.85f },	// Triangle 2
		{ 0.90f,  0.90f },
		{ -0.85f,  0.90f }
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

void TestTriangle::RenderTriangle()
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