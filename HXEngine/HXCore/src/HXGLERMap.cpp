#include "..\include\HXGLERMap.h"
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
	HXGLERMap::HXGLERMap()
	:equirectangular_map_prog(-1)
	,cube_map_fbo(-1)
	,cube_map_texture(-1)
	{
		
	}

	HXGLERMap::~HXGLERMap()
	{
		Release();
	}

	void HXGLERMap::Preprocess(std::string strERMapFile)
	{
		Initialize();
		PreRender();
		Render(strERMapFile);
		GenerateMipmap();
		PostRender();
	}

	void HXGLERMap::Initialize()
	{
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("prefab/SkySphere/Sphere.FBX", "");
		sphereMesh = pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem());

		ShaderInfo er_map_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/filtering_ermap.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/filtering_ermap.frag" },
			{ GL_NONE }
		};
		equirectangular_map_prog = LoadShaders(er_map_shaders);
		glUseProgram(equirectangular_map_prog);
		render_mvp_matrix_loc = glGetUniformLocation(equirectangular_map_prog, "mvp_matrix");
		tex_uniform_loc = glGetUniformLocation(equirectangular_map_prog, "EquirectangularMap");

		// render target
		glGenTextures(1, &cube_map_texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		for (int32_t i = 0; i < 6; i++) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_SHORT, nullptr);
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

	void HXGLERMap::Release()
	{
		HX_SAFE_DELETE(sphereMesh);

		if (cube_map_fbo != -1)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, original_fbo);
			glDeleteRenderbuffers(1, &cube_map_fbo);
			cube_map_fbo = -1;
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
		if (equirectangular_map_prog != -1) {
			glDeleteProgram(equirectangular_map_prog);
			equirectangular_map_prog = -1;
		}
	}

	void HXGLERMap::PreRender()
	{
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &original_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, cube_map_fbo);
		glUseProgram(equirectangular_map_prog);
		glViewport(0, 0, 1024, 1024);
	}

	void HXGLERMap::Render(std::string strERMapFile)
	{
		//std::string file = "prefab/_Material/SphereIBL/ermap2.hdr";
		std::string file = strERMapFile;
		HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture(file);
		if (NULL == tex)
		{
			tex = new HXGLTexture();
			tex->Create(file.c_str());
			HXResourceManager::GetInstance()->AddTexture(file, tex);
		}
		int nTexIndex = 0;
		// 采样器
		glUniform1i(tex_uniform_loc, nTexIndex);
		// 纹理单元
		glActiveTexture(GL_TEXTURE0 + nTexIndex);

		glBindTexture(GL_TEXTURE_2D, tex->texObj);

		vmath::mat4 mMatrixModel = vmath::mat4::identity();
		vmath::mat4 mMatrixProjection = vmath::perspectiveExt(90.0f, 1.0f, 0.1f, 1000.0f);
		//vmath::mat4 mMatrixView = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(0, 0, -1), vmath::vec3(0, 1, 0));
		vmath::mat4 mMatrixViewList[6];
		mMatrixViewList[0] = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(1, 0, 0), vmath::vec3(0, 1, 0));
		mMatrixViewList[1] = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(-1, 0, 0), vmath::vec3(0, 1, 0));
		mMatrixViewList[2] = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(0, 1, 0), vmath::vec3(0, 0, 1));
		mMatrixViewList[3] = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(0, -1, 0), vmath::vec3(0, 0, -1));
		mMatrixViewList[4] = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(0, 0, 1), vmath::vec3(0, 1, 0));
		mMatrixViewList[5] = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(0, 0, -1), vmath::vec3(0, 1, 0));
		
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		for (int i = 0; i < 6; ++i)
		{
			glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);	// 重点
			glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
			glClearDepth(1.0f);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			vmath::mat4 mvp = mMatrixProjection * mMatrixViewList[i] * mMatrixModel;
			glUniformMatrix4fv(render_mvp_matrix_loc, 1, GL_FALSE, mvp);
			sphereMesh->subMeshList[0]->renderable->Render();
		}
	}

	void HXGLERMap::PostRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, original_fbo);
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
	}

	void HXGLERMap::GenerateMipmap()
	{
		glEnable(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}

	GLuint HXGLERMap::GetCubeMapTexture()
	{
		return cube_map_texture;
	}
}