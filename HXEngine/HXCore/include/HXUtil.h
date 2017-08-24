#pragma once
#include "HXCommon.h"
#include <sstream>

namespace HX3D
{
	inline std::string FloatToString(float fIN)
	{
		std::stringstream ss;
		ss << fIN;
		std::string strOUT;
		ss >> strOUT;
		return strOUT;
	}

	inline bool EqualFloat(float lhs, float rhs)
	{
		return abs(lhs - rhs) <= EPSILON_E6;
	}
}