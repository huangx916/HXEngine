#include "..\include\HXMaterial.h"
#include "HXBitmap.h"
#include "HXResourceManager.h"

namespace HX3D
{
	HXMaterial::HXMaterial():mBitmap(NULL)
	{
	}


	HXMaterial::~HXMaterial()
	{
	}

	bool HXMaterial::LoadMaterialFile(std::string strMaterialName)
	{
		// TODO: 读取材质球文本
		std::string strBitmapName = strMaterialName;

		mBitmap = HXResourceManager::GetInstance()->GetBitmap(strBitmapName);

		return true;
	}

	HXBitmap* HXMaterial::UsedTexture()
	{
		return mBitmap;
	}

	HXCOLOR HXMaterial::GetPixelRatio(float fX, float fY)
	{
		if (mBitmap)
		{
			return mBitmap->GetPixelRatio(fX, fY);
		}
		else
		{
			return HXCOLOR();
		}
	}
}

