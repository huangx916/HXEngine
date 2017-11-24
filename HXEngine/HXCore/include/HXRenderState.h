#pragma once
#include "HXCommon.h"
//#include "HXGDITextureBMP.h"

namespace HX3D
{
	class HXMaterial;
	class HXGDITextureBMP;
	struct HXMaterialInfo;
	class HXRenderState
	{
	public:
		HXRenderState();
		~HXRenderState();

		static void Reset();

		//static HXMaterial* GetMaterial();
		//static void SetMaterial(std::string materialname);

		//static HXMaterial* m_pMaterial;

		static void SetMatInfoAndTexture(std::string strMatInfoFile);

		static HXMaterialInfo* m_pMatInfo;
		static HXGDITextureBMP* m_pTex;
	};
}
