#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXTextureReader
	{
	public:
		static int32_t ReadTexture(const char* texture_file_name, int8_t** texture_data, int32_t& texture_width, int32_t& texture_height, int32_t& texture_type, int32_t& pixel_format);
		static void ReleaseData(int8_t** texture_data);
	};
}