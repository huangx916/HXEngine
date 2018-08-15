#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMatrix.h"

namespace HX3D
{
	class HXGameObject;
	class HXITransform
	{
	public:
		HXITransform();
		virtual ~HXITransform();

		void SetLocalPosition(const HXVector3D& pos);
		const HXVector3D& GetLocalPosition();
		//const HXVector3D& GetGlobalPosition();
		void Move(const HXVector3D& mov);

		void SetLocalRotation(const HXVector3D& rotation);
		const HXVector3D& GetLocalRotation();
		void Pitch(float fDegree);	// ÈÆXÖáÐý×ª
		void Yaw(float fDegree);	// ÈÆYÖáÐý×ª
		void Roll(float fDegree);	// ÈÆZÖáÐý×ª

		void SetLocalScale(const HXVector3D& scale);
		const HXVector3D& GetLocalScale();

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix) = 0;
		virtual void CaculateModelMatrix() = 0;

		void AddChild(HXITransform* child);
		std::vector<HXITransform*>& GetChildren();

		HXITransform* parent;
		HXGameObject* gameObject;
		std::vector<HXITransform*> vctChildren;

		HXVector3D mLocalPostion;
		HXVector3D mLocalEulerDegree;
		HXVector3D mLocalScale;

		HXMatrix44 mGlobalModelMatrix;
	};
}