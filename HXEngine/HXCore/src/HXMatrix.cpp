#include "..\include\HXMatrix.h"
#include "HXMath.h"
#include "MathUtils3D.h"

namespace HX3D
{
	HXMatrix44 HXMatrix44::IDENTITY(1, 0, 0, 0,
									0, 1, 0, 0,
									0, 0, 1, 0,
									0, 0, 0, 1);

	HXMatrix44 HXMatrix44::CreateAffineTransformation(const HXVector3D& trans, const HXQuaternionS& rot, const HXVector3D& scale)
	{
		float x = rot.x, y = rot.y, z = rot.z, w = rot.w, x2 = x + x, y2 = y + y, z2 = z + z;
		float xx = x * x2, xy = x * y2, xz = x * z2, yy = y * y2, yz = y * z2, zz = z * z2;
		float wx = w * x2, wy = w * y2, wz = w * z2, sx = scale.x, sy = scale.y, sz = scale.z;

		HXMatrix44 tempMatrix44;
		tempMatrix44.m[0][0] = (1 - (yy + zz)) * sx;
		tempMatrix44.m[0][1] = (xy + wz) * sx;
		tempMatrix44.m[0][2] = (xz - wy) * sx;
		tempMatrix44.m[0][3] = 0;
		tempMatrix44.m[1][0] = (xy - wz) * sy;
		tempMatrix44.m[1][1] = (1 - (xx + zz)) * sy;
		tempMatrix44.m[1][2] = (yz + wx) * sy;
		tempMatrix44.m[1][3] = 0;
		tempMatrix44.m[2][0] = (xz + wy) * sz;
		tempMatrix44.m[2][1] = (yz - wx) * sz;
		tempMatrix44.m[2][2] = (1 - (xx + yy)) * sz;
		tempMatrix44.m[2][3] = 0;
		tempMatrix44.m[3][0] = trans.x;
		tempMatrix44.m[3][1] = trans.y;
		tempMatrix44.m[3][2] = trans.z;
		tempMatrix44.m[3][3] = 1;

		return tempMatrix44;
	}

	bool HXMatrix44::DecomposeTransRotScale(HXVector3D& translation, HXQuaternionS& rotation, HXVector3D& scale)
	{
		//HXMatrix44& rotationMatrix = tempMatrix44;
		HXMatrix44 rotationMatrix;
		if (DecomposeTransRotMatScale(translation, rotationMatrix, scale)) {
			HXQuaternionS::CreateFromMatrix4x4(rotationMatrix, rotation);
			return true;
		}
		else {
			rotation.Identity();
			return false;
		}
	}

