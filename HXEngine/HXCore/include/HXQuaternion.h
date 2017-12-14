#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	class HXQuaternion
	{
	public:
		static const HXQuaternion IDENTITY;

		HXQuaternion();
		HXQuaternion(float fX, float fY, float fZ, float fW);
		~HXQuaternion();

		HXQuaternion Inverse() const;
		void FromEulerDegree(float fX, float fY, float fZ);
		void FromAngleAxis(float fDegree, HXVector3D axis);
		HXQuaternion operator*( const HXQuaternion& rhs) const;
		HXVector3D Transform(const HXVector3D& vSrc);

		float x;
		float y;
		float z;
		float w;
	};
}