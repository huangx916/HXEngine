#include "..\include\HXGameObject.h"
#include "HXMesh.h"
#include "HXCore.h"

namespace HX3D
{
	HXGameObject::HXGameObject(HXMesh* pMesh)
	{
		m_pMesh = pMesh;

		mPostion = HXVector3D(0,0,0);
		mEulerDegree = HXVector3D(0,0,0);
		mScale = HXVector3D(1,1,1);
	}


	HXGameObject::~HXGameObject()
	{
		if (m_pMesh)
		{
			delete m_pMesh;
			m_pMesh = NULL;
		}
	}

	void HXGameObject::Update()
	{
		if (m_pMesh)
		{
			m_pMesh->UpdateAnimation();
		}
	}

	void HXGameObject::Insert_To_RenderList(HXRenderList* pRenderList)
	{
		m_pMesh->Insert_To_RenderList(mPostion, mEulerDegree, mScale, pRenderList);
	}

	void HXGameObject::SetPostion(const HXVector3D& pos)
	{
		mPostion = pos;
	}

	HXVector3D HXGameObject::GetPosition()
	{
		return mPostion;
	}

	void HXGameObject::Move(const HXVector3D& mov)
	{
		mPostion += mov;
	}

	void HXGameObject::SetRotation(const HXVector3D& rotation)
	{
		mEulerDegree = rotation;
	}

	HXVector3D HXGameObject::GetRotation()
	{
		return mEulerDegree;
	}

	void HXGameObject::Pitch(float fDegree)
	{
		mEulerDegree.x = fDegree;
	}

	void HXGameObject::Yaw(float fDegree)
	{
		mEulerDegree.y = fDegree;
	}

	void HXGameObject::Roll(float fDegree)
	{
		mEulerDegree.z = fDegree;
	}

	void HXGameObject::SetScale(const HXVector3D& scale)
	{
		mScale = scale;
	}
	HXVector3D HXGameObject::GetScale()
	{
		return mScale;
	}

	HXMesh* HXGameObject::GetMesh()
	{
		return m_pMesh;
	}
}


