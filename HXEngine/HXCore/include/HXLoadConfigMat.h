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
		int nCullFace;	// 0:glDisable(GL_CULL_FACE);1:glFrontFace(GL_CW);2:glFrontFace(GL_CCW);
		int nDepthTest;	// 0:glDisable(GL_DEPTH_TEST);1:glDepthFunc(GL_LESS);ect...
		int nAlphaBlend;// 0:glDisable(GL_BLEND);1:glEnable(GL_BLEND)
		int nSrcAlpha;	// 0:GL_SRC_COLOR;ect...
		int nDestAlpha;	// 0:GL_SRC_COLOR;ect...
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


