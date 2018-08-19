#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMatrix.h"
#include "HXQuaternionS.h"

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
		virtual const HXVector3D& GetGlobalPosition() = 0;
		void Move(const HXVector3D& mov);

		void SetLocalRotation(const HXVector3D& rotation);
		const HXVector3D& GetLocalRotation();
		virtual HXVector3D GetGlobalRotation() = 0;
		void Pitch(float fDegree);	// ÈÆXÖáÐý×ª
		void Yaw(float fDegree);	// ÈÆYÖáÐý×ª
		void Roll(float fDegree);	// ÈÆZÖáÐý×ª

		void SetLocalScale(const HXVector3D& scale);
		const HXVector3D& GetLocalScale();
		virtual HXVector3D GetGlobalScale() = 0;

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix) = 0;
		virtual void CaculateModelMatrix() = 0;

		void AddChild(HXITransform* child);
		void RemoveChild(HXITransform* child);
		std::vector<HXITransform*>& GetChildren();


		// TODO: New
		const HXMatrix44& GetLocalMatrix();
		void SetLocalMatrix(const HXMatrix44& mat);
		void UpdateLocalMatrix();
		void OnWorldTransform();


		HXGameObject* gameObject;
		HXITransform* parent;
		std::vector<HXITransform*> vctChildren;

		HXVector3D mLocalPostion;
		HXQuaternionS mLocalRotation;
		HXVector3D mLocalScale;
		HXVector3D mLocalEuler;
		HXMatrix44 mLocalMatrix;

		HXVector3D mPostion;
		HXQuaternionS mRotation;
		HXVector3D mScale;
		HXMatrix44 mWorldMatrix;

		HXVector3D mEuler;

		bool _localQuaternionUpdate;
		bool _locaEulerlUpdate;
		bool _localUpdate;
		bool _worldUpdate;
		bool _positionUpdate;
		bool _rotationUpdate;
		bool _scaleUpdate;


		HXMatrix44 mGlobalModelMatrix;
	};
}