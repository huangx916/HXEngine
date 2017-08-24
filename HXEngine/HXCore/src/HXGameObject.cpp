#include "..\include\HXGameObject.h"
#include "HXMesh.h"
#include "HXCore.h"

namespace HX3D
{
	HXGameObject::HXGameObject(HXMesh* pMesh)
	{
		m_pMesh = pMesh;
	}


	HXGameObject::~HXGameObject()
	{
	}

	void HXGameObject::Insert_To_RenderList(HXRenderList* pRenderList)
	{
		m_pMesh->Insert_To_RenderList(mPostion, mEulerDegree, mScale, pRenderList);
	}
}


