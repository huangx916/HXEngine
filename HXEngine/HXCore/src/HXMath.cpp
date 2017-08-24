#include "..\include\HXMath.h"

namespace HX3D
{
	HXMatrix44 GetTranslateMatrix44(float tx, float ty, float tz)
	{
		return HXMatrix44(	1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							tx, ty, tz, 1);
	}

	HXMatrix44 GetScaleMatrix44(float sx, float sy, float sz)
	{
		return HXMatrix44(	sx, 0, 0, 0,
							0, sy, 0, 0,
							0, 0, sz, 0,
							0, 0, 0, 1);
	}

	HXMatrix44 GetRotateMatrix44X(float fDegree)
	{
		float fRadian = Degree_TO_Radian(fDegree);
		float sinA = sin(fRadian);
		float cosA = cos(fRadian);

		return HXMatrix44(	1, 0, 0, 0,
							0, cosA, sinA, 0,
							0, -sinA, cosA, 0,
							0, 0, 0, 1);
	}

	HXMatrix44 GetRotateMatrix44Y(float fDegree)
	{
		float fRadian = Degree_TO_Radian(fDegree);
		float sinA = sin(fRadian);
		float cosA = cos(fRadian);

		return HXMatrix44(	cosA, 0, -sinA, 0,
							0, 1, 0, 0,
							sinA, 0, cosA, 0,
							0, 0, 0, 1);
	}

	HXMatrix44 GetRotateMatrix44Z(float fDegree)
	{
		float fRadian = Degree_TO_Radian(fDegree);
		float sinA = sin(fRadian);
		float cosA = cos(fRadian);

		return HXMatrix44(	cosA, sinA, 0, 0,
							-sinA, cosA, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);
	}

	HXMatrix44 GetRotateMatrix44(const HXVector4D& axis, float fDegree)
	{
		float fRadian = Degree_TO_Radian(fDegree);
		float sinA = sin(fRadian);
		float cosA = cos(fRadian);
		float oneCosA = 1 - cosA;

		return HXMatrix44(axis.x * axis.x * oneCosA + cosA, axis.x * axis.y * oneCosA + axis.x * sinA, axis.x * axis.z * oneCosA - axis.y * sinA, 0,
			axis.x * axis.y * oneCosA - axis.z * sinA, axis.y * axis.y * oneCosA + cosA, axis.y * axis.z * oneCosA + axis.x * sinA, 0,
			axis.x * axis.z * oneCosA + axis.y * sinA, axis.y * axis.z * oneCosA - axis.x * sinA, axis.z * axis.z * oneCosA + cosA, 0,
			0,0,0,1);
	}

	HXVector3D GetVector3DMulMatrix44(const HXVector3D& vec, const HXMatrix44& mat)
	{
		float x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + 1 * mat.m[3][0];
		float y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + 1 * mat.m[3][1];
		float z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + 1 * mat.m[3][2];

		return HXVector3D(x, y, z);
	}

	HXVector4D GetVector4DMulMatrix44(const HXVector4D& vec, const HXMatrix44& mat)
	{
		float x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0];
		float y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1];
		float z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2];
		float w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + vec.w * mat.m[3][3];

		return HXVector4D(x, y, z, w);
	}
}
