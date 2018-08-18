#include "..\include\HXQuaternionOld.h"
#include "HXMatrix.h"
#include "HXMath.h"

namespace HX3D
{
	const HXQuaternionOld HXQuaternionOld::IDENTITY(0,0,0,1); //Ðý×ª0¶È

	HXQuaternionOld::HXQuaternionOld() :x(0),y(0),z(0),w(1)
	{
	}

	HXQuaternionOld::HXQuaternionOld(float fX, float fY, float fZ, float fW)
	{
		x = fX;
		y = fY;
		z = fZ;
		w = fW;
	}

	HXQuaternionOld::~HXQuaternionOld()
	{
	}

	HXQuaternionOld HXQuaternionOld::Inverse() const
	{
		float fNorm = x*x + y*y + z*z + w*w;
		float fInvNorm = 1.0f / fNorm;
		return HXQuaternionOld(-x*fInvNorm,-y*fInvNorm,-z*fInvNorm,w*fInvNorm);
	}

	void HXQuaternionOld::Normalize()
	{
		float norm = std::sqrt(x*x + y*y + z*z + w*w);
		x /= norm;
		y /= norm;
		z /= norm;
		w /= norm;
	}

	void HXQuaternionOld::FromEulerDegree(float fX, float fY, float fZ)
	{
		float X = Degree_TO_Radian(fX);
		float Y = Degree_TO_Radian(fY);
		float Z = Degree_TO_Radian(fZ);

		x = sin(Y / 2)*sin(Z / 2)*cos(X / 2) + cos(Y / 2)*cos(Z / 2)*sin(X / 2);
		y = sin(Y / 2)*cos(Z / 2)*cos(X / 2) + cos(Y / 2)*sin(Z / 2)*sin(X / 2);
		z = cos(Y / 2)*sin(Z / 2)*cos(X / 2) - sin(Y / 2)*cos(Z / 2)*sin(X / 2);
		w = cos(Y / 2)*cos(Z / 2)*cos(X / 2) - sin(Y / 2)*sin(Z / 2)*sin(X / 2);
	}

	void HXQuaternionOld::FromAngleAxis(float fDegree, HXVector3D axis)
	{
		// assert:  axis is unit length
		float fHalfDegree = fDegree * 0.5f;
		float fHalfRadian = Degree_TO_Radian(fHalfDegree);
		float fSin = sin(fHalfRadian);
		float fCos = cos(fHalfRadian);
		x = fSin * axis.x;
		y = fSin * axis.y;
		z = fSin * axis.z;
		w = fCos;
	}

	HXVector3D HXQuaternionOld::ToEulerDegree()
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		//Vector3.transformQuat(Vector3.ForwardRH, this, TEMPVector31/*forwarldRH*/);
		HXVector3D TEMPVector31 = Transform(HXVector3D(0,0,-1));

		//Vector3.transformQuat(Vector3.Up, this, TEMPVector32/*up*/);
		HXVector3D TEMPVector32 = Transform(HXVector3D(0,1,0));
		HXVector3D upe = TEMPVector32;

		//angleTo(Vector3.ZERO, TEMPVector31, TEMPVector33/*angle*/);

		HXVector3D from = HXVector3D(0,0,0);
		HXVector3D location = TEMPVector31;

		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		//Vector3.subtract(location, from, TEMPVector30);
		HXVector3D TEMPVector30 = location - from;
		//Vector3.normalize(TEMPVector30, TEMPVector30);
		TEMPVector30.normalize();
		//angle.elements[0] = asin(TEMPVector30.y);
		//angle.elements[1] = arcTanAngle(-TEMPVector30.z, -TEMPVector30.x);
		HXVector3D angle;
		angle.x = asin(TEMPVector30.y);
		angle.y = arcTanAngle(-TEMPVector30.z, -TEMPVector30.x);
		//angle.y = atan2(-TEMPVector30.x, -TEMPVector30.z);
		HXVector3D TEMPVector33 = angle;


		HXVector3D anglee = TEMPVector33;

