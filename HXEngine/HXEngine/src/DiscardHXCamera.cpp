//#include "..\include\HXCamera.h"
//#include "HXFrustum.h"
//#include "HXMath.h"
//
//namespace HX3D
//{
//	HXCamera::HXCamera()
//	{
//		mFrustum = new HXFrustum(HXVector4D::ZERO, HXVector4D::ZERO, 75.0f, 10.0f, 1000.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
//	}
//
//
//	HXCamera::~HXCamera()
//	{
//	}
//
//	void HXCamera::setNearZ(float fNearZ)
//	{
//		mFrustum->clip_z_near = fNearZ;
//		mNeedUpdate = true;
//	}
//
//	void HXCamera::setFarZ(float fFarZ)
//	{
//		mFrustum->clip_z_far = fFarZ;
//		mNeedUpdate = true;
//	}
//
//	void HXCamera::update()
//	{
//		if (mNeedUpdate)
//		{
//			mFrustum->update();
//			mNeedUpdate = false;
//		}
//	}
//
//	void HXCamera::setPosition(const HXVector4D& pos)
//	{
//		mFrustum->camPosition = pos;
//		mNeedUpdate = true;
//	}
//
//	void HXCamera::setTargetPos(const HXVector4D& pos)
//	{
//		mFrustum->lookTarget = pos;
//		mNeedUpdate = true;
//	}
//
//	void HXCamera::move(const HXVector4D& mov)
//	{
//		mFrustum->camPosition += mov;
//		mFrustum->lookTarget += mov;
//		mNeedUpdate = true;
//	}
//
//	void HXCamera::yaw(float fDegree)
//	{
//		HXVector4D distance = mFrustum->lookTarget - mFrustum->camPosition;
//		HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
//		distance = GetVector4DMulMatrix44(distance, matRotate);
//		mFrustum->lookTarget = mFrustum->camPosition + distance;
//		mNeedUpdate = true;
//	}
//
//	void HXCamera::pitch(float fDegree)
//	{
//		HXVector4D distance = mFrustum->lookTarget - mFrustum->camPosition;
//		HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
//		distance = GetVector4DMulMatrix44(distance, matRotate);
//		mFrustum->lookTarget = mFrustum->camPosition + distance;
//		mNeedUpdate = true;
//	}
//}
