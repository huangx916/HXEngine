#pragma once
#include "HXIDisplayListener.h"

using namespace HX3D;
class HXGame : public HXIDisplayListener
{
public:
	HXGame();
	~HXGame();

	void CreateGameScene();
	virtual void OnDisplay(bool shadow);
	virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight);
	virtual void OnKeyboard(unsigned char key, int x, int y);
	virtual void OnMouseMove(int nButton, int deltaX, int deltaY);
	virtual void OnMouseWheel(float fDistance);
};

