#include "..\include\HXQuaternionOld.h"

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

	int Sign(double param)
	{
		if (param > 0)
		{
			return 1;
		}
		else if (param == 0)
		{
			return 0;
		}
		else// if (param < 0)
		{
			return -1;
		}
	}

	HXVector3D HXQuaternionOld::ToEulerDegree()
	{
		HXVector3D euler;
		const double Epsilon = 0.0009765625f;
		const double Threshold = 0.5f - Epsilon;

		double TEST = w*y - x*z;

		if (TEST < -Threshold || TEST > Threshold) // ÆæÒì×ËÌ¬,¸©Ñö½ÇÎª¡À90¡ã
		{
			int sign = Sign(TEST);

			euler.z = -2 * sign * (double)atan2(x, w); // yaw

			euler.y = sign * (PI / 2.0); // pitch

			euler.x = 0; // roll

		}
		else
		{
			euler.x = atan2(2 * (y*z + w*x), w*w - x*x - y*y + z*z);
			euler.y = asin(-2 * (x*z - w*y));
			euler.z = atan2(2 * (x*y + w*z), w*w + x*x - y*y - z*z);
		}
		euler.x = Radian_TO_Degree(euler.x);
		euler.y = Radian_TO_Degree(euler.y);
		euler.z = Radian_TO_Degree(euler.z);
		return euler;
	}

	HXVector3D HXQuaternionOld::ToEulerDegree1()
	{
		double heading;
		double attitude;
		double bank;

		double sqw = w*w;
		double sqx = x*x;
		double sqy = y*y;
		double sqz = z*z;
		double unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
		double test = x*y + z*w;
		if (test > 0.499*unit) { // singularity at north pole
			heading = 2 * atan2(x, w);
			attitude = PI / 2;
			bank = 0;
			HXVector3D euler;
			euler.x = Radian_TO_Degree(heading);
			euler.y = Radian_TO_Degree(attitude);
			euler.z = Radian_TO_Degree(bank);
			return euler;
		}
		if (test < -0.499*unit) { // singularity at south pole
			heading = -2 * atan2(x, w);
			attitude = -PI / 2;
			bank = 0;
			HXVector3D euler;
			euler.x = Radian_TO_Degree(heading);
			euler.y = Radian_TO_Degree(attitude);
			euler.z = Radian_TO_Degree(bank);
			return euler;
		}
		heading = atan2(2 * y*w - 2 * x*z, sqx - sqy - sqz + sqw);
		attitude = asin(2 * test / unit);
		bank = atan2(2 * x*w - 2 * y*z, -sqx + sqy - sqz + sqw);
		
		HXVector3D euler;
		euler.x = Radian_TO_Degree(heading);
		euler.y = Radian_TO_Degree(attitude);
		euler.z = Radian_TO_Degree(bank);
		return euler;
	}



	void threeaxisrot(double r11, double r12, double r21, double r31, double r32, double res[]) {
		res[0] = atan2(r31, r32);
		res[1] = asin(r21);
		res[2] = atan2(r11, r12);
	}

	void HXQuaternionOld::quaternion2Euler(double res[])
	{
		//yzx
		threeaxisrot(-2 * (x*z - w*y),
			w*w + x*x - y*y - z*z,
			2 * (x*y + w*z),
			-2 * (y*z - w*x),
			w*w - x*x + y*y - z*z,
			res);

		//xzy
		//threeaxisrot(2 * (y*z + w*x),
		//	w*w - x*x + y*y - z*z,
		//	-2 * (x*y - w*z),
		//	2 * (x*z + w*y),
		//	w*w + x*x - y*y - z*z,
		//	res);

		threeaxisrot(2 * (x*z + w*y),
			w*w - x*x - y*y + z*z,
			-2 * (y*z - w*x),
			2 * (x*y + w*z),
			w*w - x*x + y*y - z*z,
			res);
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
}
