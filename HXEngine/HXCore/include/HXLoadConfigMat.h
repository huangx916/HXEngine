#pragma once
#include "HXCommon.h"

namespace HX3D
{
	enum EMatPropertyType
	{
		MPT_TEXTURE,
		MPT_FLOAT,
		MPT_FLOAT2,
		MPT_FLOAT3,
		MPT_FLOAT4
	};
	struct HXMaterialProperty
	{
		EMatPropertyType type;
		std::string name;
		std::string value;
		float value1;
		float value2;
		float value3;
		float value4;
	};
	struct HXMaterialInfo
	{
		std::string strShaderFile;
		std::vector<HXMaterialProperty> vctMatProperty;
	};

	class HXLoadConfigMat
	{
	public:
		HXLoadConfigMat();
		~HXLoadConfigMat();

		bool LoadFile(std::string strFileName);

		HXMaterialInfo mMatInfo;
	};
}


