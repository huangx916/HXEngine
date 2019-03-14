#include "..\include\HXGLCubeMap.h"
#include "HXResourceManager.h"
#include "HXMesh.h"
#include "HXGLRenderable.h"
#include "HXRoot.h"
#include "LoadShaders.h"
#include "HXGLRenderSystem.h"

namespace HX3D
{
	HXGLCubeMap::HXGLCubeMap()
	{
	}

	HXGLCubeMap::~HXGLCubeMap()
	{
	}

	void HXGLCubeMap::Initialize()
	{
		//HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("prefab/SkyBox/SkyBox.FBX", "");
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("prefab/SphereIBL/Sphere.FBX", "");
		cubeMesh = pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem());

		ShaderInfo er_map_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/test_cubemap.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/test_cubemap.frag" },
			{ GL_NONE }
		};
		cube_map_prog = LoadShaders(er_map_shaders);
		glUseProgram(cube_map_prog);
		render_mvp_matrix_loc = glGetUniformLocation(cube_map_prog, "mvp_matrix");
		tex_uniform_loc = glGetUniformLocation(cube_map_prog, "CubeMap");
	}

	void HXGLCubeMap::Render(GLuint tex_obj)
	{
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
		glUseProgram(cube_map_prog);

		int nTexIndex = 0;
		// 采样器
		glUniform1i(tex_uniform_loc, nTexIndex);
		// 纹理单元
		glActiveTexture(GL_TEXTURE0 + nTexIndex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_obj);

		vmath::mat4 mMatrixModel = vmath::mat4::identity();
		vmath::mat4 mMatrixProjection = vmath::perspectiveExt(60, 1.0f * HXGLRenderSystem::gCurScreenWidth / HXGLRenderSystem::gCurScreenHeight, 0.01f, 1000);
		vmath::mat4 mMatrixView = vmath::lookat(vmath::vec3(0, 0, 0), vmath::vec3(0, 0, -1), vmath::vec3(0, 1, 0));

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		vmath::mat4 mvp = mMatrixProjection * mMatrixView * mMatrixModel;
		glUniformMatrix4fv(render_mvp_matrix_loc, 1, GL_FALSE, mvp);
		cubeMesh->subMeshList[0]->renderable->Render();
	}
}
