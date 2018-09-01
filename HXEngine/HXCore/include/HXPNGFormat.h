#pragma once
#include <stdint.h>

namespace HX3D
{
	struct PNGTextureInfo
	{
		int32_t width;
		int32_t height;
		//uint32_t format;
		int32_t internalFormat;
		//uint32_t id;
		unsigned char* texels;
	};
}