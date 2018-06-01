#include "..\include\HXGraphics.h"
#include <Windows.h>

namespace HX3D
{
	HXGraphics* HXGraphics::m_pInstance;

	HXGraphics::HXGraphics()
	{
	}

	//HXGraphics::~HXGraphics()
	//{
	//}

	void HXGraphics::InitGraphics()
	{
		mBufferHDC = ::CreateCompatibleDC(NULL);

		BITMAPINFO info = { 0 };
		info.bmiHeader.biSize = sizeof(info.bmiHeader);
		info.bmiHeader.biWidth = SCREEN_WIDTH;
		info.bmiHeader.biHeight = -SCREEN_HEIGHT;
		info.bmiHeader.biPlanes = 1;
		info.bmiHeader.biBitCount = 32;
		info.bmiHeader.biCompression = BI_RGB;
		info.bmiHeader.biSizeImage = SCREEN_WIDTH * SCREEN_HEIGHT * 32 / 8;

		void* pBits = NULL;
		mBufferHandle = ::CreateDIBSection(mBufferHDC, &info, DIB_RGB_COLORS, &pBits, NULL, 0);
		::SelectObject(mBufferHDC, mBufferHandle);
		
		DIBSECTION DIBSection;
		::GetObject(mBufferHandle, sizeof(DIBSECTION), &DIBSection);
		m_pBufferData = (unsigned char*)DIBSection.dsBm.bmBits;
		mWidthBytes = DIBSection.dsBm.bmWidthBytes;

		// 设置刷新区域
		::SetRect(&mBufferRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		// mPenHandle = ::CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
		// ::SelectObject(mBufferHDC, mPenHandle);

		mBrushHandle = ::CreateSolidBrush(RGB(128, 128, 128));
		::SelectObject(mBufferHDC, mBrushHandle);

		m_pZBuffer = new float[SCREEN_WIDTH * SCREEN_HEIGHT];
		memset(m_pZBuffer, 0, sizeof(float)*SCREEN_WIDTH*SCREEN_HEIGHT);

	}

	void HXGraphics::ShutDownGraphics()
	{
		::DeleteDC(mBufferHDC);
		::DeleteObject(mBufferHandle);
		// ::DeleteObject(mPenHandle);
		::DeleteObject(mBrushHandle);

		delete m_pZBuffer;
	}

	void HXGraphics::ClearBuffer()
	{
		::FillRect(mBufferHDC, &mBufferRect, mBrushHandle);
		memset(m_pZBuffer, 0, sizeof(float)*SCREEN_WIDTH*SCREEN_HEIGHT);
	}

	void HXGraphics::SwapBuffer(HDC hdc)
	{
		::BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mBufferHDC, 0, 0, SRCCOPY);
	}

	void HXGraphics::SetBufferPixel(int nX, int nY, float fZ, const HXCOLOR& col)
	{
		if (nX < 0 || nX > SCREEN_WIDTH-1 || nY < 0 || nY > SCREEN_HEIGHT-1)
		{
			return;
		}

		if (!CheckZ(nX, nY, fZ))
		{
			return;
		}

		unsigned char* pPixel = m_pBufferData + (mWidthBytes * nY);
		pPixel += nX * 4;
		// b g r a
		pPixel[0] = col.b;
		pPixel[1] = col.g;
		pPixel[2] = col.r;
		// TODO:ALPHA BLEND
		//pPixel[3] = col.a;
		pPixel[3] = 0;
	}

	void HXGraphics::DrawLine(int nFromX, int nFromY, int nToX, int nToY, const HXCOLOR& col)
	{
		HPEN hPen;
		HPEN hPenOld;
		hPen = CreatePen(PS_SOLID, 3, RGB(col.r,col.g,col.b));
		hPenOld = (HPEN)SelectObject(mBufferHDC, hPen);
		MoveToEx(mBufferHDC, nFromX, nFromY, NULL);
		LineTo(mBufferHDC, nToX, nToY);
		SelectObject(mBufferHDC, hPenOld);
		DeleteObject(hPen);
	}

	void HXGraphics::DrawString(std::string str, int nFromX, int nFromY, const HXCOLOR& frontCol, const HXCOLOR& backCol)
	{
		SetTextColor(mBufferHDC, RGB(frontCol.r, frontCol.g, frontCol.b));
		SetBkColor(mBufferHDC, RGB(backCol.r, backCol.g, backCol.b));
		//SetBkMode(mBufferHDC, TRANSPARENT);
		TextOut(mBufferHDC, nFromX, nFromY, str.c_str(), str.length());
	}

	bool HXGraphics::CheckZ(int nX, int nY, float fZ)
	{
		int nIndex = nY * SCREEN_WIDTH + nX;
		float divZ = 1.0f / fZ;
		if (divZ > m_pZBuffer[nIndex])
		{
			// 测试通过
			m_pZBuffer[nIndex] = divZ;
			return true;
		}
		else
		{
			return false;
		}
	}
}