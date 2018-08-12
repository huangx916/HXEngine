#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXIDisplayListener
	{
	public:
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight) {};
		virtual void OnKeyboard(unsigned char key, int x, int y) {};
		virtual void OnMouseMove(int nButton, int deltaX, int deltaY) {};
		virtual void OnMouseWheel(float fDistance) {};
	};
}
