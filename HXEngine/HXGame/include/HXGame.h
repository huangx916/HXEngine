#pragma once
#include "HXPaintListener.h"
#include "HXInputListener.h"

using namespace HX3D;
class HXGame : public HXPaintListener, public HXInputListener 
{
public:
	HXGame();
	~HXGame();

	void CreateGameScene();
	//virtual void OnUpdate();
	virtual void OnPaint();

	virtual void OnKeyDown(int msg);
	virtual void OnKeyUp(int msg);
};

