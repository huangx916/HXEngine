#include "..\include\HXFog.h"
#include "HXLoadConfigScene.h"

namespace HX3D
{
	HXFog::HXFog()
	{

	}

	HXFog::HXFog(HXFogInfo* info)
	{
		fogType = info->type;
		useFog = info->bUse;
		fogColor = info->color;
		fogStart = info->start;
		fogEnd = info->end;
		fogDensity = info->density;
		fogGradiant = info->gradiant;
	}

	HXFog::~HXFog()
	{

	}
}
