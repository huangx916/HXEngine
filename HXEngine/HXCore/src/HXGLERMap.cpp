#include "..\include\HXGLERMap.h"
#include "LoadShaders.h"
#include "HXRenderable.h"
#include "HXGLTexture.h"
#include "HXResourceManager.h"

namespace HX3D
{
	HXGLERMap::HXGLERMap()
	{
	}

	HXGLERMap::~HXGLERMap()
	{
	}

	void HXGLERMap::Initialize()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		// shader //////////////////////////////////////////////////////////////////////
		ShaderInfo er_map_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/EquirectangularMap.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/EquirectangularMap.frag" },
			{ GL_NONE }
		};
		equirectangular_map_prog = LoadShaders(er_map_shaders);
		glUseProgram(equirectangular_map_prog);

		render_mvp_matrix_loc = glGetUniformLocation(equirectangular_map_prog, "mvp_matrix");
		tex_uniform_loc = glGetUniformLocation(equirectangular_map_prog, "EquirectangularMap");


		glGenTextures(1, &cube_map_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		for (int32_t i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_SHORT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//if (enableMipmapping) 
		{
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		//else 
		//{
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);


		glGenFramebuffers(1, &cube_map_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, cube_map_fbo);

		GLint face[6] = {
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		};
		for (int32_t i = 0; i < 6; i++) 
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, face[i], cube_map_texture, 0);
		}
	}

	void HXGLERMap::PreRender()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		glUseProgram(equirectangular_map_prog);
		glBindFramebuffer(GL_FRAMEBUFFER, cube_map_fbo);
		glViewport(0, 0, 1024, 1024);
	}

	void HXGLERMap::Render(HXRenderable* renderable)
	{
		HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture("prefab/_Material/SphereIBL/ermap.hdr");
		if (NULL == tex)
		{
			
			//tex = new HXGLTexture(MPT_TEXTURE, itr->value);
			tex = new HXGLTexture();
			tex->Create("prefab/_Material/SphereIBL/ermap.hdr");
			HXResourceManager::GetInstance()->AddTexture("prefab/_Material/SphereIBL/ermap.hdr", tex);
		}
		int nTexIndex = 0;
		// 采样器
		glUniform1i(tex_uniform_loc, nTexIndex);
		// 纹理单元
		glActiveTexture(GL_TEXTURE0 + nTexIndex);

		glBindTexture(GL_TEXTURE_2D, tex->texObj);

		for (int i = 0; i < 6; ++i)
		{
			glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
			glClearDepth(1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			renderable->Render();
		}
	}

	void HXGLERMap::PostRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
	}
}