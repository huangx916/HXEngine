#include "..\include\HXGDICamera.h"
#include "HXFrustum.h"
#include "HXMath.h"

namespace HX3D
{
	HXGDICamera::HXGDICamera():mFrustum(NULL)
	{
	}


	HXGDICamera::~HXGDICamera()
	{
		if (mFrustum)
		{
			delete mFrustum;
		}
	}

	void HXGDICamera::Initialize(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
		float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
		float left, float right, float bottom, float top)
	{
		mFrustum = new HXFrustum(HXVector4D(eye.x, eye.y, eye.z, 1), HXVector4D(at.x, at.y, at.z, 1)
			, ffov,nearZ, farZ, viewportWidth, viewportHeigth);
	}

	void HXGDICamera::Update()
	{
		if (mFrustum)
		{
			mFrustum->update();
		}
	}

	void HXGDICamera::OnViewPortResize(int nScreenWidth, int nScreenHeight)
	{

	}

	void HXGDICamera::move(const HXVector3D& mov)
	{
		mFrustum->camPosition += HXVector4D(mov.x, mov.y, mov.z, 1);
		mFrustum->lookTarget += HXVector4D(mov.x, mov.y, mov.z, 1);;
	}

	void HXGDICamera::yaw(float fDegree)
	{
		HXVector4D distance = mFrustum->lookTarget - mFrustum->camPosition;
		HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
		distance = GetVector4DMulMatrix44(distance, matRotate);
		mFrustum->lookTarget = mFrustum->camPosition + distance;
	}

	void HXGDICamera::pitch(float fDegree)
	{
		HXVector4D distance = mFrustum->lookTarget - mFrustum->camPosition;
		HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
		distance = GetVector4DMulMatrix44(distance, matRotate);
		mFrustum->lookTarget = mFrustum->camPosition + distance;
	}

	void HXGDICamera::YawLockTarget(float fDegree)
	{
		HXVector4D distance = mFrustum->camPosition - mFrustum->lookTarget;
		HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
		distance = GetVector4DMulMatrix44(distance, matRotate);
		mFrustum->camPosition = mFrustum->lookTarget + distance;
	}

	void HXGDICamera::PitchLockTarget(float fDegree)
	{
		HXVector4D vec = mFrustum->camPosition - mFrustum->lookTarget;

		float tanRadian = vec.x / vec.z;
		float fRadian = atan(tanRadian);
		float fDegreeY = Radian_TO_Degree(fRadian);
		if (vec.z < 0)
		{
			fDegreeY += 180;
		}
		// 先旋转到朝Z轴负方向
		HXMatrix44 matRotate = GetRotateMatrix44Y(-fDegreeY);
		vec = GetVector4DMulMatrix44(vec, matRotate);
		// pitch
		matRotate = GetRotateMatrix44X(fDegree);
		vec = GetVector4DMulMatrix44(vec, matRotate);
		// 恢复
		matRotate = GetRotateMatrix44Y(fDegreeY);
		vec = GetVector4DMulMatrix44(vec, matRotate);

		mFrustum->camPosition = mFrustum->lookTarget + vec;

		/*HXVector4D distance = mFrustum->camPosition - mFrustum->lookTarget;
		HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
		distance = GetVector4DMulMatrix44(distance, matRotate);
		mFrustum->camPosition = mFrustum->lookTarget + distance;*/
	}

	void HXGDICamera::Forward(float fDistance)
	{
		HXVector4D direction = mFrustum->lookTarget - mFrustum->camPosition;
		direction.normalize();
		HXVector4D forward = direction * fDistance;
		mFrustum->lookTarget += forward;
		mFrustum->camPosition += forward;
	}


}