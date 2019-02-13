#include "..\include\HXLight.h"
#include "HXMesh.h"
#include "HXLoadConfigScene.h"

namespace HX3D
{
	HXLight::HXLight()
	{
	}

	HXLight::HXLight(HXLightInfo* lightInfo)
	{
		name = lightInfo->name;
		enable = lightInfo->isEnable;
		lightType = lightInfo->lightType;
		color = lightInfo->lightColor;
		direct = lightInfo->lightDir;
		shininess = lightInfo->shininess;
		strength = lightInfo->strength;
		position = lightInfo->lightPos;
		constantAttenuation = lightInfo->constantAttenuation;
		LinearAttenuation = lightInfo->LinearAttenuation;
		QuadraticAttenuation = lightInfo->QuadraticAttenuation;
		ConeDirection = lightInfo->ConeDirection;
		SpotCosCutoff = lightInfo->SpotCosCutoff;
		SpotExponent = lightInfo->SpotExponent;
	}

	HXLight::~HXLight()
	{
	}

	/*HXColor HXLight::VertexLighting(HXVertex* pVertex)
	{
		HXColor col;
		if (lightType == LIGHT_DIRECTION)
		{
			pVertex->normal.normalize();
			direct.normalize();
			float ndotl = pVertex->normal.dotProduct(-direct);

			if (ndotl > 0)
			{
				col = color * pVertex->color * ndotl;
			}
			else
			{
				col = HXColor(0, 0, 0);
			}
		}
		else if (lightType == LIGHT_AMBIENT)
		{
			col = color * pVertex->color;
		}
		return col;
	}*/


}