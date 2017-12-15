#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXGameObject;
	class HXICamera
	{
	public:
		HXICamera() {};
		virtual ~HXICamera() {};

		virtual void Initialize(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up, 
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth, 
			float left, float right, float bottom, float top) = 0;

		virtual void Update() = 0;
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight) = 0;


		// 相机移动
		virtual void move(const HXVector3D& mov) = 0;
		// 绕Y轴旋转
		virtual void yaw(float fDegree) = 0;
		// 绕X轴旋转
		virtual void pitch(float fDegree) = 0;

		/*virtual void YawLockTarget(float fDegree) = 0;
		virtual void PitchLockTarget(float fDegree) = 0;*/

		virtual void Forward(float fDistance) = 0;
		virtual void MoveHorizon(float fDistance) = 0;
		virtual void MoveVertical(float fDistance) = 0;

		inline void AttachGameObject(HXGameObject* go) { followedGO.push_back(go); };
		inline void DetachGameObject(HXGameObject* go) { followedGO.remove(go); };
		std::list<HXGameObject*> followedGO;

	};
}
