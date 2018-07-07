#pragma once
#include "HXCommon.h"
#include "HXMaterial.h"
#include "HXGDITextureBMP.h"

namespace HX3D
{
	class HXGDIMaterial : public HXMaterial
	{
	public:
		HXGDIMaterial(HXMaterialInfo* pMatInfo);
		~HXGDIMaterial();

		HXGDITextureBMP* GetTexture();
	};
}


