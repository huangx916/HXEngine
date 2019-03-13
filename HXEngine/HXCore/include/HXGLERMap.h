#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXRenderable;
	class HXGLERMap
	{
	public:
		HXGLERMap();
		~HXGLERMap();

		void Initialize();
		void PreRender();
		void Render(HXRenderable* renderable);
		void PostRender();

		GLint original_fbo;
		GLuint equirectangular_map_prog;
		GLuint cube_map_fbo;
		GLuint cube_map_texture;

		GLint render_mvp_matrix_loc;
		GLint tex_uniform_loc;
	};
}

