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
		mSrcEye = eye;
		mSrcAt = at;
		mSrcUp = up;
		mLeft = left;
		mRight = right;
		mBottom = bottom;
		mTop = top;
		mNear = nearZ;
		mFar = farZ;

		mYaw = 0.0f;
		mPitch = 0.0f;
		mRoll = 0.0f;

		UpdateViewMatrix(mSrcEye, mSrcAt, mSrcUp);
		UpdateProjectionMatrix(mLeft, mRight, mBottom, mTop, mNear, mFar);
	}

	void HXGLCamera::Update()
	{
		HXQuaternion q;
		q.FromEulerDegree(mPitch, mYaw, mRoll);
		HXVector3D vec = mSrcEye - mSrcAt;
		vec = q.Transform(vec);
		//mSrcEye = mSrcAt + vec;
		HXVector3D up = q.Transform(mSrcUp);

		//UpdateViewMatrix(mSrcEye, mSrcAt, mSrcUp);
		UpdateViewMatrix(mSrcAt + vec, mSrcAt, up);
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
		HXQuaternion q;
		q.FromEulerDegree(mPitch, mYaw, mRoll);
		HXVector3D v = mov;
		v = q.Transform(v);
		mSrcAt += v;
		mSrcEye += v;
	}

	void HXGLCamera::yaw(float fDegree)
	{
		/*HXVector3D distance = mSrcAt - mSrcEye;
		HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
		HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
		distance = HXVector3D(vec.x, vec.y, vec.z);
		mSrcAt = mSrcEye + distance;*/

		// 四元数形式
		mYaw += fDegree;
	}

	void HXGLCamera::pitch(float fDegree)
	{
		/*HXVector3D distance = mSrcAt - mSrcEye;
		HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
		HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
		distance = HXVector3D(vec.x, vec.y, vec.z);
		mSrcAt = mSrcEye + distance;*/

		// 四元数形式
		mPitch += fDegree;
	}

	//void HXGLCamera::YawLockTarget(float fDegree)
	//{
	//	HXVector3D distance = mSrcEye - mSrcAt;
	//	HXMatrix44 matRotate = GetRotateMatrix44Y(fDegree);
	//	HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
	//	distance = HXVector3D(vec.x, vec.y, vec.z);
	//	mSrcEye = mSrcAt + distance;
	//}

	//void HXGLCamera::PitchLockTarget(float fDegree)
	//{
	//	HXVector3D distance = mSrcEye - mSrcAt;
	//	HXVector4D vec = HXVector4D(distance, 1);
	//	
	//	float tanRadian = distance.x / distance.z;
	//	float fRadian = atan(tanRadian);
	//	float fDegreeY = Radian_TO_Degree(fRadian);
	//	if (vec.z < 0)
	//	{
	//		fDegreeY += 180;
	//	}
	//	// 先旋转到朝Z轴负方向
	//	HXMatrix44 matRotate = GetRotateMatrix44Y(-fDegreeY);
	//	vec = GetVector4DMulMatrix44(vec, matRotate);
	//	// pitch
	//	matRotate = GetRotateMatrix44X(fDegree);
	//	vec = GetVector4DMulMatrix44(vec, matRotate);
	//	// 恢复
	//	matRotate = GetRotateMatrix44Y(fDegreeY);
	//	vec = GetVector4DMulMatrix44(vec, matRotate);

	//	distance = HXVector3D(vec.x, vec.y, vec.z);
	//	mSrcEye = mSrcAt + distance;

	//	/*HXVector3D distance = mSrcEye - mSrcAt;
	//	HXMatrix44 matRotate = GetRotateMatrix44X(fDegree);
	//	HXVector4D vec = GetVector4DMulMatrix44(HXVector4D(distance, 1), matRotate);
	//	distance = HXVector3D(vec.x, vec.y, vec.z);
	//	mSrcEye = mSrcAt + distance;*/
	//}

	void HXGLCamera::Forward(float fDistance)
	{
		/*HXVector3D direction = mSrcAt - mSrcEye;
		direction.normalize();
		HXVector3D forward = direction * fDistance;
		mSrcAt += forward;
		mSrcEye += forward;*/

		HXQuaternion q;
		q.FromEulerDegree(mPitch, mYaw, mRoll);
		HXVector3D v(0, 0, -fDistance);
		v = q.Transform(v);
		mSrcAt += v;
		mSrcEye += v;
	}

	void HXGLCamera::MoveHorizon(float fDistance)
	{
		HXQuaternion q;
		q.FromEulerDegree(mPitch, mYaw, mRoll);
		HXVector3D v(fDistance, 0, 0);
		v = q.Transform(v);
		mSrcAt += v;
		mSrcEye += v;
	}

	void HXGLCamera::MoveVertical(float fDistance)
	{
		HXQuaternion q;
		q.FromEulerDegree(mPitch, mYaw, mRoll);
		HXVector3D v(0, -fDistance, 0);
		v = q.Transform(v);
		mSrcAt += v;
		mSrcEye += v;
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