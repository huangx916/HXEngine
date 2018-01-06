#include "..\include\HXRenderSystem.h"
#include "HXDisplayListener.h"

namespace HX3D
{
	HXDisplayListener* HXRenderSystem::m_pDisplayListener = NULL;
	int HXRenderSystem::gCurScreenWidth = SCREEN_WIDTH;
	int HXRenderSystem::gCurScreenHeight = SCREEN_HEIGHT;
	//float HXRenderSystem::gAspect = (float)gCurScreenHeight / (float)gCurScreenWidth;
	int HXRenderSystem::mLastX = 0;
	int HXRenderSystem::mLastY = 0;
	int HXRenderSystem::mButtonDown = -1;
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
	
	void HXRenderSystem::Reshape(int nWidth, int nHeight)
	{
		gCurScreenWidth = nWidth;
		gCurScreenHeight = nHeight;
		//gAspect = (float)gCurScreenHeight / (float)gCurScreenWidth;
		if (m_pDisplayListener)
		{
			m_pDisplayListener->OnViewPortResize(nWidth, nHeight);
		}
	}

	void HXRenderSystem::Keyboard(unsigned char key, int x, int y)
	{
		if (m_pDisplayListener)
		{
			m_pDisplayListener->OnKeyboard(key, x, y);
		}
	}

	void HXRenderSystem::Mouse(int button, int state, int x, int y)
	{
		mLastX = x;
		mLastY = y;
		if (button == 3)
		{
			// mouse wheel up
			if (m_pDisplayListener)
			{
				m_pDisplayListener->OnMouseWheel(1);
			}
		}
		if (button == 4)
		{
			// mouse wheel down
			if (m_pDisplayListener)
			{
				m_pDisplayListener->OnMouseWheel(-1);
			}
		}

		//std::cout << button << std::endl;
		//std::cout << state << std::endl;

		if (button == 0)
		{
			if (state == 0)
			{
				// ×ó¼ü°´ÏÂ
				mButtonDown = 0;
			}
			else if (state == 1)
			{
				// ×ó¼üµ¯Æð
				mButtonDown = -1;
			}
		}
		if (button == 2)
		{
			if (state == 0)
			{
				// ÓÒ¼ü°´ÏÂ
				mButtonDown = 2;
			}
			else if (state == 1)
			{
				// ÓÒ¼üµ¯Æð
				mButtonDown = -1;
			}
		}
	}

	void HXRenderSystem::MouseMotion(int x, int y)
	{
		if (m_pDisplayListener)
		{
			m_pDisplayListener->OnMouseMove(mButtonDown, mLastX - x, mLastY - y);
		}
		mLastX = x;
		mLastY = y;
	}
}
