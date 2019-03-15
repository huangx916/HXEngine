/*
球形贴图采样，渲染到CubeMap中
*/
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
		
		void Preprocess(std::string strERMapFile);
		GLuint GetCubeMapTexture();

	private:
		void Initialize();
		void Release();
		void PreRender();
		void Render(std::string strERMapFile);
		void PostRender();
		void GenerateMipmap();

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

