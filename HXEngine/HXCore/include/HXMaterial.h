#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXBitmap;
	class HXMaterial
	{
	public:
		HXMaterial();
		~HXMaterial();

		bool LoadMaterialFile(std::string strMaterialName);
		HXBitmap* UsedTexture();
		HXCOLOR GetPixelRatio(float fX, float fY);

		HXBitmap* mBitmap;
	};
}

