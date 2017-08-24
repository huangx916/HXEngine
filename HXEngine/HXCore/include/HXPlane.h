#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	struct HXPlane3D 
	{
		HXVector4D point;	// 面上一点
		HXVector4D normal;	// 面上法线

		HXPlane3D() {}
		HXPlane3D(const HXVector4D& p, const HXVector4D& n);
		HXPlane3D& operator=(const HXPlane3D& rhs);
	};
}