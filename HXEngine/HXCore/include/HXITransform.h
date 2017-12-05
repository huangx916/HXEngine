#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMatrix.h"

namespace HX3D
{
	class HXITransform
	{
	public:
		HXITransform();
		virtual ~HXITransform();

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix) = 0;
		virtual void CaculateModelMatrix() = 0;

		HXVector3D mPostion;
		HXVector3D mEulerDegree;
		HXVector3D mScale;

		HXMatrix44 mCurModelMatrix;
	};
}