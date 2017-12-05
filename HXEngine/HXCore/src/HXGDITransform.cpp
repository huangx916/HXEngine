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

	void HXGDITransform::CaculateModelMatrix(HXMatrix44& fatherModelMatrix)
	{
		// 缩放处理S
		HXMatrix44 matS = GetScaleMatrix44(mScale.x, mScale.y, mScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mEulerDegree.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mEulerDegree.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mEulerDegree.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mPostion.x, mPostion.y, mPostion.z);

		// 模型空间到世界空间转换 SQT
		// HXMatrix44 mat = matS*matX*matY*matZ*matT;
		HXMatrix44 mat = matS*matY*matZ*matX*matT;

		mCurModelMatrix = mat * fatherModelMatrix;
	}

	void HXGDITransform::CaculateModelMatrix()
	{
		// 缩放处理S
		HXMatrix44 matS = GetScaleMatrix44(mScale.x, mScale.y, mScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mEulerDegree.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mEulerDegree.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mEulerDegree.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mPostion.x, mPostion.y, mPostion.z);

		// 模型空间到世界空间转换 SQT
		// HXMatrix44 mat = matS*matX*matY*matZ*matT;
		HXMatrix44 mat = matS*matY*matZ*matX*matT;

		mCurModelMatrix = mat;
	}
}