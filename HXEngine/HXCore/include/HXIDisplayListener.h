#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXIDisplayListener
	{
	public:
		virtual void OnDisplay() = 0;
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight) = 0;
		virtual void OnKeyboard(unsigned char key, int x, int y) = 0;
		virtual void OnMouseMove(int nButton, int deltaX, int deltaY) = 0;
		virtual void OnMouseWheel(float fDistance) = 0;
	};
}
