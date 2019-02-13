#pragma once
#include "HXCommon.h"

namespace HX3D
{
	struct HXColor
	{
		// unsigned char r, g, b, a;
		// 光栅化线性插值产生step里的color rgba分量可能是负值
		float r, g, b, a;

		HXColor() :r(255), g(255), b(255), a(255) {}

		/*HXColor(int color, unsigned char alpha = 255)
		{
		r = (unsigned char)((color & 0xff0000) >> 16);
		g = (unsigned char)((color & 0x00ff00) >> 8);
		b = (unsigned char)(color & 0x0000ff);
		a = alpha;
		}*/

		HXColor(float fr, float fg, float fb, float fa = 255) :
			r(fr), g(fg), b(fb), a(fa) {}

		/*inline int ToInt() const
		{
		return HXColor_TO_24BIT(r,g,b);
		}*/

		inline HXColor operator*(const HXColor& rhs) const
		{
			// r >> 8  相当于  r / 255
			return HXColor(r * (rhs.r / 255), g * (rhs.g / 255), b * (rhs.b / 255), a * (rhs.a / 255));
		}

		inline HXColor operator*(float rhs) const
		{
			float fR = r * rhs;
			float fG = g * rhs;
			float fB = b * rhs;
			float fA = a * rhs;
			if (fR > 255)
			{
				fR = 255;
			}
			if (fR < 0)
			{
				fR = 0;
			}
			if (fG > 255)
			{
				fG = 255;
			}
			if (fG < 0)
			{
				fG = 0;
			}
			if (fB > 255)
			{
				fB = 255;
			}
			if (fB < 0)
			{
				fB = 0;
			}
			if (fA > 255)
			{
				fA = 255;
			}
			if (fA < 0)
			{
				fA = 0;
			}
			return HXColor(fR, fG, fB, fA);
		}

		inline HXColor operator/(float rhs) const
		{
			return HXColor(r / rhs, g / rhs, b / rhs, a / rhs);
		}

		inline HXColor operator-(const HXColor& rhs) const
		{
			float fR = r - rhs.r;
			float fG = g - rhs.g;
			float fB = b - rhs.b;
			float fA = a - rhs.a;
			return HXColor(fR, fG, fB, fA);
		}

		inline HXColor& operator+=(const HXColor& rhs)
		{
			float fR = r + rhs.r;
			float fG = g + rhs.g;
			float fB = b + rhs.b;
			float fA = a + rhs.a;
			if (fR > 255)
			{
				fR = 255;
			}
			if (fG > 255)
			{
				fG = 255;
			}
			if (fB > 255)
			{
				fB = 255;
			}
			if (fA > 255)
			{
				fA = 255;
			}

			r = fR;
			g = fG;
			b = fB;
			a = fA;

			return *this;
		}
	};
}