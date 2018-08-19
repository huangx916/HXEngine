#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	class HXQuaternionS
	{
	public:
		static const HXQuaternionS IDENTITY;

		HXQuaternionS();
		HXQuaternionS(float fX, float fY, float fZ, float fW);
		~HXQuaternionS();

		HXQuaternionS Inverse() const;
		void Normalize();
		void FromEulerDegree(float fX, float fY, float fZ);
		void FromAngleAxis(float fDegree, HXVector3D axis);

		HXVector3D ToEulerDegree();
		static float arcTanAngle(float x, float y);

		HXQuaternionS operator*( const HXQuaternionS& rhs) const;
		HXVector3D Transform(const HXVector3D& vSrc);

		static void CreateFromMatrix4x4(const HXMatrix44& mat, HXQuaternionS& out);
		void Identity();

		float x;
		float y;
		float z;
		float w;
	};
}