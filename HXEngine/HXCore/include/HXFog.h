#pragma once
#include "HXCommon.h"

namespace HX3D
{
	enum HXFogType
	{
		FOG_Linear = 0,
		FOG_EXP = 1,
		FOG_EXPX = 2,
	};

	struct HXFogInfo;
	class HXFog
	{
	public:
		HXFog();
		HXFog(HXFogInfo* info);
		virtual ~HXFog();

		bool useFog;
		HXFogType fogType;
		HXColor fogColor;

		float fogStart;
		float fogEnd;
		float fogDensity;
		float fogGradiant;
	};
}
