#pragma once
#include <fbxsdk.h>
#include "HXMaterial.h"

namespace HX3D
{
	enum MAT_SHADING_MODEL
	{
		Lambert,
		Phong
	};
	class HXMaterialFBX : public HXMaterial
	{
	public:
		HXMaterialFBX();
		~HXMaterialFBX();

		bool Initialize(const FbxSurfaceMaterial* pMaterial);

		HXCOLOR ambient;
		HXCOLOR diffuse;
		HXCOLOR specular;
		HXCOLOR emissive;
		float transparencyfactor;
		float shininess;
		float reflectionfactor;
		MAT_SHADING_MODEL shadingModel;
	};
}