	bool HXMatrix44::DecomposeTransRotMatScale(HXVector3D& translation, HXMatrix44& rotationMatrix, HXVector3D& scale)
	{
		//Get the translation. 
		translation.x = m[3][0];
		translation.y = m[3][1];
		translation.z = m[3][2];

		//Scaling is the length of the rows. 
		float m11 = m[0][0], m12 = m[0][1], m13 = m[0][2];
		float m21 = m[1][0], m22 = m[1][1], m23 = m[1][2];
		float m31 = m[2][0], m32 = m[2][1], m33 = m[2][2];

		float sX = scale.x = sqrt((m11 * m11) + (m12 * m12) + (m13 * m13));
		float sY = scale.y = sqrt((m21 * m21) + (m22 * m22) + (m23 * m23));
		float sZ = scale.z = sqrt((m31 * m31) + (m32 * m32) + (m33 * m33));

		//If any of the scaling factors are zero, than the rotation matrix can not exist. 
		if (MathUtils3D::isZero(sX) || MathUtils3D::isZero(sY) || MathUtils3D::isZero(sZ))
		{
			rotationMatrix.m[0][1] = rotationMatrix.m[0][2] = rotationMatrix.m[0][3] = rotationMatrix.m[1][0] = rotationMatrix.m[1][2] = rotationMatrix.m[1][3] = rotationMatrix.m[2][0] = rotationMatrix.m[2][1] = rotationMatrix.m[2][3] = rotationMatrix.m[3][0] = rotationMatrix.m[3][1] = rotationMatrix.m[3][2] = 0;
			rotationMatrix.m[0][0] = rotationMatrix.m[1][1] = rotationMatrix.m[2][2] = rotationMatrix.m[3][3] = 1;
			return false;
		}

		// Calculate an perfect orthonormal matrix (no reflections)
		//HXVector3D& at = tempVector0;
		HXVector3D at;
		at.x = m31 / sZ;
		at.y = m32 / sZ;
		at.z = m33 / sZ;
		//HXVector3D& tempRight = tempVector1;
		HXVector3D tempRight;
		tempRight.x = m11 / sX;
		tempRight.y = m12 / sX;
		tempRight.z = m13 / sX;
		//HXVector3D& up = tempVector2;
		HXVector3D up;
		//HXVector3D::cross(at, tempRight, up);
		up = at.crossProduct(tempRight);
		//HXVector3D& right = tempVector1;
		HXVector3D right;
		//HXVector3D::cross(up, at, right);
		right = up.crossProduct(at);

		rotationMatrix.m[0][3] = rotationMatrix.m[1][3] = rotationMatrix.m[2][3] = rotationMatrix.m[3][0] = rotationMatrix.m[3][1] = rotationMatrix.m[3][2] = 0;
		rotationMatrix.m[3][3] = 1;
		rotationMatrix.m[0][0] = right.x;
		rotationMatrix.m[0][1] = right.y;
		rotationMatrix.m[0][2] = right.z;

		rotationMatrix.m[1][0] = up.x;
		rotationMatrix.m[1][1] = up.y;
		rotationMatrix.m[1][2] = up.z;

		rotationMatrix.m[2][0] = at.x;
		rotationMatrix.m[2][1] = at.y;
		rotationMatrix.m[2][2] = at.z;

		// In case of reflexions//TODO:是否不用计算dot后的值即为结果
		((rotationMatrix.m[0][0] * m11 + rotationMatrix.m[0][1] * m12 + rotationMatrix.m[0][2] * m13)/*Vector3.dot(right,Right)*/ < 0.0) && (scale.x = -sX);
		((rotationMatrix.m[1][0] * m21 + rotationMatrix.m[1][1] * m22 + rotationMatrix.m[1][2] * m23)/* Vector3.dot(up, Up)*/ < 0.0) && (scale.y = -sY);
		((rotationMatrix.m[2][0] * m31 + rotationMatrix.m[2][1] * m32 + rotationMatrix.m[2][2] * m33)/*Vector3.dot(at, Backward)*/ < 0.0) && (scale.z = -sZ);

		return true;
	}

	void HXMatrix44::createRotationX(float rad, HXMatrix44& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		//var oe : Float32Array = out.elements;
		float s = sin(rad), c = cos(rad);

		out.m[0][1] = out.m[0][2] = out.m[0][3] = out.m[1][0] = out.m[1][3] = out.m[2][0] = out.m[2][3] = out.m[3][0] = out.m[3][1] = out.m[3][2] = 0;
		out.m[0][0] = out.m[3][3] = 1;
		out.m[1][1] = out.m[2][2] = c;
		out.m[1][2] = s;
		out.m[2][1] = -s;
	}

	void HXMatrix44::createRotationY(float rad, HXMatrix44& out)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		//var oe : Float32Array = out.elements;
		float s = sin(rad), c = cos(rad);

		out.m[0][1] = out.m[0][3] = out.m[1][0] = out.m[1][2] = out.m[1][3] = out.m[2][1] = out.m[2][3] = out.m[3][0] = out.m[3][1] = out.m[3][2] = 0;
		out.m[1][1] = out.m[3][3] = 1;
		out.m[0][0] = out.m[2][2] = c;
		out.m[0][2] = -s;
		out.m[2][0] = s;
	}
}