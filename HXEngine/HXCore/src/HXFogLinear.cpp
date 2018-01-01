#include "..\include\HXFogLinear.h"
#include "HXLoadConfigScene.h"

namespace HX3D
{
	HXFogLinear::HXFogLinear()
	{

	}
	HXFogLinear::HXFogLinear(HXFogInfo* info)
	{
		fogType = HXFogType::FOG_Linear;
		useFog = info->bUse;
		fogColor = info->color;
		fogStart = info->start;
		fogEnd = info->end;
	}
	HXFogLinear::~HXFogLinear()
	{
	}


}
