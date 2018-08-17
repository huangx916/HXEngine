#include "..\include\HXVector3.h"

namespace HX3D
{
	HXVector3::HXVector3()
	{
	}

	HXVector3::~HXVector3()
	{
	}

	void HXVector3::normalize(const HXVector3& s, HXVector3& out)
	{
		const float* se = s.elements;
		float* oe = out.elements;
		float x = se[0], y = se[1], z = se[2];
		float len = x * x + y * y + z * z;
		if (len > 0) {
			len = 1 / sqrt(len);
			oe[0] = se[0] * len;
			oe[1] = se[1] * len;
			oe[2] = se[2] * len;
		}
	}

	void HXVector3::subtract(const HXVector3& a, const HXVector3& b, HXVector3& o)
	{
		float* oe = o.elements;
		const float* ae = a.elements;
		const float* be = b.elements;
		oe[0] = ae[0] - be[0];
		oe[1] = ae[1] - be[1];
		oe[2] = ae[2] - be[2];
	}

	void HXVector3::cross(const HXVector3& a, const  HXVector3& b, HXVector3& o)
	{
		const float* ae = a.elements;
		const float* be = b.elements;
		float* oe = o.elements;
		float ax = ae[0], ay = ae[1], az = ae[2], bx = be[0], by = be[1], bz = be[2];
		oe[0] = ay * bz - az * by;
		oe[1] = az * bx - ax * bz;
		oe[2] = ax * by - ay * bx;
	}

	float HXVector3::dot(const HXVector3& a, const HXVector3& b)
	{
		const float* ae = a.elements;
		const float* be = b.elements;
		float r = (ae[0] * be[0]) + (ae[1] * be[1]) + (ae[2] * be[2]);
		return r;
	}













}