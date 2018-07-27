#include "..\include\HXGLShadowMap.h"
#include "LoadShaders.h"
#include "HXGLRenderSystem.h"

namespace HX3D
{
	HXGLShadowMap::HXGLShadowMap()
	{
	}


	HXGLShadowMap::~HXGLShadowMap()
	{
	}

	void HXGLShadowMap::Initialize()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		// shadow //////////////////////////////////////////////////////////////////////
		ShaderInfo light_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/ShadowMap.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/ShadowMap.frag" },
			{ GL_NONE }
		};
		render_light_prog = LoadShaders(light_shaders);
		// Get the location of the projetion_matrix uniform
		render_light_uniforms.model_view_projection_matrix = glGetUniformLocation(render_light_prog, "model_view_projection_matrix");

		// Create a depth texture
		glGenTextures(1, &depth_texture);
		glBindTexture(GL_TEXTURE_2D, depth_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		GLfloat border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Create FBO to render depth into
		glGenFramebuffers(1, &depth_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);

		//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depth_texture, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);
		glDrawBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
	}

	void HXGLShadowMap::PreRender()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		//float t = float(GetTickCount() & 0xFFFF) / float(0xFFFF);
		//static float q = 0.0f;
		static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
		static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
		static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

		//vmath::vec3 light_position = vmath::vec3(sinf(t * 6.0f * 3.141592f) * 300.0f, 200.0f, cosf(t * 4.0f * 3.141592f) * 100.0f + 250.0f);
		//vec3 light_position = vec3(sinf(t * 6.0f * 3.141592f) * 150.0f, 100.0f, cosf(t * 4.0f * 3.141592f) * 50.0f + 125.0f);
		//vmath::vec3 light_position = vmath::vec3(sinf(t * 6.0f * 3.141592f) * 40,40, cosf(t * 4.0f * 3.141592f) * 40);
		// TODO:
		vmath::vec3 light_position = vmath::vec3(5, 5, 5);
		// Setup
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_TRUE);

		// Matrices for rendering the scene
		//vmath::mat4 scene_model_matrix = rotate(t * 720.0f, Y);
		/*vmath::mat4 scene_view_matrix = vmath::translate(0.0f, 0.0f, -300.0f);
		vmath::mat4 scene_projection_matrix = vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, FRUSTUM_DEPTH);*/
		const vmath::mat4 scale_bias_matrix = vmath::mat4(vmath::vec4(0.5f, 0.0f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 0.5f, 0.0f, 0.0f),
			vmath::vec4(0.0f, 0.0f, 0.5f, 0.0f),
			vmath::vec4(0.5f, 0.5f, 0.5f, 1.0f));

		// Matrices used when rendering from the light's position
		light_view_matrix = vmath::lookat(light_position, vmath::vec3(0.0f), Y);
		//vmath::mat4 matrix(vmath::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, FRUSTUM_DEPTH));
		vmath::mat4 matrix(vmath::Ortho(-ORTHO_HALF_SIZE, ORTHO_HALF_SIZE, -ORTHO_HALF_SIZE, ORTHO_HALF_SIZE, 1.0f, FRUSTUM_DEPTH));
		light_projection_matrix = matrix;

		// Now we render from the light's position into the depth buffer.
		// Select the appropriate program
		glUseProgram(render_light_prog);
		//glUniformMatrix4fv(render_light_uniforms.model_view_projection_matrix, 1, GL_FALSE, light_projection_matrix * light_view_matrix * scene_model_matrix);
		//glUniformMatrix4fv(render_light_uniforms.model_view_projection_matrix, 1, GL_FALSE, scene_projection_matrix * scene_view_matrix * scene_model_matrix);

		// Bind the 'depth only' FBO and set the viewport to the size of the depth texture
		glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
		//glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
		glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);
		//glViewport(0, 0, current_width, current_height);

		// Clear
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// Enable polygon offset to resolve depth-fighting isuses
		glEnable(GL_POLYGON_OFFSET_FILL);
		//glPolygonOffset(2.0f, 4.0f);
		glPolygonOffset(1.0f, 2.0f);
	}

	void HXGLShadowMap::PostRender()
	{
		glDisable(GL_POLYGON_OFFSET_FILL);

		// Restore the default framebuffer and field of view
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
	}
}
