#pragma once
namespace HX3D
{
	// Texture file's type
	enum TEXTURE_FILE_TYPE {
		TFT_DDS = 0,
		TFT_HDR,
		TFT_PFC,  // Prefilter CubeMap file format <Customize>
		TFT_PFT,  // Prefilter Table file format <Customize>
		TFT_UNKOWN,
	};

	// Texture type
	enum TEXTURE_TYPE {
		TT_2D = 0,
		TT_3D,
		TT_CUBE,
		TT_UNKOWN,
	};

	// Texture pixel's format type
	enum TEXTURE_PIXEL_FORMAT_TYPE {
		TPFT_R8G8B8 = 0,
		TPFT_A8R8G8B8,
		TPFT_R8G8B8A8,
		TPFT_R16G16,
		TPFT_G16R16,
		TPFT_R16G16B16F,
		TPFT_R16G16B16A16F,
		TPFT_R32G32B32A32F,
		TPFT_UNKOWN,
	};
}
