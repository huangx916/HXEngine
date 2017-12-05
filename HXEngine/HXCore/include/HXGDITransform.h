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

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix);
		virtual void CaculateModelMatrix();
	};
}

