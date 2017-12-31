#pragma once
#include "HXCommon.h"

namespace HX3D
{
	enum HXFogType
	{
		FOG_Linear,
		FOG_EXP,
		FOG_EXPX
	};

	class HXFogBase
	{
	public:
		HXFogBase() {};
		virtual ~HXFogBase() {};

		bool useFog;
		HXFogType fogType;
		HXCOLOR fogColor;
	};
}
