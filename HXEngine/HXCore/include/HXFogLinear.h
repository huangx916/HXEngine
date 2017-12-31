#pragma once
#include "HXCommon.h"
#include "HXFogBase.h"

namespace HX3D
{
	struct HXFogInfo;
	class HXFogLinear : public HXFogBase
	{
	public:
		HXFogLinear();
		HXFogLinear(HXFogInfo* info);
		~HXFogLinear();

		float fogStart;
		float fogEnd;
	};
}