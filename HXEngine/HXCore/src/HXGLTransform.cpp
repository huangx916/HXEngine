#include "..\include\HXGLTransform.h"

namespace HX3D
{
	HXGLTransform::HXGLTransform()
	{
	}

	HXGLTransform::~HXGLTransform()
	{
	}

	vmath::mat4 HXGLTransform::ConvertMatrix(HXMatrix44& mat)
	{
		vmath::mat4 destMat4;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				destMat4[i][j] = mat.m[i][j];
			}
		}
		return destMat4;
	}

	HXMatrix44 HXGLTransform::UnConvertMatrix(vmath::mat4& mat)
	{
		HXMatrix44 destMat;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				destMat.m[i][j] = mat[i][j];
			}
		}
		return destMat;
	}

	void HXGLTransform::CaculateModelMatrix(HXMatrix44& fatherModelMatrix)
	{
		// 转换成右手坐标系
		vmath::mat4 fatherMatrix = ConvertMatrix(fatherModelMatrix);
		

		// 缩放处理S
		vmath::mat4 matS = vmath::scale(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		vmath::mat4 matX = vmath::rotate(mLocalEulerDegree.x, 1.0f, 0.0f, 0.0f);
		vmath::mat4 matY = vmath::rotate(mLocalEulerDegree.y, 0.0f, 1.0f, 0.0f);
		vmath::mat4 matZ = vmath::rotate(mLocalEulerDegree.z, 0.0f, 0.0f, 1.0f);
		// 平移一定要最后处理T
		vmath::mat4 matT = vmath::translate(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT(OPENGL右手坐标系，从右往左结合)
		vmath::mat4 localMatrixModel = matT*matX*matZ*matY*matS;
		// mMatrixModel = matS * matY * matZ * matX * matT;
		vmath::mat4 globalMatrixModel = fatherMatrix * localMatrixModel;


		// 转换回左手坐标系保存
		mGlobalModelMatrix = UnConvertMatrix(globalMatrixModel);
	}

	void HXGLTransform::CaculateModelMatrix()
	{
		// 缩放处理S
		vmath::mat4 matS = vmath::scale(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		vmath::mat4 matX = vmath::rotate(mLocalEulerDegree.x, 1.0f, 0.0f, 0.0f);
		vmath::mat4 matY = vmath::rotate(mLocalEulerDegree.y, 0.0f, 1.0f, 0.0f);
		vmath::mat4 matZ = vmath::rotate(mLocalEulerDegree.z, 0.0f, 0.0f, 1.0f);
		// 平移一定要最后处理T
		vmath::mat4 matT = vmath::translate(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT(OPENGL右手坐标系，从右往左结合)
		vmath::mat4 localMatrixModel = matT*matX*matZ*matY*matS;
		// mMatrixModel = matS * matY * matZ * matX * matT;
		vmath::mat4 globalMatrixModel = localMatrixModel;

		// 转换回左手坐标系保存
		mGlobalModelMatrix = UnConvertMatrix(globalMatrixModel);
	}
}
