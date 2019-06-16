#pragma once
#include "HXCommon.h"
#include "HXTextureInfo.h"
#include "HXTextureMetaData.h"

namespace HX3D
{
	enum TextureType
	{
		TEX_NONE = 0,
		TEX_2D,
		TEX_3D,
		TEX_CUBE,
	};

	enum TextureFormat
	{
		FMT_R8G8B8 = 0,
		FMT_R8G8B8A8,
		FMT_R16G16,
		FMT_R16G16B16A16F,
		FMT_R32G32B32A32F,
		FMT_R16G16B16F,
		FMT_DEPTH32F,
	};

	class HXITexture
	{
	public:
		HXITexture() {};
		virtual ~HXITexture() {};

		HXTextureMetaData* m_pMetaData = NULL;
	};
}