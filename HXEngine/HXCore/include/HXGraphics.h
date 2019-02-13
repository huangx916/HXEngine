#pragma once
#include <Windows.h>
#include <string>
#include "HXCommon.h"

namespace HX3D
{
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

		void SetBufferPixel(int nX, int nY, float fZ, const HXColor& col);
		// UI
		void DrawLine(int nFromX, int nFromY, int nToX, int nToY, const HXColor& col = HXColor(255,255,255));
		void DrawString(std::string str, int nFromX, int nFromY, const HXColor& frontCol = HXColor(255,255,255), const HXColor& backCol = HXColor(0,0,0));

		bool CheckZ(int nX, int nY, float fZ);
	private:

		HDC mBufferHDC;			//后备缓冲DC
		HBITMAP mBufferHandle;	//后备缓冲
		// DIBSECTION mDIBSection;	
		unsigned char* m_pBufferData;	// 指向后备缓冲数据
		int mWidthBytes;	// 后备缓冲每行所占字节数
		// HPEN mPenHandle;
		HBRUSH mBrushHandle;
		RECT mBufferRect;
		float* m_pZBuffer;
	};
}

