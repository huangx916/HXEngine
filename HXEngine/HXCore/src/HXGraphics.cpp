#include "..\include\HXGraphics.h"
#include <Windows.h>

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

	// 设置刷新区域
	::SetRect(&mBufferRect, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	mPenHandle = ::CreatePen(PS_SOLID, 1, RGB(255,255,255));
	::SelectObject(mBufferHDC, mPenHandle);

	mBrushHandle = ::CreateSolidBrush(RGB(0,0,0));
	::SelectObject(mBufferHDC, mBrushHandle);

}

void HXGraphics::ShutDownGraphics()
{
	::DeleteObject(mBufferHDC);
	::DeleteObject(mBufferHandle);
	::DeleteObject(mPenHandle);
	::DeleteObject(mBrushHandle);
}

void HXGraphics::ClearBuffer()
{
	::FillRect(mBufferHDC, &mBufferRect, mBrushHandle);
}

void HXGraphics::SwapBuffer(HDC hdc)
{
	::BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, mBufferHDC, 0, 0, SRCCOPY);
}

void HXGraphics::DrawLine(int nFromX, int nFromY, int nToX, int nToY, COLORREF col)
{
	HPEN hPen;
	HPEN hPenOld;
	hPen = CreatePen(PS_SOLID, 3, col);
	hPenOld = (HPEN)SelectObject(mBufferHDC, hPen);
	MoveToEx(mBufferHDC, nFromX, nFromY, NULL);
	LineTo(mBufferHDC, nToX, nToY);
	SelectObject(mBufferHDC, hPenOld);
	DeleteObject(hPen);
}

void HXGraphics::DrawString(std::string str, int nFromX, int nFromY, COLORREF col)
{
	SetTextColor(mBufferHDC, RGB(255, 0, 0));
	//SetBkColor(mBufferHDC, RGB(0, 255, 0));
	//SetBkMode(mBufferHDC, TRANSPARENT);
	TextOut(mBufferHDC, 200, 100, str.c_str(), str.length());
}