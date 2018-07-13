#include "..\include\HXGameObject.h"
#include "HXMesh.h"
#include "HXCore.h"
#include "HXMath.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	HXGameObject::HXGameObject(std::string strName, HXMesh* pMesh, HXRenderSystem* pRenderSystem)
	{
		m_strName = strName;
		m_pMesh = pMesh;
		m_pFather = NULL;
		m_pTransform = pRenderSystem->CreateTransform();
	}

	HXGameObject::~HXGameObject()
	{
		if (m_pMesh)
		{
			delete m_pMesh;
			m_pMesh = NULL;
		}
		if (m_pTransform)
		{
			delete m_pTransform;
			m_pTransform = NULL;
		}
		for (std::vector<HXGameObject*>::iterator itr = vctChildren.begin(); itr != vctChildren.end(); ++itr)
		{
			delete *itr;
		}
		vctChildren.clear();
	}

	int ntest = 0;
	void HXGameObject::Update()
	{
		/*if (ntest > 100)
		{
			return;
		}
		ntest++;*/

		if (m_pFather)
		{
			m_pTransform->CaculateModelMatrix(m_pFather->m_pTransform->mCurModelMatrix);
		}
		else
		{
			m_pTransform->CaculateModelMatrix();
		}
		if (m_pMesh)
		{
			m_pMesh->UpdateAnimation();
		}
	}

	/*void HXGameObject::Insert_To_RenderList(HXRenderList* pRenderList)
	{
		m_pMesh->Insert_To_RenderList(mPostion, mEulerDegree, mScale, pRenderList);
	}*/

	HXMesh* HXGameObject::GetMesh()
	{
		return m_pMesh;
	}

	HXGameObject* HXGameObject::GetFather()
	{
		return m_pFather;
	}

	void HXGameObject::SetFather(HXGameObject* father)
	{
		m_pFather = father;
	}

	void HXGameObject::AddChild(HXGameObject* child)
	{
		vctChildren.push_back(child);
	}

	std::vector<HXGameObject*>& HXGameObject::GetChildren()
	{
		return vctChildren;
	}

	HXITransform* HXGameObject::GetTransform()
	{
		return m_pTransform;
	}

	bool HXGameObject::GetCastShadow() const
	{
		return m_bCastShadow;
	}

	void HXGameObject::SetCastShadow(bool bCastShadow)
	{
		m_bCastShadow = bCastShadow;
		if (m_pMesh)
		{
			for (std::vector<HXSubMesh*>::iterator itr = m_pMesh->subMeshList.begin(); itr != m_pMesh->subMeshList.end(); ++itr)
			{
				// 设置是否投射阴影
				(*itr)->IsCastShadow = bCastShadow;
			}
		}
	}
}


