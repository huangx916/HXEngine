#pragma once
#include "HXCommon.h"
#include "HXRenderable.h"
#include "vgl.h"
#include "vmath.h"

namespace HX3D
{
	enum Attrib_IDs
	{
		vPosition = 0,
		vColor = 1,
		vUV = 2,
	};

	class HXICamera;
	class HXGLRenderable : public HXRenderable
	{
	public:
		HXGLRenderable();
		~HXGLRenderable();

		virtual void SetModelMatrix(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale);
		// 提取到外层计算提高效率
		virtual void SetViewMatrix(HXICamera* pCamera);
		// 提取到外层计算提高效率
		virtual void SetProjectionMatrix(HXICamera* pCamera);
		// 生成渲染系统需要的内容（例如 OPENGL 的 VBO等）
		virtual void GenerateArguments(HXSubMesh* pSubMesh);
		virtual void Render();

		vmath::mat4 mMatrixModel;
		vmath::mat4 mMatrixView;
		vmath::mat4 mMatrixProjection;

		GLuint mVAO;
		GLuint mVBO;
		GLuint program;
		GLint render_model_matrix_loc;
		GLint render_view_matrix_loc;
		GLint render_projection_matrix_loc;
		GLint render_mvp_matrix_loc;
	};
}
