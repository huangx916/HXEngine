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

		void Initialize();
		void PreRender();
		void Render(GLuint tex_obj);
		void PostRender();
		void GenerateMipmap();

		GLuint GetCubeMapTexture();

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
