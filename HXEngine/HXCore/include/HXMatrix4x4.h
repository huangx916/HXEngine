#pragma once
#include "HXCommon.h"
#include "HXVector3.h"
#include "HXQuaternion.h"

namespace HX3D
{
	class HXMatrix4x4
	{
	public:
		HXMatrix4x4();
		~HXMatrix4x4();

		/**
		* 绕X轴旋转
		* @param	rad  旋转角度
		* @param	out 输出矩阵
		*/
		static void createRotationX(float rad, HXMatrix4x4& out);

		/**
		*
		* 绕Y轴旋转
		* @param	rad  旋转角度
		* @param	out 输出矩阵
		*/
		static void createRotationY(float rad, HXMatrix4x4& out);

		/**
		* 绕Z轴旋转
		* @param	rad  旋转角度
		* @param	out 输出矩阵
		*/
		static void createRotationZ(float rad, HXMatrix4x4& out);

		/**
		* 通过yaw pitch roll旋转创建旋转矩阵。
		* @param	yaw
		* @param	pitch
		* @param	roll
		* @param	result
		*/
		static void createRotationYawPitchRoll(float yaw, float pitch, float roll, HXMatrix4x4& result);

		/**
		* 通过旋转轴axis和旋转角度angle计算旋转矩阵。
		* @param	axis 旋转轴,假定已经归一化。
		* @param	angle 旋转角度。
		* @param	result 结果矩阵。
		*/
		static void createRotationAxis(const HXVector3& axis, float angle, HXMatrix4x4& result);

		/**
		* 通过四元数创建旋转矩阵。
		* @param	rotation 旋转四元数。
		* @param	result 输出旋转矩阵
		*/
		static void createRotationQuaternion(const HXQuaternion& rotation, HXMatrix4x4& result);

		/**
		* 根据平移计算输出矩阵
		* @param	trans  平移向量
		* @param	out 输出矩阵
		*/
		static void createTranslate(const HXVector3& trans, HXMatrix4x4& out);

		/**
		* 根据缩放计算输出矩阵
		* @param	scale  缩放值
		* @param	out 输出矩阵
		*/
		static void createScaling(const HXVector3& scale, HXMatrix4x4& out);

		/**
		* 计算两个矩阵的乘法
		* @param	left left矩阵
		* @param	right  right矩阵
		* @param	out  输出矩阵
		*/
		static void multiply(HXMatrix4x4& left, HXMatrix4x4& right, HXMatrix4x4& out);

		/**
		* 从四元数计算旋转矩阵
		* @param	rotation 四元数
		* @param	out 输出矩阵
		*/
		static void createFromQuaternion(const HXQuaternion& rotation, HXMatrix4x4& out);

		/**
		* 计算仿射矩阵
		* @param	trans 平移
		* @param	rot 旋转
		* @param	scale 缩放
		* @param	out 输出矩阵
		*/
		static void createAffineTransformation(const HXVector3& trans, const HXQuaternion& rot, const HXVector3& scale, HXMatrix4x4& out);
		
		/**
		*  计算观察矩阵
		* @param	eye 视点位置
		* @param	center 视点目标
		* @param	up 向上向量
		* @param	out 输出矩阵
		*/
		static void createLookAt(const HXVector3& eye, const HXVector3& target, const HXVector3& up, HXMatrix4x4& out);

		/**
		* 计算透视投影矩阵。
		* @param	fov  视角。
		* @param	aspect 横纵比。
		* @param	near 近裁面。
		* @param	far 远裁面。
		* @param	out 输出矩阵。
		*/
		static void createPerspective(float fov, float aspect, float near, float far, HXMatrix4x4& out);

		/**
		* 计算正交投影矩阵。
		* @param	left 视椎左边界。
		* @param	right 视椎右边界。
		* @param	bottom 视椎底边界。
		* @param	top 视椎顶边界。
		* @param	near 视椎近边界。
		* @param	far 视椎远边界。
		* @param	out 输出矩阵。
		*/
		static void createOrthoOffCenterRH(float left, float right, float bottom, float top, float near, float far, HXMatrix4x4& out);

		/**矩阵元素数组*/
		float elements[16];

		/**
		* 创建一个 <code>Matrix4x4</code> 实例。
		* @param	4x4矩阵的各元素
		*/
		HXMatrix4x4(float m11 = 1, float m12 = 0, float m13 = 0, float m14 = 0
			, float m21 = 0, float m22 = 1, float m23 = 0, float m24 = 0
			, float m31 = 0, float m32 = 0, float m33 = 1, float m34 = 0
			, float m41 = 0, float m42 = 0, float m43 = 0, float m44 = 1);

		float getElementByRowColumn(int row, int column);

		void setElementByRowColumn(int row, int column, float value);

		/**
		* 判断两个4x4矩阵的值是否相等。
		* @param	other 4x4矩阵
		*/
		bool equalsOtherMatrix(const HXMatrix4x4& other) const;

		/**
		* 分解矩阵为平移向量、旋转四元数、缩放向量。
		* @param	translation 平移向量。
		* @param	rotation 旋转四元数。
		* @param	scale 缩放向量。
		* @return 是否分解成功。
		*/
		bool decomposeTransRotScale(HXVector3& translation, HXQuaternion& rotation, HXVector3& scale);

		/**
		* 分解矩阵为平移向量、旋转矩阵、缩放向量。
		* @param	translation 平移向量。
		* @param	rotationMatrix 旋转矩阵。
		* @param	scale 缩放向量。
		* @return 是否分解成功。
		*/
		bool decomposeTransRotMatScale(HXVector3& translation, HXMatrix4x4& rotationMatrix, HXVector3& scale);

		/**
		* 分解旋转矩阵的旋转为YawPitchRoll欧拉角。
		* @param	out float yaw
		* @param	out float pitch
		* @param	out float roll
		* @return
		*/
		void decomposeYawPitchRoll(HXVector3& yawPitchRoll);

		/**归一化矩阵 */
		void normalize();

		/**计算矩阵的转置矩阵*/
		HXMatrix4x4& transpose();

		/**
		* 计算一个矩阵的逆矩阵
		* @param	out 输出矩阵
		*/
		void invert(HXMatrix4x4& out);

		/**设置矩阵为单位矩阵*/
		void identity();

		static void translation(const HXVector3& v3, HXMatrix4x4& out);

		/**
		* 获取平移向量。
		* @param	out 平移向量。
		*/
		void getTranslationVector(HXVector3& out) const;
		
		/**
		* 设置平移向量。
		* @param	translate 平移向量。
		*/
		void setTranslationVector(const HXVector3& translate);

		/**
		* 获取前向量。
		* @param	out 前向量。
		*/
		void getForward(HXVector3& out) const;

		/**
		* 设置前向量。
		* @param	forward 前向量。
		*/
		void setForward(const HXVector3& forward);


	private:
		static HXMatrix4x4 _tempMatrix4x4;
		static HXVector3 _tempVector0;
		static HXVector3 _tempVector1;
		static HXVector3 _tempVector2;
		static HXQuaternion _tempQuaternion;
	};
}