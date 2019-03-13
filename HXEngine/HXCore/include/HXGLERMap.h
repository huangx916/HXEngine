#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXRenderable;
	class HXMesh;
	class HXGLERMap
	{
	public:
		HXGLERMap();
		~HXGLERMap();

		void Initialize();
		void PreRender();
		void Render();
		void PostRender();
		void GenerateMipmap();

		GLuint GetCubeMapTexture();

	private:
		GLint original_fbo;
		GLuint equirectangular_map_prog;
		GLuint cube_map_fbo;
		GLuint cube_map_texture;

		GLint render_mvp_matrix_loc;
		GLint tex_uniform_loc;

		HXMesh* sphereMesh;
	};
}

