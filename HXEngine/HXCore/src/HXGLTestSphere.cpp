#include "..\include\HXGLTestSphere.h"
#include "HXResourceManager.h"
#include "HXMesh.h"
#include "HXGLRenderable.h"
#include "HXRoot.h"
#include "LoadShaders.h"
#include "HXGLRenderSystem.h"

namespace HX3D
{
	HXGLTestSphere::HXGLTestSphere()
	{
	}

	HXGLTestSphere::~HXGLTestSphere()
	{
	}

	void HXGLTestSphere::Initialize()
	{
		//HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("prefab/SkyBox/SkyBox.FBX", "");
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("prefab/SphereIBL/Sphere.FBX", "");
		sphereMesh = pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem());

		ShaderInfo ibl_diff_shaders[] =
		{
			{ GL_VERTEX_SHADER, "builtin/IBL_Diff.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/IBL_Diff.frag" },
			/*{ GL_VERTEX_SHADER, "builtin/Error.vert" },
			{ GL_FRAGMENT_SHADER, "builtin/Error.frag" },*/
			{ GL_NONE }
		};
		ibl_diff_prog = LoadShaders(ibl_diff_shaders);
		glUseProgram(ibl_diff_prog);
		render_mvp_matrix_loc = glGetUniformLocation(ibl_diff_prog, "mvp_matrix");
		world_matrix_loc = glGetUniformLocation(ibl_diff_prog, "model_matrix");
		albedo_loc = glGetUniformLocation(ibl_diff_prog, "hx_Albedo");
		roughness_loc = glGetUniformLocation(ibl_diff_prog, "hx_Roughness");
		metalic_loc = glGetUniformLocation(ibl_diff_prog, "hx_Metalic");
		eye_pos_loc = glGetUniformLocation(ibl_diff_prog, "eyePos");
		tex_uniform_loc = glGetUniformLocation(ibl_diff_prog, "hx_IrradianceMap");
	}

	void HXGLTestSphere::Render(GLuint tex_obj)
	{
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
		glUseProgram(ibl_diff_prog);

		int nTexIndex = 0;
		// 采样器
		glUniform1i(tex_uniform_loc, nTexIndex);
		// 纹理单元
		glActiveTexture(GL_TEXTURE0 + nTexIndex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_obj);

		glUniform3f(albedo_loc, 1.0f, 1.0f, 1.0f);
		glUniform1f(roughness_loc, 0.2f);
		glUniform1f(metalic_loc, 0.2f);
		glUniform3f(eye_pos_loc, 0.0f, 0.0f, 150.0f);

		vmath::mat4 mMatrixModel = vmath::mat4::identity();
		vmath::mat4 mMatrixProjection = vmath::perspectiveExt(60, 1.0f * HXGLRenderSystem::gCurScreenWidth / HXGLRenderSystem::gCurScreenHeight, 0.01f, 1000);
		vmath::mat4 mMatrixView = vmath::lookat(vmath::vec3(0, 0, 150), vmath::vec3(0, 0, 0), vmath::vec3(0, 1, 0));

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_FRONT);

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClearDepth(1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//glClear(GL_DEPTH_BUFFER_BIT);
		vmath::mat4 mvp = mMatrixProjection * mMatrixView * mMatrixModel;
		glUniformMatrix4fv(render_mvp_matrix_loc, 1, GL_FALSE, mvp);
		glUniformMatrix4fv(world_matrix_loc, 1, GL_FALSE, mMatrixModel);

		sphereMesh->subMeshList[0]->renderable->Render();
	}
}
