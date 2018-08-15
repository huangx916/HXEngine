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
		HXMatrix44 matS = GetScaleMatrix44(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mLocalEulerDegree.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mLocalEulerDegree.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mLocalEulerDegree.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT
		// HXMatrix44 mat = matS*matX*matY*matZ*matT;
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
		// HXMatrix44 mat = matS*matX*matY*matZ*matT;
		HXMatrix44 mat = matS*matY*matZ*matX*matT;

		mGlobalModelMatrix = mat;
	}
}