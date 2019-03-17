#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXMesh;
	class HXGLSpecularDFGTexture
	{
	public:
		HXGLSpecularDFGTexture();
		~HXGLSpecularDFGTexture();

		void Preprocess();
		GLuint GetCubeMapTexture();

	private:
		void Initialize();
		void Release();
		void PreRender();
		void Render();
		void PostRender();

	private:
		GLint original_fbo;
		GLuint dfg_prog;
		GLuint texture_fbo;
		GLuint texture_obj;

		HXMesh* quadMesh;
	};
}
