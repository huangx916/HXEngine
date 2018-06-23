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

		virtual void Initialize(const HXVector3D& position, const HXVector3D& rotate,
			float nearZ, float farZ);

		virtual void Update();
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight);

		// 相机移动
		virtual void move(const HXVector3D& mov);
		// 绕Y轴旋转
		virtual void yaw(float fDegree);
		// 绕X轴旋转
		virtual void pitch(float fDegree);

		HXFrustum* mFrustum;
	};
}
