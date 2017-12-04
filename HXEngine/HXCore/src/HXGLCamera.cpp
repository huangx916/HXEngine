#include "..\include\HXGLCamera.h"
#include "HXMath.h"

namespace HX3D
{
	HXGLCamera::HXGLCamera()
	{
	}

	HXGLCamera::~HXGLCamera()
	{
	}

	void HXGLCamera::Initialize(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
		float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
		float left, float right, float bottom, float top)
	{
		mEye = eye;
		mAt = at;
		mUp = up;
		mLeft = left;
		mRight = right;
		mBottom = bottom;
		mTop = top;
		mNear = nearZ;
		mFar = farZ;

		UpdateViewMatrix(mEye, mAt, mUp);
		UpdateProjectionMatrix(mLeft, mRight, mBottom, mTop, mNear, mFar);
	}

	void HXGLCamera::Update()
	{
		UpdateViewMatrix(mEye, mAt, mUp);
	}

	void HXGLCamera::OnViewPortResize(int nScreenWidth, int nScreenHeight)
	{
		float gAspect = (float)nScreenHeight / (float)nScreenWidth;
		mBottom = -gAspect;
		mTop = gAspect;
		UpdateProjectionMatrix(mLeft, mRight, mBottom, mTop, mNear, mFar);
	}

	void HXGLCamera::move(const HXVector3D& mov)
	{
		mEye += mov;
		mAt += mov;
	}

	void HXGLCamera::yaw(float fDegree)
	{
		HXVector3D distance = mAt - mEye;
		HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
		HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
		distance = HXVector3D(vec.x, vec.y, vec.z);
		mAt = mEye + distance;
	}

	void HXGLCamera::pitch(float fDegree)
	{
		HXVector3D distance = mAt - mEye;
		HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
		HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
		distance = HXVector3D(vec.x, vec.y, vec.z);
		mAt = mEye + distance;
	}

	void HXGLCamera::YawLockTarget(float fDegree)
	{
		HXVector3D distance = mEye - mAt;
		HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
		HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
		distance = HXVector3D(vec.x, vec.y, vec.z);
		mEye = mAt + distance;
	}

	void HXGLCamera::PitchLockTarget(float fDegree)
	{
		HXVector3D distance = mEye - mAt;
		HXVector4D vec = HXVector4D(distance, 1);
		
		float tanRadian = distance.x / distance.z;
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

		distance = HXVector3D(vec.x, vec.y, vec.z);
		mEye = mAt + distance;

		/*HXVector3D distance = mEye - mAt;
		HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
		HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
		distance = HXVector3D(vec.x, vec.y, vec.z);
		mEye = mAt + distance;*/
	}

	void HXGLCamera::Forward(float fDistance)
	{
		HXVector3D direction = mAt - mEye;
		direction.normalize();
		HXVector3D forward = direction * fDistance;
		mAt += forward;
		mEye += forward;
	}

	void HXGLCamera::UpdateViewMatrix(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up)
	{
		// UVN相机
		mMatrixView = vmath::lookat(vmath::vec3(eye.x, eye.y, eye.z), vmath::vec3(at.x, at.y, at.z), vmath::vec3(up.x, up.y, up.z));
	}

	void HXGLCamera::UpdateProjectionMatrix(float left, float right, float bottom, float top, float n, float f)
	{
		mMatrixProjection = vmath::frustum(left, right, bottom, top, n, f);
	}
}