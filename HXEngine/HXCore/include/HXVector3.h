#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXVector3
	{
	public:
		HXVector3();
		~HXVector3();

		float x() { return elements[0]; }
		void x(float v) { elements[0] = v; }
		float y() { return elements[1]; }
		void y(float v) { elements[1] = v; }
		float z() { return elements[2]; }
		void z(float v) { elements[2] = v; }


		/**
		* 归一化三维向量。
		* @param	s 源三维向量。
		* @param	out 输出三维向量。
		*/
		static void normalize(const HXVector3& s, HXVector3& out);

		/**
		* 求两个三维向量的差。
		* @param	a  left三维向量。
		* @param	b  right三维向量。
		* @param	o out 输出向量。
		*/
		static void subtract(const HXVector3& a, const HXVector3& b, HXVector3& o);

		/**
		* 求两个三维向量的叉乘。
		* @param	a left向量。
		* @param	b right向量。
		* @param	o 输出向量。
		*/
		static void cross(const HXVector3& a, const  HXVector3& b, HXVector3& o);

		/**
		* 求两个三维向量的点积。
		* @param	a left向量。
		* @param	b right向量。
		* @return   点积。
		*/
		static float dot(const HXVector3& a, const HXVector3& b);





		/**三维向量元素数组*/
		float elements[3];
	};
}