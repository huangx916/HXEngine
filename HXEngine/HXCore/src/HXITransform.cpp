#include "..\include\HXITransform.h"

namespace HX3D
{
	HXITransform::HXITransform()
	{
		mPostion = HXVector3D(0,0,0);
		mEulerDegree = HXVector3D(0,0,0);
		mScale = HXVector3D(1,1,1);
	}

	HXITransform::~HXITransform()
	{
	}
}