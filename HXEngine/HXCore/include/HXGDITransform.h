#pragma once
#include "HXCommon.h"
#include "HXITransform.h"

namespace HX3D
{
	class HXGDITransform : public HXITransform
	{
	public:
		HXGDITransform();
		~HXGDITransform();

		virtual const HXVector3D& GetGlobalPosition();
		virtual HXVector3D GetGlobalRotation();
		virtual HXVector3D GetGlobalScale();

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix);
		virtual void CaculateModelMatrix();
	};
}

