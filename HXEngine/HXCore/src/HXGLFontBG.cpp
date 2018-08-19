#include "..\include\HXGLFontBG.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include "HXGLTexture.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	HXGLFontBG::HXGLFontBG()
	{
	}

	HXGLFontBG::~HXGLFontBG()
	{
	}

	void HXGLFontBG::Initialize()
	{
		glGenVertexArrays(1, &_vaoId);
		glGenBuffers(1, &_vboId);
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "builtin\\FontBG.vert" },
			{ GL_FRAGMENT_SHADER, "builtin\\FontBG.frag" },
			{ GL_NONE, NULL }
		};
		_programId = LoadShaders(shaders);
		
		HXGLTexture* tex = new HXGLTexture(MPT_TEXTURE, "prefab/_Material/FontBG/status.png");
		_texId = tex->texId;
	}

	void HXGLFontBG::BeginRender()
	{
		glBindVertexArray(_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, _vboId);
		glUseProgram(_programId);

		//glClear(GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		//glFrontFace(GL_CCW);
		glFrontFace(GL_CW);
	}

	void HXGLFontBG::Render()
	{
		BeginRender();

		typedef float Vertex[5];
		Vertex* pVert = new Vertex[4];

		int nWidth = 150;
		//int nWidth = SCREEN_WIDTH / 4;
		int nHeight = 100;
		//int nHeight = SCREEN_HEIGHT / 4;

		/**
		*   第一个点
		*/
		pVert[0][0] = 0;
		pVert[0][1] = 0;
		pVert[0][2] = 0;
		pVert[0][3] = 0;
		pVert[0][4] = 1;
		/**
		*   第二个点
		*/
		pVert[1][0] = nWidth;
		pVert[1][1] = 0;
		pVert[1][2] = 0;
		pVert[1][3] = 1;
		pVert[1][4] = 1;
		/**
		*   第三个点
		*/
		pVert[2][0] = nWidth;
		pVert[2][1] = nHeight;
		pVert[2][2] = 0;
		pVert[2][3] = 1;
		pVert[2][4] = 0;
		/**
		*   第四个点
		*/
		pVert[3][0] = 0;
		pVert[3][1] = nHeight;
		pVert[3][2] = 0;
		pVert[3][3] = 0;
		pVert[3][4] = 0;

		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), pVert, GL_STATIC_DRAW);

		delete[] pVert;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(0 + 3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);

		glUseProgram(_programId);

		GLint render_mvp_matrix_loc = glGetUniformLocation(_programId, "mvp_matrix");
		vmath::mat4 matModelView = vmath::mat4::identity();
		vmath::mat4 matProjection = vmath::Ortho(0, HXRenderSystem::gCurScreenWidth, HXRenderSystem::gCurScreenHeight, 0, 1, -1);
		glUniformMatrix4fv(render_mvp_matrix_loc, 1, GL_FALSE, matProjection * matModelView);

		GLint tex_uniform_loc = glGetUniformLocation(_programId, "MainTexture");
		// 采样器
		glUniform1i(tex_uniform_loc, 0);
		// 纹理单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glDrawArrays(GL_QUADS, 0, 4);

		EndRender();
	}

	void HXGLFontBG::EndRender()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}
}
