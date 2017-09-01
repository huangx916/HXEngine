#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXMaterial;

	class HXRenderState
	{
	public:
		HXRenderState();
		~HXRenderState();

		static void Reset();

		static HXMaterial* GetMaterial();
		static void SetMaterial(std::string materialname);

		static HXMaterial* m_pMaterial;
	};
}
