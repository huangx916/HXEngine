#include "..\include\HXGDICamera.h"
#include "HXFrustum.h"
#include "HXMath.h"
#include "HXQuaternion.h"
#include "HXGDITransform.h"

namespace HX3D
{
	HXGDICamera::HXGDICamera():mFrustum(NULL)
	{
		transform = new HXGDITransform();
	}

	HXGDICamera::~HXGDICamera()
	{
		if (mFrustum)
		{
			delete mFrustum;
			mFrustum = NULL;
		}
		delete transform;
	}

	void HXGDICamera::Initialize(const HXVector3D& position, const HXVector3D& rotate,
		float nearZ, float farZ)
	{
		transform->mLocalPostion = position;
		transform->mLocalEulerDegree = rotate;
		mFrustum = new HXFrustum(transform
			, 90, nearZ, farZ, SCREEN_WIDTH, SCREEN_HEIGHT);
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
		HXQuaternion q;
		q.FromEulerDegree(transform->mLocalEulerDegree.x, transform->mLocalEulerDegree.y, transform->mLocalEulerDegree.z);
		HXVector3D v = mov;
		v = q.Transform(v);
		transform->mLocalPostion += v;
	}

	void HXGDICamera::yaw(float fDegree)
	{
		transform->mLocalEulerDegree.y += fDegree;
	}

	void HXGDICamera::pitch(float fDegree)
	{
		transform->mLocalEulerDegree.x += fDegree;
	}
}