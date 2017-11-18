#include "..\include\HXGLCamera.h"

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

	void HXGLCamera::UpdateViewMatrix(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up)
	{
		// UVNÏà»ú
		mMatrixView = vmath::lookat(vmath::vec3(eye.x, eye.y, eye.z), vmath::vec3(at.x, at.y, at.z), vmath::vec3(up.x, up.y, up.z));
	}

	void HXGLCamera::UpdateProjectionMatrix(float left, float right, float bottom, float top, float n, float f)
	{
		mMatrixProjection = vmath::frustum(left, right, bottom, top, n, f);
	}
}