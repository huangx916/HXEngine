#include "..\include\HXGLTransform.h"
#include "HXMath.h"

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

	HXVector3D HXGLTransform::GetGlobalPosition()
	{
		mPostion = GetVector3DMulMatrix44(HXVector3D(0,0,0), mGlobalModelMatrix);
		return mPostion;
	}

	HXVector3D HXGLTransform::GetGlobalRotation()
	{
		//float x = Radian_TO_Degree(atan2(mGlobalModelMatrix.m[2][1], mGlobalModelMatrix.m[2][2]/mGlobalScale.z));
		//float y = Radian_TO_Degree(atan2(-mGlobalModelMatrix.m[2][0], sqrt(mGlobalModelMatrix.m[2][1] * mGlobalModelMatrix.m[2][1] + mGlobalModelMatrix.m[2][2] / mGlobalScale.z * mGlobalModelMatrix.m[2][2] / mGlobalScale.z)));
		//float z = Radian_TO_Degree(atan2(mGlobalModelMatrix.m[1][0], mGlobalModelMatrix.m[0][0]/mGlobalScale.x));
		////float z = Radian_TO_Degree(atan2(mGlobalModelMatrix.m[0][1], -mGlobalModelMatrix.m[1][1]/mGlobalScale.y));
		//return HXVector3D(x, y, z);

		//float x = Radian_TO_Degree(atan2(mGlobalRotationMatrix.m[2][1], mGlobalRotationMatrix.m[2][2]));
		//float y = Radian_TO_Degree(atan2(-mGlobalRotationMatrix.m[2][0], sqrt(mGlobalRotationMatrix.m[2][1] * mGlobalRotationMatrix.m[2][1] + mGlobalRotationMatrix.m[2][2] * mGlobalRotationMatrix.m[2][2])));
		//float z = Radian_TO_Degree(atan2(mGlobalRotationMatrix.m[1][0], mGlobalRotationMatrix.m[0][0]));
		////float z = Radian_TO_Degree(atan2(mGlobalRotationMatrix.m[0][1], -mGlobalRotationMatrix.m[1][1]));
		//return HXVector3D(x, y, z);

		////return mGlobalEulerDegree;

		/*mGlobalEulerDegree = mGlobalQuaternion.ToEulerDegree1();
		return mGlobalEulerDegree;*/

		double euler[3];
		mRotation.quaternion2Euler(euler);
		mEuler = HXVector3D(Radian_TO_Degree(euler[0]), Radian_TO_Degree(euler[1]), Radian_TO_Degree(euler[2]));
		return mEuler;

		//return mRotation;
	}

	HXVector3D HXGLTransform::GetGlobalScale()
	{
		return mScale;
	}

	void HXGLTransform::CaculateModelMatrix(HXMatrix44& fatherModelMatrix)
	{
		//// 转换成右手坐标系
		//vmath::mat4 fatherMatrix = ConvertMatrix(fatherModelMatrix);
		//
		//// 缩放处理S
		//vmath::mat4 matS = vmath::scale(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		//// 旋转处理Q
		//vmath::mat4 matX = vmath::rotate(mLocalEulerDegree.x, 1.0f, 0.0f, 0.0f);
		//vmath::mat4 matY = vmath::rotate(mLocalEulerDegree.y, 0.0f, 1.0f, 0.0f);
		//vmath::mat4 matZ = vmath::rotate(mLocalEulerDegree.z, 0.0f, 0.0f, 1.0f);
		//// 平移一定要最后处理T
		//vmath::mat4 matT = vmath::translate(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		//// 模型空间到世界空间转换 SQT(OPENGL右手坐标系，从右往左结合)
		//vmath::mat4 localMatrixModel = matT*matX*matZ*matY*matS;
		//vmath::mat4 globalMatrixModel = fatherMatrix * localMatrixModel;

		//// 转换回左手坐标系保存
		//mGlobalModelMatrix = UnConvertMatrix(globalMatrixModel);


		// 中间过程不需要转，最后转成GLSL所需类型就行
		// 缩放处理S
		HXMatrix44 matS = GetScaleMatrix44(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mLocalEuler.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mLocalEuler.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mLocalEuler.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT
		//mGlobalModelMatrix = matS*matY*matZ*matX*matT * fatherModelMatrix;
		mGlobalModelMatrix = matS*matY*matX*matZ*matT * fatherModelMatrix;


		mScale = mLocalScale * parent->mScale;

		HXQuaternionOld q;
		q.FromEulerDegree(mLocalEuler.x, mLocalEuler.y, mLocalEuler.z);
		mRotation = q * parent->mRotation;

		//HXVector3D test = q.ToEulerDegree1();
		double euler[3];
		q.quaternion2Euler(euler);
		HXVector3D test = HXVector3D(Radian_TO_Degree(euler[0]), Radian_TO_Degree(euler[1]), Radian_TO_Degree(euler[2]));
	}

	void HXGLTransform::CaculateModelMatrix()
	{
		//// 缩放处理S
		//vmath::mat4 matS = vmath::scale(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		//// 旋转处理Q
		//vmath::mat4 matX = vmath::rotate(mLocalEulerDegree.x, 1.0f, 0.0f, 0.0f);
		//vmath::mat4 matY = vmath::rotate(mLocalEulerDegree.y, 0.0f, 1.0f, 0.0f);
		//vmath::mat4 matZ = vmath::rotate(mLocalEulerDegree.z, 0.0f, 0.0f, 1.0f);
		//// 平移一定要最后处理T
		//vmath::mat4 matT = vmath::translate(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		//// 模型空间到世界空间转换 SQT(OPENGL右手坐标系，从右往左结合)
		//vmath::mat4 localMatrixModel = matT*matX*matZ*matY*matS;
		//vmath::mat4 globalMatrixModel = localMatrixModel;

		//// 转换回左手坐标系保存
		//mGlobalModelMatrix = UnConvertMatrix(globalMatrixModel);


		// 中间过程不需要转，最后转成GLSL所需类型就行
		// 缩放处理S
		HXMatrix44 matS = GetScaleMatrix44(mLocalScale.x, mLocalScale.y, mLocalScale.z);
		// 旋转处理Q
		HXMatrix44 matX = GetRotateMatrix44X(mLocalEuler.x);
		HXMatrix44 matY = GetRotateMatrix44Y(mLocalEuler.y);
		HXMatrix44 matZ = GetRotateMatrix44Z(mLocalEuler.z);
		// 平移一定要最后处理T
		HXMatrix44 matT = GetTranslateMatrix44(mLocalPostion.x, mLocalPostion.y, mLocalPostion.z);

		// 模型空间到世界空间转换 SQT
		//mGlobalModelMatrix = matS*matY*matZ*matX*matT;
		mGlobalModelMatrix = matS*matY*matX*matZ*matT;


		mScale = mLocalScale;

		HXQuaternionOld q;
		q.FromEulerDegree(mLocalEuler.x, mLocalEuler.y, mLocalEuler.z);
		mRotation = q;

		//HXVector3D test = q.ToEulerDegree1();
		double euler[3];
		q.quaternion2Euler(euler);
		HXVector3D test = HXVector3D(Radian_TO_Degree(euler[0]), Radian_TO_Degree(euler[1]), Radian_TO_Degree(euler[2]));
	}
}
