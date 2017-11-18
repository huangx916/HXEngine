#pragma once
#include "HXCommon.h"
#include "HXRenderable.h"
#include "HXVector.h"

namespace HX3D
{
	struct HXRenderList;
	struct HXFrustum;
	class HXICamera;
	class HXGDIRenderable : public HXRenderable
	{
	public:
		HXGDIRenderable();
		~HXGDIRenderable();

		virtual void SetModelMatrix(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale);
		// 提取到外层计算提高效率
		virtual void SetViewMatrix(HXICamera* pCamera);
		// 提取到外层计算提高效率
		virtual void SetProjectionMatrix(HXICamera* pCamera);
		// 生成渲染系统需要的内容（例如 OPENGL 的 VBO等）
		virtual void GenerateArguments(HXSubMesh* pSubMesh);
		virtual void Render();

		HXRenderList*	mRenderList;

		HXVector3D mPos;
		HXVector3D mEulerDegree;
		HXVector3D mScale;

		HXFrustum* mFrustum;
	};
}