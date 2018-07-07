#pragma once
#include "HXCommon.h"
#include "HXLoadConfigMat.h"

namespace HX3D
{
	class HXMaterial
	{
	public:
		HXMaterial();
		void SetMaterialInfo(HXMaterialInfo* pMatInfo);
		virtual ~HXMaterial();

		HXMaterialInfo* mMatInfo;
	};
}


