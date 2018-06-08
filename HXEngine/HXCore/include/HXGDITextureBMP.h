#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "HXBitmap.h"

namespace HX3D
{
	class HXGDITextureBMP : public HXITexture
	{
	public:
		HXGDITextureBMP(std::string strTextureFile);
		~HXGDITextureBMP();
		
		HXBitmap* mBitmap;
	};
}

