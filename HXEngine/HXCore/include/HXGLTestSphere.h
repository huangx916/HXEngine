/*
CubeMap采样，渲染测试球，测试用
*/
#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXMesh;
	class HXGLTestSphere
	{
	public:
		HXGLTestSphere();
		~HXGLTestSphere();

		void Initialize();
		void Render(GLuint tex_obj);

	private:
		GLuint ibl_diff_prog;

		GLint render_mvp_matrix_loc;
		GLint world_matrix_loc;
		GLint albedo_loc;
		GLint roughness_loc;
		GLint metalic_loc;
		GLint eye_pos_loc;
		GLint tex_uniform_loc;

		HXMesh* sphereMesh;
	};
}
