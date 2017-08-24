#include "HXPlane.h"

namespace HX3D
{
	HXPlane3D::HXPlane3D(const HXVector4D& p, const HXVector4D& n)
	{
		point = p;
		normal = n;
	}

	HXPlane3D& HXPlane3D::operator=(const HXPlane3D& rhs)
	{
		point = rhs.point;
		normal = rhs.normal;
		return *this;
	}
}