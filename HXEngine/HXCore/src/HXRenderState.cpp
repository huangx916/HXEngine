#include "..\include\HXRenderState.h"
#include "HXResourceManager.h"
#include "HXGDITextureBMP.h"
#include "HXLoadConfigMat.h"
#include "HXMaterial.h"
#include "HXGDIMaterial.h"

namespace HX3D
{
	//HXMaterial* HXRenderState::m_pMaterial = NULL;
	HXMaterial* HXRenderState::m_pMat = NULL;
	HXGDITextureBMP* HXRenderState::m_pTex = NULL;
	HXRenderState::HXRenderState()
	{
	}

	HXRenderState::~HXRenderState()
	{
	}

	void HXRenderState::Reset()
	{
		//m_pMaterial = NULL;
		m_pMat = NULL;
		m_pTex = NULL;
	}

	/*HXMaterial* HXRenderState::GetMaterial()
	{
		return m_pMaterial;
	}

	void HXRenderState::SetMaterial(std::string materialname)
	{
		m_pMaterial = HXResourceManager::GetInstance()->GetMaterial(materialname);
	}*/

	void HXRenderState::SetMatInfoAndTexture(std::string strMatInfoFile)
	{
		HXGDIMaterial* pMat = (HXGDIMaterial*)HXResourceManager::GetInstance()->GetMaterial(strMatInfoFile);
		m_pMat = pMat;
		if (pMat)
		{
			m_pTex = pMat->GetTexture();
		}
	}
}
