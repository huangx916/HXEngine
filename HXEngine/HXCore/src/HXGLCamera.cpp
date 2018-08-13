#include "..\include\HXGLCamera.h"
#include "HXMath.h"
#include "HXGLTransform.h"
#include "HXRenderSystem.h"
#include "HXGLRenderSystem.h"
#include "HXGLShadowMap.h"
#include "Matrices.h"

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

		UpdateProjectionMatrix(mField, mSize, mNear, mFar);
	}

	bool HXGLCamera::PreRender()
	{
		glViewport(mViewportRectX * HXGLRenderSystem::gCurScreenWidth, mViewportRectY * HXGLRenderSystem::gCurScreenHeight, mViewportRectW * HXGLRenderSystem::gCurScreenWidth, mViewportRectH * HXGLRenderSystem::gCurScreenHeight);
		// 清除部分绘制区域
		glScissor(mViewportRectX * HXGLRenderSystem::gCurScreenWidth, mViewportRectY * HXGLRenderSystem::gCurScreenHeight, mViewportRectW * HXGLRenderSystem::gCurScreenWidth, mViewportRectH * HXGLRenderSystem::gCurScreenHeight);
		glEnable(GL_SCISSOR_TEST);
		switch (clearFlag)
		{
		case HX3D::CF_SOLIDCOLOR:
			glClearColor(background.r / 256, background.g / 256, background.b / 256, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			break;
		case HX3D::CF_DEPTHONLY:
			glClear(GL_DEPTH_BUFFER_BIT);
			break;
		case HX3D::CF_DONTCLEAR:
			break;
		default:
			break;
		}
		glDisable(GL_SCISSOR_TEST);
		return true;
	}

	void HXGLCamera::PostRender()
	{
		glViewport(0, 0, HXGLRenderSystem::gCurScreenWidth, HXGLRenderSystem::gCurScreenHeight);
	}

	bool HXGLCamera::PreRenderShadowMap()
	{
		if (HXGLRenderSystem::mShadowMap && HXGLRenderSystem::mShadowMap->IsEnable())
		{
			HXGLRenderSystem::mShadowMap->PreRender();
			return true;
		}
		else
		{
			return false;
		}
	}

	void HXGLCamera::PostRenderShadowMap()
	{
		if (HXGLRenderSystem::mShadowMap && HXGLRenderSystem::mShadowMap->IsEnable())
		{
			HXGLRenderSystem::mShadowMap->PostRender();
		}
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
		UpdateProjectionMatrix(mField, mSize, mNear, mFar);
	}

	HXVector3D HXGLCamera::WorldToNDCPoint(HXVector3D position)
	{
		//vmath::vec4 vec(position.x, position.y, position.z, 1.0f);
		//vec = mMatrixProjection * mMatrixView * vec;
		//return HXVector3D(vec[0] / vec[3], vec[1] / vec[3], vec[2] / vec[3]);

		Matrix4 matProj = Matrix4(mMatrixProjection);
		Matrix4 matView =  Matrix4(mMatrixView);
		Vector4 v = Vector4(position.x, position.y, position.z, 1.0f);
		v = matProj * matView * v;
		return HXVector3D(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
		
	}

	HXVector3D HXGLCamera::NDCToWorldPoint(HXVector3D position)
	{
		Matrix4 matProj = Matrix4(mMatrixProjection);
		Matrix4 matView = Matrix4(mMatrixView);
		Vector4 v = Vector4(position.x, position.y, position.z, 1.0f);
		v = matView.invert() * matProj.invert() * v;
		return HXVector3D(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
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

	//void HXGLCamera::UpdateProjectionMatrix(float left, float right, float bottom, float top, float n, float f)
	//{
	//	// 默认使用90度视野 left = -n	right = n;
	//	left *= n;
	//	right *= n;
	//	bottom *= n;
	//	top *= n;
	//	if (projection == CP_ORTHOGRAPHIC)
	//	{
	//		mMatrixProjection = vmath::Ortho(-5, 5, -5, 5, n, f);
	//	}
	//	else
	//	{
	//		mMatrixProjection = vmath::frustum(left, right, bottom, top, n, f);
	//	}
	//}

	void HXGLCamera::UpdateProjectionMatrix(float field, float size, float n, float f)
	{
		if (projection == CP_ORTHOGRAPHIC)
		{
			if (mViewportRectH <= 0 || mViewportRectW <= 0)
			{
				mMatrixProjection = vmath::Ortho(0, 0, 0, 0, n, f);
			}
			else
			{
				float top = size;
				float gAspect = (mViewportRectW * HXRenderSystem::gCurScreenWidth) / (mViewportRectH * HXRenderSystem::gCurScreenHeight);
				float right = gAspect * top;
				mMatrixProjection = vmath::Ortho(-right, right, -top, top, n, f);
			}
		}
		else
		{
			if (mViewportRectH <= 0 || mViewportRectW <= 0)
			{
				mMatrixProjection = vmath::frustum(0, 0, 0, 0, n, f);
			}
			else
			{
				float fRadian = Degree_TO_Radian(field);
				float top = tan(fRadian / 2) * n;
				float gAspect = (mViewportRectW * HXRenderSystem::gCurScreenWidth) / (mViewportRectH * HXRenderSystem::gCurScreenHeight);
				float right = gAspect * top;
				mMatrixProjection = vmath::frustum(-right, right, -top, top, n, f);
			}
		}
	}
}