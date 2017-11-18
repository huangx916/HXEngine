#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXDisplayListener
	{
	public:
		virtual void OnDisplay() = 0;
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight) = 0;
	};
}
