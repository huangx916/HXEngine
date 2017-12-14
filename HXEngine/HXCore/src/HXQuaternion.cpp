#include "..\include\HXQuaternion.h"

namespace HX3D
{
	const HXQuaternion HXQuaternion::IDENTITY(0,0,0,1); //Ðý×ª0¶È

	HXQuaternion::HXQuaternion() :x(0),y(0),z(0),w(1)
	{
	}

	HXQuaternion::HXQuaternion(float fX, float fY, float fZ, float fW)
	{
		x = fX;
		y = fY;
		z = fZ;
		w = fW;
	}

	HXQuaternion::~HXQuaternion()
	{
	}

	HXQuaternion HXQuaternion::Inverse() const
	{
		float fNorm = x*x + y*y + z*z + w*w;
		float fInvNorm = 1.0f / fNorm;
		return HXQuaternion(-x*fInvNorm,-y*fInvNorm,-z*fInvNorm,w*fInvNorm);
	}

	void HXQuaternion::FromEulerDegree(float fX, float fY, float fZ)
	{
		float X = Degree_TO_Radian(fX);
		float Y = Degree_TO_Radian(fY);
		float Z = Degree_TO_Radian(fZ);

		x = sin(Y / 2)*sin(Z / 2)*cos(X / 2) + cos(Y / 2)*cos(Z / 2)*sin(X / 2);
		y = sin(Y / 2)*cos(Z / 2)*cos(X / 2) + cos(Y / 2)*sin(Z / 2)*sin(X / 2);
		z = cos(Y / 2)*sin(Z / 2)*cos(X / 2) - sin(Y / 2)*cos(Z / 2)*sin(X / 2);
		w = cos(Y / 2)*cos(Z / 2)*cos(X / 2) - sin(Y / 2)*sin(Z / 2)*sin(X / 2);
	}

	void HXQuaternion::FromAngleAxis(float fDegree, HXVector3D axis)
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

	HXQuaternion HXQuaternion::operator*(const HXQuaternion& rhs) const
	{
		HXQuaternion q;
		q.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
		q.y = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
		q.z = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
		q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
		return q;
	}

	HXVector3D HXQuaternion::Transform(const HXVector3D& vSrc)
	{
		HXQuaternion p(vSrc.x, vSrc.y, vSrc.z, 0);
		HXQuaternion q(x, y, z, w);
		HXQuaternion invq = q.Inverse();
		HXQuaternion destP = q*p*invq;
		return HXVector3D(destP.x, destP.y, destP.z);
	}
}
