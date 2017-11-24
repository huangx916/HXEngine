#include "..\include\HXRenderState.h"
#include "HXResourceManager.h"
#include "HXGDITextureBMP.h"
#include "HXLoadConfigMat.h"

namespace HX3D
{
	//HXMaterial* HXRenderState::m_pMaterial = NULL;
	HXMaterialInfo* HXRenderState::m_pMatInfo = NULL;
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
		m_pMatInfo = NULL;
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
		HXMaterialInfo* pMatInfo = HXResourceManager::GetInstance()->GetMaterialInfo(strMatInfoFile);
		m_pMatInfo = pMatInfo;
		if (pMatInfo)
		{
			HXGDITextureBMP* tex = (HXGDITextureBMP*)HXResourceManager::GetInstance()->GetTexture("GDI_" + pMatInfo->vctMatProperty[0].value);
			if (NULL == tex)
			{
				tex = new HXGDITextureBMP();
				tex->mBitmap = HXResourceManager::GetInstance()->GetBitmap(pMatInfo->vctMatProperty[0].value + ".bmp");
				HXResourceManager::GetInstance()->AddTexture("GDI_" + pMatInfo->vctMatProperty[0].value, tex);
			}
			m_pTex = tex;
		}
	}
}
