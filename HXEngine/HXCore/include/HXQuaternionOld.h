#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	class HXQuaternionOld
	{
	public:
		static const HXQuaternionOld IDENTITY;

		HXQuaternionOld();
		HXQuaternionOld(float fX, float fY, float fZ, float fW);
		~HXQuaternionOld();

		HXQuaternionOld Inverse() const;
		void Normalize();
		void FromEulerDegree(float fX, float fY, float fZ);
		void FromAngleAxis(float fDegree, HXVector3D axis);

		HXVector3D ToEulerDegree();
		static float arcTanAngle(float x, float y);

		HXQuaternionOld operator*( const HXQuaternionOld& rhs) const;
		HXVector3D Transform(const HXVector3D& vSrc);

		static void CreateFromMatrix4x4(const HXMatrix44& mat, HXQuaternionOld& out);
		void Identity();

		float x;
		float y;
		float z;
		float w;
	};
}