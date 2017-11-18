#include "..\include\HXGDIRenderable.h"
#include "HXRenderState.h"
#include "HXCore.h"
#include "HXGDICamera.h"

namespace HX3D
{
	HXGDIRenderable::HXGDIRenderable()
	{
		mRenderList = new HXRenderList();
	}

	HXGDIRenderable::~HXGDIRenderable()
	{
		delete mRenderList;
	}

	void HXGDIRenderable::SetModelMatrix(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale)
	{
		mPos = pos;
		// important 为和OPENGL保持方向一致 X轴需要反向
		mPos.x = -mPos.x;
		mEulerDegree = eulerDegree;
		mScale = scale;
	}

	void HXGDIRenderable::SetViewMatrix(HXICamera* pCamera)
	{
		mFrustum = ((HXGDICamera*)pCamera)->mFrustum;
	}

	void HXGDIRenderable::SetProjectionMatrix(HXICamera* pCamera)
	{
		mFrustum = ((HXGDICamera*)pCamera)->mFrustum;
	}

	void HXGDIRenderable::GenerateArguments(HXSubMesh* pSubMesh)
	{
		HXRenderable::GenerateArguments(pSubMesh);
	}

	void HXGDIRenderable::Render()
	{
		if (NULL == mFrustum)
		{
			return;
		}

		HXRenderState::Reset();
		HXRenderState::SetMaterial(m_pSubMesh->materialName);

		m_pSubMesh->Insert_To_RenderList(mPos, mEulerDegree, mScale, mRenderList);
		Culling_Backface_RenderList(mRenderList, mFrustum);
		// TODO: 光照
		// World_Space_Vertex_Lighting(mRenderList, &lightVct);
		World_To_Camera_RenderList(mRenderList, mFrustum);
		Camera_To_Project_RenderList(mRenderList, mFrustum);
		Project_To_ViewPort_RenderList(mRenderList, mFrustum);
		//Draw_RenderList_Wire(mRenderList);
		Draw_RenderList_Texture_Solid(mRenderList);
	}
}
