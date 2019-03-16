#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXMesh;
	class HXGLSpecularLDCubeMap
	{
	public:
		HXGLSpecularLDCubeMap();
		~HXGLSpecularLDCubeMap();

		void Preprocess(GLuint tex_obj);
		GLuint GetCubeMapTexture();

	private:
		void Initialize();
		void Release();
		void PreRender();
		void Render(GLuint tex_obj);
		void PostRender();

	private:
		GLint original_fbo;
		GLuint ld_prog;
		GLuint cube_map_fbo[9];
		GLuint cube_map_texture;

		GLint tex_uniform_loc;
		GLint face_uniform_loc;
		GLint roughness_uniform_loc;

		HXMesh* quadMesh;
	};
}
