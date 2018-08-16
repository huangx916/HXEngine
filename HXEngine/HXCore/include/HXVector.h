#pragma once
#include "HXCommon.h"
#include "HXUtil.h"

namespace HX3D
{
	struct HXVector2D
	{
		static HXVector2D ZERO;
		static HXVector2D UNIT_X;
		static HXVector2D UNIT_Y;

		float x;
		float y;
		
		HXVector2D() :x(0), y(0) {}
		HXVector2D(float fx, float fy) :x(fx), y(fy) {}
		HXVector2D(const HXVector2D& Vec):x(Vec.x),y(Vec.y){}

		inline float length() const
		{
			return sqrt(x*x + y*y);
		}

		// 返回归一化前的长度
		inline float normalize()
		{
			float fLen = length();
			if (fLen > EPSILON_E6)	// 保证除数大于0
			{
				x /= fLen;
				y /= fLen;
			}
			return fLen;
		}

		inline float dotProduct(const HXVector2D& rhs) const
		{
			return x*rhs.x + y*rhs.y;
		}

		inline HXVector2D operator+(const HXVector2D& rhs) const
		{
			return HXVector2D(x + rhs.x, y + rhs.y);
		}

		inline HXVector2D operator-(const HXVector2D& rhs) const
		{
			return HXVector2D(x-rhs.x, y-rhs.y);
		}

		inline HXVector2D operator*(float rhs) const
		{
			return HXVector2D(x*rhs, y*rhs);
		}

		inline HXVector2D& operator=(const HXVector2D& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		inline bool operator==(const HXVector2D& rhs) const
		{
			return EqualFloat(x, rhs.x) && EqualFloat(y, rhs.y);
		}
	};

	struct HXVector3D 
	{
		static HXVector3D ZERO;
		static HXVector3D UNIT_X;
		static HXVector3D UNIT_Y;
		static HXVector3D UNIT_Z;

		float x;
		float y;
		float z;

		HXVector3D() :x(0), y(0), z(0) {}
		HXVector3D(float fx, float fy, float fz):x(fx),y(fy),z(fz){}
		HXVector3D(const HXVector2D& vec, float fz) :x(vec.x), y(vec.y), z(fz) {}
		HXVector3D(const HXVector3D& vec):x(vec.x),y(vec.y),z(vec.z){}

		inline float length() const
		{
			return sqrt(x*x + y*y + z*z);
		}

		// 返回归一化前的长度
		inline float normalize()
		{
			float fLen = length();
			if (fLen > EPSILON_E6)
			{
				x /= fLen;
				y /= fLen;
				z /= fLen;
			}
			return fLen;
		}

		inline float dotProduct(const HXVector3D& rhs) const
		{
			return x*rhs.x + y*rhs.y + z*rhs.z;
		}

		inline HXVector3D crossProduct(const HXVector3D& rhs) const
		{
			return HXVector3D(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
		}

		inline HXVector3D operator+(const HXVector3D& rhs) const
		{
			return HXVector3D(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		inline HXVector3D operator-() const
		{
			return HXVector3D(-x,-y,-z);
		}

		inline HXVector3D operator-(const HXVector3D& rhs) const
		{
			return HXVector3D(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		inline HXVector3D operator*(float rhs) const
		{
			return HXVector3D(x*rhs, y*rhs, z*rhs);
		}

		inline HXVector3D operator*(const HXVector3D& rhs) const
		{
			return HXVector3D(x*rhs.x, y*rhs.y, z*rhs.z);
		}

		inline HXVector3D operator/(float rhs) const
		{
			return HXVector3D(x/rhs, y/rhs, z/rhs);
		}

		inline HXVector3D& operator=(const HXVector3D& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		inline HXVector3D& operator+=(const HXVector3D& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		inline HXVector3D& operator-=(const HXVector3D& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		inline bool operator==(const HXVector3D& rhs) const
		{
			return EqualFloat(x, rhs.x) && EqualFloat(y, rhs.y) && EqualFloat(z, rhs.z);
		}
	};

	struct HXVector4D
	{
		static HXVector4D ZERO;
		static HXVector4D UNIT_X;
		static HXVector4D UNIT_Y;
		static HXVector4D UNIT_Z;
		//static HXVector4D UNIT_W;

		float x;
		float y;
		float z;
		float w;

		HXVector4D():x(0),y(0),z(0),w(0){}
		HXVector4D(float fx, float fy, float fz, float fw = 1):x(fx),y(fy),z(fz),w(fw){}
		HXVector4D(const HXVector2D& vec, float fz, float fw) :x(vec.x), y(vec.y), z(fz), w(fw) {};
		HXVector4D(const HXVector3D& vec, float fw) :x(vec.x), y(vec.y), z(vec.z), w(fw) {};
		HXVector4D(const HXVector4D& vec) :x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

		// TODO: vec.xyz
		// HXVector3D xyz
		inline HXVector3D xyz()
		{
			return HXVector3D(x,y,z);
		}

		// 以下接口前提 w = 1
		inline float length() const
		{
			return sqrt(x*x + y*y + z*z);
		}

		inline float normalize()
		{
			float fLen = length();
			if (fLen > EPSILON_E6)
			{
				x /= fLen;
				y /= fLen;
				z /= fLen;
				w = 1;
			}
			return fLen;
		}

		inline float dotProduct(const HXVector4D& rhs) const
		{
			return x*rhs.x + y*rhs.y + z*rhs.z;
		}

		inline HXVector4D crossProduct(const HXVector4D& rhs) const
		{
			return HXVector4D(y*rhs.z-z*rhs.y, z*rhs.x-x*rhs.z, x*rhs.y-y*rhs.x, 1);
		}

		inline HXVector4D operator+(const HXVector4D& rhs) const
		{
			return HXVector4D(x + rhs.x, y + rhs.y, z + rhs.z, 1);
		}

		inline HXVector4D operator-(const HXVector4D& rhs) const
		{
			return HXVector4D(x - rhs.x, y - rhs.y, z - rhs.z, 1);
		}

		inline HXVector4D operator*(float rhs) const
		{
			return HXVector4D(x*rhs, y*rhs, z*rhs, 1);
		}

		inline HXVector4D& operator=(const HXVector4D& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		inline HXVector4D& operator+=(const HXVector4D& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w = 1;
			return *this;
		}

		inline HXVector4D& operator-=(const HXVector4D& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w = 1;
			return *this;
		}

		inline bool operator==(const HXVector4D& rhs) const
		{
			return EqualFloat(x, rhs.x) && EqualFloat(y, rhs.y) && EqualFloat(z, rhs.z) && EqualFloat(w, rhs.w);
		}
	};
}