		if (anglee.x == PI / 2) {
			anglee.y = arcTanAngle(upe.z, upe.x);
			//anglee.y = atan2(upe.x, upe.z);
			anglee.z = 0;
		}
		else if (anglee.x == -PI / 2) {
			anglee.y = arcTanAngle(-upe.z, -upe.x);
			//anglee.y = atan2(-upe.x, -upe.z);
			anglee.z = 0;
		}
		else {
			HXMatrix44 TEMPMatrix0;
			HXMatrix44 TEMPMatrix1;
			HXMatrix44::createRotationY(-anglee.y, TEMPMatrix0);
			HXMatrix44::createRotationX(-anglee.x, TEMPMatrix1);

			//Vector3.transformCoordinate(TEMPVector32, TEMPMatrix0, TEMPVector32);
			TEMPVector32 = GetVector3DMulMatrix44(TEMPVector32, TEMPMatrix0);
			//Vector3.transformCoordinate(TEMPVector32, TEMPMatrix1, TEMPVector32);
			TEMPVector32 = GetVector3DMulMatrix44(TEMPVector32, TEMPMatrix1);
			upe = TEMPVector32;
			anglee.z = arcTanAngle(upe.y, -upe.x);
			//anglee.z = atan2(-upe.x, upe.y);
		}

		// Special cases.
		if (anglee.y <= -PI)
			anglee.y = PI;
		if (anglee.z <= -PI)
			anglee.z = PI;

		if (anglee.y >= PI && anglee.z >= PI) {
			anglee.y = 0;
			anglee.z = 0;
			anglee.x = PI - anglee.x;
		}

		/*HXVector3D out;
		out.x = anglee.y;
		out.y = anglee.x;
		out.z = anglee.z;
		return out;*/

		anglee.x = Radian_TO_Degree(anglee.x);
		anglee.y = Radian_TO_Degree(anglee.y);
		anglee.z = Radian_TO_Degree(anglee.z);

		return anglee;
	}

	float HXQuaternionOld::arcTanAngle(float x, float y)
	{
		/*[DISABLE-ADD-VARIABLE-DEFAULT-VALUE]*/
		if (x == 0) {
			if (y == 1)
				return PI / 2;
			return -PI / 2;
		}
		if (x > 0)
			return atan(y / x);
		if (x < 0) {
			if (y > 0)
				return atan(y / x) + PI;
			return atan(y / x) - PI;
		}
		return 0;
	}

	HXQuaternionOld HXQuaternionOld::operator*(const HXQuaternionOld& rhs) const
	{
		HXQuaternionOld q;
		q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
		q.y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
		q.z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
		q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
		return q;
	}

	HXVector3D HXQuaternionOld::Transform(const HXVector3D& vSrc)
	{
		HXQuaternionOld p(vSrc.x, vSrc.y, vSrc.z, 0);
		HXQuaternionOld q(x, y, z, w);
		HXQuaternionOld invq = q.Inverse();
		HXQuaternionOld destP = q*p*invq;
		return HXVector3D(destP.x, destP.y, destP.z);
	}

	void HXQuaternionOld::CreateFromMatrix4x4(const HXMatrix44& mat, HXQuaternionOld& out)
	{
		float _sqrt;
		float half;
		float scale = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];

		if (scale > 0.0) {
			_sqrt = sqrt(scale + 1.0);
			out.w = _sqrt * 0.5;
			_sqrt = 0.5 / _sqrt;

			out.x = (mat.m[1][2] - mat.m[2][1]) * _sqrt;
			out.y = (mat.m[2][0] - mat.m[0][2]) * _sqrt;
			out.z = (mat.m[0][1] - mat.m[1][0]) * _sqrt;
		}
		else if ((mat.m[0][0] >= mat.m[1][1]) && (mat.m[0][0] >= mat.m[2][2])) {
			_sqrt = sqrt(1.0 + mat.m[0][0] - mat.m[1][1] - mat.m[2][2]);
			half = 0.5 / _sqrt;

			out.x = 0.5 * _sqrt;
			out.y = (mat.m[0][1] + mat.m[1][0]) * half;
			out.z = (mat.m[0][2] + mat.m[2][0]) * half;
			out.w = (mat.m[1][2] - mat.m[2][1]) * half;
		}
		else if (mat.m[1][1] > mat.m[2][2]) {
			_sqrt = sqrt(1.0 + mat.m[1][1] - mat.m[0][0] - mat.m[2][2]);
			half = 0.5 / _sqrt;

			out.x = (mat.m[1][0] + mat.m[0][1]) * half;
			out.y = 0.5 * _sqrt;
			out.z = (mat.m[2][1] + mat.m[1][2]) * half;
			out.w = (mat.m[2][0] - mat.m[0][2]) * half;
		}
		else {
			_sqrt = sqrt(1.0 + mat.m[2][2] - mat.m[0][0] - mat.m[1][1]);
			half = 0.5 / _sqrt;

			out.x = (mat.m[2][0] + mat.m[0][2]) * half;
			out.y = (mat.m[2][1] + mat.m[1][2]) * half;
			out.z = 0.5 * _sqrt;
			out.w = (mat.m[0][1] - mat.m[1][0]) * half;
		}
	}

	void HXQuaternionOld::Identity()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
}
