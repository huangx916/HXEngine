#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMatrix.h"

namespace HX3D
{
	class HXITransform
	{
	public:
		HXITransform();
		virtual ~HXITransform();

		void SetPosition(const HXVector3D& pos);
		HXVector3D GetPosition();
		void Move(const HXVector3D& mov);

		void SetRotation(const HXVector3D& rotation);
		HXVector3D GetRotation();
		void Pitch(float fDegree);	// ÈÆXÖáÐý×ª
		void Yaw(float fDegree);	// ÈÆYÖáÐý×ª
		void Roll(float fDegree);	// ÈÆZÖáÐý×ª

		void SetScale(const HXVector3D& scale);
		HXVector3D GetScale();

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix) = 0;
		virtual void CaculateModelMatrix() = 0;

		HXVector3D mPostion;
		HXVector3D mEulerDegree;
		HXVector3D mScale;

		HXMatrix44 mCurModelMatrix;
	};
}