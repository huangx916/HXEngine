#pragma once
#include "HXCommon.h"
#include "vgl.h"
#include "vmath.h"

namespace HX3D
{
	class HXGLShadowMap
	{
	public:
		HXGLShadowMap();
		~HXGLShadowMap();

		void Initialize();
		void PreRender();
		void PostRender();

		// shadow mapping
		GLint original_fbo;

		GLuint render_light_prog;
		struct
		{
			GLint model_view_projection_matrix;
		}render_light_uniforms;
		GLuint depth_fbo;
		GLuint depth_texture;

		vmath::mat4 light_view_matrix;
		vmath::mat4 light_projection_matrix;
	};
}