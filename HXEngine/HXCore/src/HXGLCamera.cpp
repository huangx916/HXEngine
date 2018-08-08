#include "..\include\HXGLCamera.h"
#include "HXMath.h"
#include "HXGLTransform.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	HXGLCamera::HXGLCamera()
	{
		transform = new HXGLTransform();
	}

	HXGLCamera::~HXGLCamera()
	{
		delete transform;
	}

	void HXGLCamera::Initialize(const HXVector3D& position, const HXVector3D& rotate,
		float nearZ, float farZ)
	{
		mNear = nearZ;
		mFar = farZ;

		transform->mPostion = position;
		transform->mEulerDegree = rotate;

		float gAspect = (float)HXRenderSystem::gCurScreenWidth / (float)HXRenderSystem::gCurScreenHeight;
		UpdateProjectionMatrix(-1, 1, -gAspect, gAspect, mNear, mFar);
	}

	void HXGLCamera::Update()
	{
		UpdateViewMatrix(transform->mPostion, UpdateAt(), UpdateUp());
	}

	HXVector3D HXGLCamera::UpdateAt()
	{
		HXQuaternion q;
		q.FromEulerDegree(transform->mEulerDegree.x, transform->mEulerDegree.y, transform->mEulerDegree.z);
		HXVector3D vec = HXVector3D(0, 0, -1);
		vec = q.Transform(vec);
		return transform->mPostion + vec;
	}

	HXVector3D HXGLCamera::UpdateUp()
	{
		HXQuaternion q;
		q.FromEulerDegree(transform->mEulerDegree.x, transform->mEulerDegree.y, transform->mEulerDegree.z);
		HXVector3D vec = HXVector3D(0, 1, 0);
		return q.Transform(vec);
	}

	void HXGLCamera::OnViewPortResize(int nScreenWidth, int nScreenHeight)
	{
		float gAspect = (float)nScreenHeight / (float)nScreenWidth;
		UpdateProjectionMatrix(-1, 1, -gAspect, gAspect, mNear, mFar);
	}

	void HXGLCamera::move(const HXVector3D& mov)
	{
		HXQuaternion q;
		q.FromEulerDegree(transform->mEulerDegree.x, transform->mEulerDegree.y, transform->mEulerDegree.z);
		HXVector3D v = mov;
		v = q.Transform(v);
		transform->mPostion += v;
	}

	void HXGLCamera::yaw(float fDegree)
	{
		// 四元数形式
		transform->mEulerDegree.y += fDegree;
	}

	void HXGLCamera::pitch(float fDegree)
	{
		// 四元数形式
		transform->mEulerDegree.x += fDegree;
	}

	void HXGLCamera::UpdateViewMatrix(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up)
	{
		// UVN相机
		mMatrixView = vmath::lookat(vmath::vec3(eye.x, eye.y, eye.z), vmath::vec3(at.x, at.y, at.z), vmath::vec3(up.x, up.y, up.z));
	}

	void HXGLCamera::UpdateProjectionMatrix(float left, float right, float bottom, float top, float n, float f)
	{
		// 默认使用90度视野 left = -n	right = n;
		left *= n;
		right *= n;
		bottom *= n;
		top *= n;
		mMatrixProjection = vmath::frustum(left, right, bottom, top, n, f);
		//mMatrixProjection = vmath::Ortho(-5, 5, -5, 5, 0.01, 1000);
	}
}