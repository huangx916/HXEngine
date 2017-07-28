#pragma once
#include <Windows.h>
#include <string>
#include "HXCommon.h"


class HXGraphics
{
private:
	// 单例模式
	static HXGraphics* m_pInstance;
	HXGraphics();	//单例模式构造函数是私有的,防止外部直接new

public:
	static HXGraphics* GetInstance()
	{
		if (NULL == m_pInstance)
		{
			m_pInstance = new HXGraphics();
		}
		return m_pInstance;
	}

	//~HXGraphics();

	void InitGraphics();
	void ShutDownGraphics();

	void ClearBuffer();
	void SwapBuffer(HDC hdc);

	void DrawLine(int nFromX, int nFromY, int nToX, int nToY, COLORREF col);
	void DrawString(std::string str, int nFromX, int nFromY, COLORREF col);

private:

	HDC mBufferHDC;			//后备缓冲DC
	HBITMAP mBufferHandle;	//后备缓冲
	HPEN mPenHandle;
	HBRUSH mBrushHandle;

	RECT mBufferRect;
};

