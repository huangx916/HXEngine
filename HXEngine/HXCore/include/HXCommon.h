#pragma once

#include <string>
#include <vector>
#include <list>
//#include <deque>
#include <iostream>
#include "HX3DHeader.h"

namespace HX3D
{
	// 窗口大小
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	// 数学常量
	#define PI			3.141592654f
	#define PI2			(PI*2.0f)
	#define PI_DIV_2	(PI*0.5f)
	#define PI_DIV_4	(PI*0.25f)
	#define PI_INV		0.318309886f

	// 角度转弧度
	#define Degree_TO_Radian(deg)	(deg * PI / 180)
	// 弧度转角度
	#define Radian_TO_Degree(rad)	(rad * 180 * PI_INV)

	// 计算精度
	#define EPSILON_E6	((float)(1E-6))

	//#define HXCOLOR_TO_24BIT(r,g,b)		(((r) & 0xff) << 16 | ((g) & 0xff) << 8 | ((b) & 0xff))

	struct HXCOLOR
	{
		// unsigned char r, g, b, a;
		// 光栅化线性插值产生step里的color rgba分量可能是负值
		float r, g, b, a;

		HXCOLOR() :r(255), g(255), b(255), a(255) {}

		/*HXCOLOR(int color, unsigned char alpha = 255)
		{
			r = (unsigned char)((color & 0xff0000) >> 16);
			g = (unsigned char)((color & 0x00ff00) >> 8);
			b = (unsigned char)(color & 0x0000ff);
			a = alpha;
		}*/

		HXCOLOR(float fr, float fg, float fb, float fa = 255) :
			r(fr), g(fg), b(fb), a(fa) {}

		/*inline int ToInt() const
		{
			return HXCOLOR_TO_24BIT(r,g,b);
		}*/

		inline HXCOLOR operator*(const HXCOLOR& rhs) const
		{
			// r >> 8  相当于  r / 255
			return HXCOLOR(r * (rhs.r / 255), g * (rhs.g / 255), b * (rhs.b / 255), a * (rhs.a / 255));
		}

		inline HXCOLOR operator/(float rhs) const
		{
			return HXCOLOR(r/rhs, g/rhs, b/rhs, a/rhs);
		}

		inline HXCOLOR operator-(const HXCOLOR& rhs) const
		{
			float fR = r - rhs.r;
			float fG = g - rhs.g;
			float fB = b - rhs.b;
			float fA = a - rhs.a;
			
			return HXCOLOR(fR, fG, fB, fA);
		}

		inline HXCOLOR& operator+=(const HXCOLOR& rhs)
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