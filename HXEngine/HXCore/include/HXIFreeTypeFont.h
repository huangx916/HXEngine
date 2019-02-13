#pragma once
#include "HXCommon.h"

#include "ft2build.h"
#include "freetype/ftglyph.h"
#include <assert.h>

namespace HX3D
{
	class HXCharacter
	{
	public:
		HXCharacter()
		{
			x0 = 0;
			y0 = 0;
			x1 = 0;
			y1 = 0;
			offsetX = 0;
			offsetY = 0;
		}
		/**
		*   存储当前字符在纹理上的坐标位置
		*/

		unsigned int   x0 : 10;
		unsigned int   y0 : 10;
		unsigned int   x1 : 10;
		unsigned int   y1 : 10;
		unsigned int   offsetX : 10;
		unsigned int   offsetY : 10;
	};
	class HXIFreeTypeFont
	{
	public:
		HXIFreeTypeFont() {};
		virtual ~HXIFreeTypeFont() {};

		virtual void Initialize(const char* fontFile, int fontSize) = 0;
		virtual void BeginText() = 0;
		virtual void _DrawText(float x, float y, const wchar_t* text, const HXColor& color) = 0;
		virtual void EndText() = 0;

	protected:
		HXCharacter   _character[1 << 16];
		FT_Library  _library;
		FT_Face     _face;
		int         _yStart;
		int         _xStart;
		int         _fontSize;
	};
}