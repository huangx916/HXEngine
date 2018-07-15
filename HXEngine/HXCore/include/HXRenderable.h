#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXSubMesh;
	class HXICamera;
	class HXITransform;
	class HXRenderable
	{
	public:
		HXRenderable();
		virtual ~HXRenderable();

		//virtual void SetModelMatrix(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale) = 0;
		virtual void SetModelMatrix(HXMatrix44& mat) = 0;
		virtual void SetViewMatrix(HXICamera* pCamera) = 0;
		virtual void SetProjectionMatrix(HXICamera* pCamera) = 0;
		// 生成具体渲染系统需要的内容（例如 OPENGL 的 VBO等）
		virtual void GenerateArguments(HXSubMesh* pSubMesh);
		virtual void RenderShadowMap() {};
		virtual void Render() = 0;

		HXSubMesh* m_pSubMesh;
		HXITransform* m_pTransform;
	};
}