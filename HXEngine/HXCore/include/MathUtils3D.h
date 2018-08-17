#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class MathUtils3D
	{
	public:

		/**单精度浮点(float)零的容差*/
		static const float zeroTolerance;
		/**浮点数默认最大值*/
		static const float MaxValue;
		/**浮点数默认最小值*/
		static const float MinValue;
	
		MathUtils3D();
		~MathUtils3D();

		/**
		* 是否在容差的范围内近似于0
		* @param  判断值
		* @return  是否近似于0
		*/
		static bool isZero(float v)
		{
			return abs(v) < zeroTolerance;
		}

		/**
		* 两个值是否在容差的范围内近似相等Sqr Magnitude
		* @param  判断值
		* @return  是否近似于0
		*/
		static bool nearEqual(float n1, float n2)
		{
			if (isZero(n1 - n2))
				return true;
			return false;
		}

		static float fastInvSqrt(float value)
		{
			if (isZero(value))
				return value;
			return 1.0 / sqrt(value);
		}
	};
}