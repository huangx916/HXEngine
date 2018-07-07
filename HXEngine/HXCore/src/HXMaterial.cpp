#include "..\include\HXMaterial.h"

namespace HX3D
{
	HXMaterial::HXMaterial() : mMatInfo(NULL)
	{
		
	}
	void HXMaterial::SetMaterialInfo(HXMaterialInfo* pMatInfo)
	{
		mMatInfo = pMatInfo;
	}

	HXMaterial::~HXMaterial()
	{
		if (mMatInfo)
		{
			delete mMatInfo;
		}
	}
}
