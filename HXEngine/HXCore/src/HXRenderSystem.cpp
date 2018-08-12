#include "..\include\HXRenderSystem.h"
#include "HXIDisplayListener.h"
#include "HXSceneManager.h"

namespace HX3D
{
	HXIDisplayListener* HXRenderSystem::m_pDisplayListener = NULL;
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

	void HXRenderSystem::SetDisplayListener(HXIDisplayListener* pDisplayListener)
	{
		m_pDisplayListener = pDisplayListener;
	}
	
	ERenderSystem HXRenderSystem::GetRenderSystemType()
	{
		return m_eRenderSystemType;
	}

	void HXRenderSystem::SetRenderSystemType(ERenderSystem rs)
	{
		m_eRenderSystemType = rs;
	}

	void HXRenderSystem::Reshape(int nWidth, int nHeight)
	{
		gCurScreenWidth = nWidth;
		gCurScreenHeight = nHeight;
		//gAspect = (float)gCurScreenHeight / (float)gCurScreenWidth;
		if (m_pDisplayListener)
		{
			m_pDisplayListener->OnViewPortResize(nWidth, nHeight);
			HXSceneManager::GetInstance()->OnViewPortResize(nWidth, nHeight);
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
		// std::cout << button << std::endl;
		// glut库不支持鼠标滚轮，freeglut库支持
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
				// 左键按下
				mButtonDown = 0;
			}
			else if (state == 1)
			{
				// 左键弹起
				mButtonDown = -1;
			}
		}
		if (button == 2)
		{
			if (state == 0)
			{
				// 右键按下
				mButtonDown = 2;
			}
			else if (state == 1)
			{
				// 右键弹起
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
