#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXICamera
	{
	public:
		HXICamera() {};
		virtual ~HXICamera() {};

		virtual void Initialize(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up, 
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth, 
			float left, float right, float bottom, float top) = 0;

		virtual void Update() = 0;
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight) = 0;
	};
}
