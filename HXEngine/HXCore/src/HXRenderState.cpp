#include "..\include\HXRenderState.h"
#include "HXResourceManager.h"

namespace HX3D
{
	HXMaterial* HXRenderState::m_pMaterial = NULL;

	HXRenderState::HXRenderState()
	{
	}

	HXRenderState::~HXRenderState()
	{
	}

	void HXRenderState::Reset()
	{
		m_pMaterial = NULL;
	}

	HXMaterial* HXRenderState::GetMaterial()
	{
		return m_pMaterial;
	}

	void HXRenderState::SetMaterial(std::string materialname)
	{
		m_pMaterial = HXResourceManager::GetInstance()->GetMaterial(materialname);
	}
}
