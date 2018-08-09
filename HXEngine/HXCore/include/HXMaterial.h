#pragma once
#include "HXCommon.h"
#include "HXLoadConfigMat.h"

namespace HX3D
{
	class HXRenderable;
	class HXICamera;
	class HXMaterial
	{
	public:
		HXMaterial();
		void SetMaterialInfo(HXMaterialInfo* pMatInfo);
		virtual ~HXMaterial();

		virtual void SetMaterialRenderStateAllRenderable(HXICamera* curCamera) {};
		virtual void SetMaterialRenderStateEachRenderable(HXRenderable* renderable) {};
		virtual void SetShadowMapMaterialRenderStateAllRenderable() {};
		virtual void SetShadowMapMaterialRenderStateEachRenderable(HXRenderable* renderable) {};

		HXMaterialInfo* mMatInfo;
	};
}


