#include "..\include\HXGDITransform.h"
#include "HXMath.h"

namespace HX3D
{
	HXGDITransform::HXGDITransform()
	{
	}

	HXGDITransform::~HXGDITransform()
	{
	}

	HXVector3D HXGDITransform::GetGlobalPosition()
	{
		return GetVector3DMulMatrix44(mLocalPostion, mGlobalModelMatrix);
	}

	HXVector3D HXGDITransform::GetGlobalRotation()
	{
		return GetVector3DMulMatrix44(mLocalEulerDegree, mGlobalModelMatrix);
	}

	HXVector3D HXGDITransform::GetGlobalScale()
	{
		return GetVector3DMulMatrix44(mLocalScale, mGlobalModelMatrix);
	}

	void HXGDITransform::CaculateModelMatrix(HXMatrix44& fatherModelMatrix)
	{
		// 缩放处理S
		HXMatrix44 matS = GetScaleMatrix44(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mLocalEulerDegree.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mLocalEulerDegree.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mLocalEulerDegree.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT
		HXMatrix44 mat = matS*matY*matZ*matX*matT;

		mGlobalModelMatrix = mat * fatherModelMatrix;
	}

	void HXGDITransform::CaculateModelMatrix()
	{
		// 缩放处理S
		HXMatrix44 matS = GetScaleMatrix44(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mLocalEulerDegree.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mLocalEulerDegree.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mLocalEulerDegree.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT
		HXMatrix44 mat = matS*matY*matZ*matX*matT;

		mGlobalModelMatrix = mat;
	}
}