#include "..\include\HXGLSpecularLDCubeMap.h"
#include "LoadShaders.h"
#include "HXRenderable.h"
#include "HXGLTexture.h"
#include "HXResourceManager.h"
#include "HXRoot.h"
#include "HXMesh.h"
#include "HXGLRenderable.h"
#include "HXGLCamera.h"
#include "HXGLRenderSystem.h"

namespace HX3D
{
	HXGLSpecularLDCubeMap::HXGLSpecularLDCubeMap()
	:ld_prog(-1)
	,cube_map_texture(-1)
	{
		for (int i = 0; i < 9; ++i)
		{
			cube_map_fbo[i] = -1;
		}
	}

	HXGLSpecularLDCubeMap::~HXGLSpecularLDCubeMap()
	{
		Release();
	}

	void HXGLSpecularLDCubeMap::Preprocess(GLuint tex_obj)
	{
		Initialize();
		PreRender();
		Render(tex_obj);
		PostRender();
	}

	void HXGLSpecularLDCubeMap::Initialize()
	{
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("Quad", "");
		quadMesh = pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem());

		ShaderInfo ld_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/specular_ld.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/specular_ld.frag" },
			{ GL_NONE }
		};
		ld_prog = LoadShaders(ld_shaders);
		glUseProgram(ld_prog);
		tex_uniform_loc = glGetUniformLocation(ld_prog, "hx_CubeMap");
		face_uniform_loc = glGetUniformLocation(ld_prog, "hx_FaceIndex");
		roughness_uniform_loc = glGetUniformLocation(ld_prog, "hx_Roughness");

		// render target texture
		glGenTextures(1, &cube_map_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		for (int32_t i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16, 256, 256, 0, GL_RGBA, GL_UNSIGNED_SHORT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//if (enableMipmapping) 
		{
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		//else 
		//{
		//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		int32_t width = 256, height = 256;
		for (int32_t i = 0; i < 9; i++) {
			// render target fbo
			glGenFramebuffers(1, &cube_map_fbo[i]);
			glBindFramebuffer(GL_FRAMEBUFFER, cube_map_fbo[i]);
			// bind texture to fbo
			GLint face[6] = {
				GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			};
			for (int32_t j = 0; j < 6; j++)
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + j, face[j], cube_map_texture, i);
			}
			width /= 2;
			height /= 2;
		}
		
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
	}

	void HXGLSpecularLDCubeMap::Release()
	{
		HX_SAFE_DELETE(quadMesh);

		for (int i = 0; i < 9; ++i)
		{
			if (cube_map_fbo[i] != -1)
			{
				glBindRenderbuffer(GL_RENDERBUFFER, original_fbo);
				glDeleteRenderbuffers(1, &cube_map_fbo[i]);
				cube_map_fbo[i] = -1;
			}
		}

		if (cube_map_texture != -1) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDeleteTextures(1, &cube_map_texture);
			cube_map_texture = -1;
		}

		/*if (m_VertexShader != nullptr) {
		HX_SAFE_DELETE(m_VertexShader);
		}
		if (m_FragmentShader != nullptr) {
		HX_SAFE_DELETE(m_FragmentShader);
		}*/
		if (ld_prog != -1) {
			glDeleteProgram(ld_prog);
			ld_prog = -1;
		}
	}

	void HXGLSpecularLDCubeMap::PreRender()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		glUseProgram(ld_prog);
	}

	void HXGLSpecularLDCubeMap::Render(GLuint tex_obj)
	{
		int nTexIndex = 0;
		// 采样器
		glUniform1i(tex_uniform_loc, nTexIndex);
		// 纹理单元
		glActiveTexture(GL_TEXTURE0 + nTexIndex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_obj);

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		int32_t miplevels = log(256) / log(2) + 1;
		float roughnessStep = 1.0f / miplevels;
		int32_t width = 256, height = 256;
		for (int32_t j = 0; j < miplevels; j++) 
		{
			// Render Target
			glBindFramebuffer(GL_FRAMEBUFFER, cube_map_fbo[j]);
			// View port
			glViewport(0, 0, width, height);

			width /= 2;
			height /= 2;

			for (int32_t i = 0; i < 6; i++) {
				// Set Draw Color Buffer
				glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);	// 重点
				// Clear
				glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
				glClearDepth(1.0f);
				glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
				// Setup uniform
				glUniform1i(face_uniform_loc, i);
				glUniform1f(roughness_uniform_loc, j * roughnessStep);
				// Draw
				quadMesh->subMeshList[0]->renderable->Render();
			}
		}
	}

	void HXGLSpecularLDCubeMap::PostRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
	}

	GLuint HXGLSpecularLDCubeMap::GetCubeMapTexture()
	{
		return cube_map_texture;
	}
}