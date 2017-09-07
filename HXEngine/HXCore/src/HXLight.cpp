#include "..\include\HXLight.h"
#include "HXMesh.h"

namespace HX3D
{
	HXLight::HXLight(LIGHT_TYPE lightType_):lightType(lightType_), enable(true)
	{
	}


	HXLight::~HXLight()
	{
	}

	HXCOLOR HXLight::VertexLighting(HXVertex* pVertex)
	{
		HXCOLOR col;
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
				col = HXCOLOR(0, 0, 0);
			}
		}
		else if (lightType == LIGHT_AMBIENT)
		{
			col = color * pVertex->color;
		}
		return col;
	}
}