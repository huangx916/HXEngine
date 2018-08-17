#pragma once
#include "HXCommon.h"
#include "HXVector3.h"

namespace HX3D
{
	class HXMatrix4x4;
	class HXQuaternion
	{
	public:
		HXQuaternion();
		~HXQuaternion();

		/**
		*  从欧拉角生成四元数（顺序为Yaw、Pitch、Roll）
		* @param	yaw yaw值
		* @param	pitch pitch值
		* @param	roll roll值
		* @param	out 输出四元数
		*/
		static void createFromYawPitchRoll(float yaw, float pitch, float roll, HXQuaternion& out);

		/**
		*设置四元数为单位算数
		* @param out  输出四元数
		*/
		void identity();

		/**
		*  从旋转矩阵计算四元数
		* @param	mat 旋转矩阵
		* @param	out  输出四元数
		*/
		static void createFromMatrix4x4(const HXMatrix4x4& mat, HXQuaternion& out);

		/**四元数元素数组*/
		float elements[4];
	};
}