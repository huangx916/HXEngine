#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	enum LIGHT_TYPE
	{
		LIGHT_AMBIENT = 0,		// 环境光
		LIGHT_DIRECTION	= 1,	// 平行光
		LIGHT_POINT = 2,		// 点光源
		LIGHT_SPOT = 3,			// 聚光灯
	};

	struct HXVertex;
	struct HXLightInfo;
	class HXLight
	{
	public:
		HXLight();
		HXLight(HXLightInfo* lightInfo);
		~HXLight();
		
		//HXColor VertexLighting(HXVertex* pVertex);

		std::string name;

		bool enable;
		LIGHT_TYPE lightType;
		HXColor color;
		HXVector3D direct;
		float shininess;
		float strength;

		HXVector3D position;
		float constantAttenuation;
		float LinearAttenuation;
		float QuadraticAttenuation;

		HXVector3D ConeDirection;
		float SpotCosCutoff;
		float SpotExponent;
	};
}