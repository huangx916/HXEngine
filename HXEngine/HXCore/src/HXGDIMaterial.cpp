#include "..\include\HXGDIMaterial.h"
#include "HXResourceManager.h"

namespace HX3D
{
	HXGDIMaterial::HXGDIMaterial(HXMaterialInfo* pMatInfo)
	{
		HXMaterial::SetMaterialInfo(pMatInfo);
	}

	HXGDIMaterial::~HXGDIMaterial()
	{
		
	}

	HXGDITextureBMP* HXGDIMaterial::GetTexture()
	{
		// GDI默认只使用第一张贴图
		HXGDITextureBMP* tex = (HXGDITextureBMP*)HXResourceManager::GetInstance()->GetTexture("GDI_" + mMatInfo->vctMatProperty[0].value);
		if (NULL == tex)
		{
			tex = new HXGDITextureBMP(mMatInfo->vctMatProperty[0].value);
			HXResourceManager::GetInstance()->AddTexture("GDI_" + mMatInfo->vctMatProperty[0].value, tex);
		}
		return tex;
	}
}
