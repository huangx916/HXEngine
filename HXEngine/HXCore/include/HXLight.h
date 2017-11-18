#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	enum LIGHT_TYPE
	{
		LIGHT_AMBIENT = 0,		// 环境光
		LIGHT_DIRECTION	= 1,	// 平行光
	};

	struct HXVertex;

	class HXLight
	{
	public:
		HXLight(LIGHT_TYPE lightType);
		~HXLight();
		
		HXCOLOR VertexLighting(HXVertex* pVertex);

		bool enable;
		LIGHT_TYPE lightType;
		HXVector3D position;
		HXVector3D direct;
		HXCOLOR color;
	};
}