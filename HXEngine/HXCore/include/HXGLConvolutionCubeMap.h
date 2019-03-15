/*
对CubeMap进行半球空间卷积，渲染到低分辨率的CubeMap中
*/
#pragma once
#include "HXCommon.h"
#include "vgl.h"

namespace HX3D
{
	class HXMesh;
	class HXGLConvolutionCubeMap
	{
	public:
		HXGLConvolutionCubeMap();
		~HXGLConvolutionCubeMap();

		void Preprocess(GLuint tex_obj);
		GLuint GetCubeMapTexture();

	private:
		void Initialize();
		void Release();
		void PreRender();
		void Render(GLuint tex_obj);
		void PostRender();
		void GenerateMipmap();

	private:
		GLint original_fbo;
		GLuint convolution_prog;
		GLuint cube_map_fbo;
		GLuint cube_map_texture;

		GLint tex_uniform_loc;
		GLint face_uniform_loc;

		HXMesh* quadMesh;

	};
}
