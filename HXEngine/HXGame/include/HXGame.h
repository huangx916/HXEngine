#pragma once
#include "DiscardHXPaintListener.h"
#include "DiscardHXInputListener.h"
#include "HXIDisplayListener.h"

using namespace HX3D;
class HXGame : /*public HXPaintListener, public HXInputListener , */public HXIDisplayListener
{
public:
	HXGame();
	~HXGame();

	void CreateGameScene();
	//virtual void OnUpdate();
	//virtual void OnPaint();
	virtual void OnDisplay(bool shadow);
	virtual void OnViewPortResize(int nScreenWidth, int nScreenHeight);
	virtual void OnKeyboard(unsigned char key, int x, int y);
	virtual void OnMouseMove(int nButton, int deltaX, int deltaY);
	virtual void OnMouseWheel(float fDistance);
	//virtual void OnKeyDown(int msg);
	//virtual void OnKeyUp(int msg);
};

