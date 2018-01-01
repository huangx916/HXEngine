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
