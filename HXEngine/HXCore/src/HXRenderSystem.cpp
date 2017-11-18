#include "..\include\HXRenderSystem.h"

namespace HX3D
{
	HXDisplayListener* HXRenderSystem::m_pDisplayListener = NULL;
	/*int HXRenderSystem::gCurScreenWidth = SCREEN_WIDTH;
	int HXRenderSystem::gCurScreenHeight = SCREEN_HEIGHT;
	float HXRenderSystem::gAspect = (float)gCurScreenHeight / (float)gCurScreenWidth;*/
	HXRenderSystem::HXRenderSystem()
	{
	}


	HXRenderSystem::~HXRenderSystem()
	{
	}

	void HXRenderSystem::CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen)
	{

	}

	void HXRenderSystem::SetDisplayListener(HXDisplayListener* pDisplayListener)
	{
		m_pDisplayListener = pDisplayListener;
	}
	
}
