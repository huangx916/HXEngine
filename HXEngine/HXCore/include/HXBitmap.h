#pragma once
#include "HXCommon.h"
#include <Windows.h>

namespace HX3D
{
	extern HINSTANCE GInstance;

	class HXBitmap
	{
	public:
		HXBitmap();
		~HXBitmap();

		bool LoadBitmapFile(std::string strFileName);
		HXCOLOR GetPixel(int nX, int nY);
		int GetWidth() { return nWidth; }
		int GetHeight() { return nHeight; }
		HXCOLOR GetPixelRatio(float fX, float fY);

	private:
		int nWidth;
		int nHeight;
		int nPitch;
	
		HBITMAP		hBitmap;
		HDC			hBitmapDC;
		HXCOLOR*	 mPixels;
	};	
}
