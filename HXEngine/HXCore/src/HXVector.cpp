#include "..\include\HXVector.h"

namespace HX3D
{
	HXVector2D HXVector2D::ZERO(0,0);
	HXVector2D HXVector2D::UNIT_X(1, 0);
	HXVector2D HXVector2D::UNIT_Y(0, 1);

	HXVector3D HXVector3D::ZERO(0, 0, 0);
	HXVector3D HXVector3D::UNIT_X(1, 0, 0);
	HXVector3D HXVector3D::UNIT_Y(0, 1, 0);
	HXVector3D HXVector3D::UNIT_Z(0, 0, 1);

	HXVector4D HXVector4D::ZERO(0, 0, 0);
	HXVector4D HXVector4D::UNIT_X(1, 0, 0);
	HXVector4D HXVector4D::UNIT_Y(0, 1, 0);
	HXVector4D HXVector4D::UNIT_Z(0, 0, 1);
}