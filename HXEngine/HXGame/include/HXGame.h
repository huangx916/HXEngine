#pragma once
#include "HXPaintListener.h"
#include "HXInputListener.h"

class HXGame : public HXPaintListener, public HXInputListener 
{
public:
	HXGame();
	~HXGame();

	//virtual void OnUpdate();
	virtual void OnPaint();
};

