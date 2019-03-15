#include "..\include\HXGLConvolutionCubeMap.h"
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
	HXGLConvolutionCubeMap::HXGLConvolutionCubeMap()
	{

	}

	HXGLConvolutionCubeMap::~HXGLConvolutionCubeMap()
	{
		Release();
	}

	void HXGLConvolutionCubeMap::Preprocess(GLuint tex_obj)
	{
		Initialize();
		PreRender();
		Render(tex_obj);
		GenerateMipmap();
		PostRender();
	}

	void HXGLConvolutionCubeMap::Initialize()
	{
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("Quad", "");
		quadMesh = pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem());

		ShaderInfo convolution_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/convolution.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/convolution.frag" },
			{ GL_NONE }
		};
		convolution_prog = LoadShaders(convolution_shaders);
		glUseProgram(convolution_prog);
		tex_uniform_loc = glGetUniformLocation(convolution_prog, "hx_CubeMap");
		face_uniform_loc = glGetUniformLocation(convolution_prog, "hx_FaceIndex");

		// render target
		glGenTextures(1, &cube_map_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		for (int32_t i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16, 32, 32, 0, GL_RGBA, GL_UNSIGNED_SHORT, nullptr);
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

		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
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

		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
	}

	void HXGLConvolutionCubeMap::Release()
	{
		HX_SAFE_DELETE(quadMesh);
	}

	void HXGLConvolutionCubeMap::PreRender()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, cube_map_fbo);
		glUseProgram(convolution_prog);
		glViewport(0, 0, 32, 32);
	}

	void HXGLConvolutionCubeMap::Render(GLuint tex_obj)
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

		for (int i = 0; i < 6; ++i)
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);	// 重点
			glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
			glClearDepth(1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			
			glUniform1i(face_uniform_loc, i);
			quadMesh->subMeshList[0]->renderable->Render();
		}
	}

	void HXGLConvolutionCubeMap::PostRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
	}

	void HXGLConvolutionCubeMap::GenerateMipmap()
	{
		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	GLuint HXGLConvolutionCubeMap::GetCubeMapTexture()
	{
		return cube_map_texture;
	}
}