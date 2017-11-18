#pragma once
#include "HXCommon.h"
#include "HXICamera.h"

namespace HX3D
{
	struct HXFrustum;
	// TODO: Frustum Cull  nearClip farClip etc.
	class HXGDICamera : public HXICamera
	{
	public:
		HXGDICamera();
		~HXGDICamera();

		virtual void Initialize(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
			float left, float right, float bottom, float top);

		virtual void Update();
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight);

		HXFrustum* mFrustum;
	};
}
