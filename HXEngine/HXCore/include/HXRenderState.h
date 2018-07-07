#pragma once
#include "HXCommon.h"
//#include "HXGDITextureBMP.h"

namespace HX3D
{
	class HXMaterial;
	class HXGDITextureBMP;
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

		static HXMaterial* m_pMat;
		static HXGDITextureBMP* m_pTex;
	};
}
