#pragma once
#include "HXCommon.h"
#include "HXICamera.h"
#include "vgl.h"
#include "vmath.h"
#include "HXVector.h"
#include "HXQuaternionS.h"

namespace HX3D
{
	class HXGLCamera : public HXICamera
	{
	public:
		HXGLCamera();
		~HXGLCamera();

		virtual void Initialize(const HXVector3D& position, const HXVector3D& rotate,
			float nearZ, float farZ);

		virtual bool PreRender();
		virtual void PostRender();
		virtual bool PreRenderShadowMap();
		virtual void PostRenderShadowMap();

		virtual void Update();
		HXVector3D UpdateAt();
		HXVector3D UpdateUp();
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
	
		//virtual HXVector3D WorldToScreenPoint(HXVector3D position);
		//virtual HXVector3D ScreenToWorldPoint(HXVector3D position);
		//virtual HXVector3D WorldToViewportPoint(HXVector3D position);	//([0,1],[0,1])
		//virtual HXVector3D ViewportToWorldPoint(HXVector3D position);
		virtual HXVector3D WorldToNDCPoint(HXVector3D position);	//([-1,1],[-1,1])
		virtual HXVector3D NDCToWorldPoint(HXVector3D position);

		// 相机移动
		virtual void move(const HXVector3D& mov);
		// 绕Y轴旋转
		virtual void yaw(float fDegree);
		// 绕X轴旋转
		virtual void pitch(float fDegree);

		void UpdateViewMatrix(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up);
		//void UpdateProjectionMatrix(float left, float right, float bottom, float top, float n, float f);
		void UpdateProjectionMatrix(float field, float size, float n, float f);

		vmath::mat4 mMatrixView;
		vmath::mat4 mMatrixProjection;

		/*float mNear;
		float mFar;*/
	};
}


