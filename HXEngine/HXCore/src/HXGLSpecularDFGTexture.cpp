#include "..\include\HXGLSpecularDFGTexture.h"
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
	HXGLSpecularDFGTexture::HXGLSpecularDFGTexture()
	{
	}

	HXGLSpecularDFGTexture::~HXGLSpecularDFGTexture()
	{
		Release();
	}

	void HXGLSpecularDFGTexture::Preprocess()
	{
		Initialize();
		PreRender();
		Render();
		PostRender();
	}

	void HXGLSpecularDFGTexture::Initialize()
	{
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("Quad", "");
		quadMesh = pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem());

		ShaderInfo dfg_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/specular_dfg.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/specular_dfg.frag" },
			{ GL_NONE }
		};
		dfg_prog = LoadShaders(dfg_shaders);
		glUseProgram(dfg_prog);
		tex_uniform_loc = glGetUniformLocation(dfg_prog, "hx_CubeMap");
		face_uniform_loc = glGetUniformLocation(dfg_prog, "hx_FaceIndex");

		// render target texture
		glGenTextures(1, &texture_obj);
		glBindTexture(GL_TEXTURE_2D, texture_obj);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 128, 128, 0, GL_RGBA, GL_FLOAT, nullptr);
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

		// render target fbo
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		glGenFramebuffers(1, &texture_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, texture_fbo);

		// bind texture to fbo
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_obj, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
	}

	void HXGLSpecularDFGTexture::Release()
	{
		HX_SAFE_DELETE(quadMesh);
	}

	void HXGLSpecularDFGTexture::PreRender()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, texture_fbo);
		glUseProgram(dfg_prog);
		glViewport(0, 0, 128, 128);
	}

	void HXGLSpecularDFGTexture::Render()
	{
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		glDrawBuffer(GL_COLOR_ATTACHMENT0);	// ÖØµã
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		quadMesh->subMeshList[0]->renderable->Render();
	}

	void HXGLSpecularDFGTexture::PostRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
	}

	GLuint HXGLSpecularDFGTexture::GetCubeMapTexture()
	{
		return texture_obj;
	}
}
