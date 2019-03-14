#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXMesh;
	class HXGLCubeMap
	{
	public:
		HXGLCubeMap();
		~HXGLCubeMap();

		void Initialize();
		void Render(GLuint tex_obj);

	private:
		GLuint cube_map_prog;

		GLint render_mvp_matrix_loc;
		GLint tex_uniform_loc;

		HXMesh* cubeMesh;
	};
}
