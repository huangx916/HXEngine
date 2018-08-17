#include "..\include\HXMatrix.h"
#include "HXMath.h"

namespace HX3D
{
	HXMatrix44 HXMatrix44::IDENTITY(1, 0, 0, 0,
									0, 1, 0, 0,
									0, 0, 1, 0,
									0, 0, 0, 1);

	//HXMatrix44 HXMatrix44::CreateAffineTransformation(const HXVector3D& trans, const HXQuaternionOld& rot, const HXVector3D& scale)
	//{
	//	float x = rot.x, y = rot.y, z = rot.z, w = rot.w, x2 = x + x, y2 = y + y, z2 = z + z;
	//	float xx = x * x2, xy = x * y2, xz = x * z2, yy = y * y2, yz = y * z2, zz = z * z2;
	//	float wx = w * x2, wy = w * y2, wz = w * z2, sx = scale.x, sy = scale.y, sz = scale.z;

	//	// TODO: 使用提前new的matrix避免值拷贝开销
	//	HXMatrix44 mat;
	//	mat.m[0][0] = (1 - (yy + zz)) * sx;
	//	mat.m[0][1] = (xy + wz) * sx;
	//	mat.m[0][2] = (xz - wy) * sx;
	//	mat.m[0][3] = 0;
	//	mat.m[1][0] = (xy - wz) * sy;
	//	mat.m[1][1] = (1 - (xx + zz)) * sy;
	//	mat.m[1][2] = (yz + wx) * sy;
	//	mat.m[1][3] = 0;
	//	mat.m[2][0] = (xz + wy) * sz;
	//	mat.m[2][1] = (yz - wx) * sz;
	//	mat.m[2][2] = (1 - (xx + yy)) * sz;
	//	mat.m[2][3] = 0;
	//	mat.m[3][0] = trans.x;
	//	mat.m[3][1] = trans.y;
	//	mat.m[3][2] = trans.z;
	//	mat.m[3][3] = 1;

	//	return mat;
	//}

	//bool HXMatrix44::DecomposeTransRotScale(HXVector3D& translation, HXQuaternionOld& rotation, HXVector3D& scale)
	//{

	//}

	//bool HXMatrix44::DecomposeTransRotMatScale(HXVector3D& translation, HXMatrix44& rotationMatrix, HXVector3D& scale)
	//{
	//	//Get the translation. 
	//	translation.x = m[3][0];
	//	translation.y = m[3][1];
	//	translation.z = m[3][2];

	//	//Scaling is the length of the rows. 
	//	float m11 = m[0][0], m12 = m[0][1], m13 = m[0][2];
	//	float m21 = m[1][0], m22 = m[1][1], m23 = m[1][2];
	//	float m31 = m[2][0], m32 = m[2][1], m33 = m[2][2];

	//	float sX = scale.x = sqrt((m11 * m11) + (m12 * m12) + (m13 * m13));
	//	float sY = scale.y = sqrt((m21 * m21) + (m22 * m22) + (m23 * m23));
	//	float sZ = scale.z = sqrt((m31 * m31) + (m32 * m32) + (m33 * m33));

	//	//If any of the scaling factors are zero, than the rotation matrix can not exist. 
	//	if (IsZero(sX) || IsZero(sY) || IsZero(sZ))
	//	{

	//	}
	//}
}