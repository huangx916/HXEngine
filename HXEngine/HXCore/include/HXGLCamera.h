#pragma once
#include "HXCommon.h"
#include "HXICamera.h"
#include "vgl.h"
#include "vmath.h"
#include "HXVector.h"

namespace HX3D
{
	class HXGLCamera : public HXICamera
	{
	public:
		HXGLCamera();
		~HXGLCamera();

		virtual void Initialize(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
			float left, float right, float bottom, float top);

		virtual void Update();
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
	
		vmath::mat4 mMatrixView;
		vmath::mat4 mMatrixProjection;

	private:
		void UpdateViewMatrix(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up);
		void UpdateProjectionMatrix(float left, float right, float bottom, float top, float n, float f);

		HXVector3D mEye;
		HXVector3D mAt;
		HXVector3D mUp;
		float mLeft;
		float mRight;
		float mBottom; 
		float mTop;
		float mNear;
		float mFar;
	};
}


