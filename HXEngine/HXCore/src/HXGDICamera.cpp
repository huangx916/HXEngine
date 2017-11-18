#include "..\include\HXGDICamera.h"
#include "HXFrustum.h"

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
}