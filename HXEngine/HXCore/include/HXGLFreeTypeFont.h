#pragma once
#include "HXCommon.h"
#include "HXIFreeTypeFont.h"

namespace HX3D
{
	class HXGLFreeTypeFont : public HXIFreeTypeFont
	{
	public:
		HXGLFreeTypeFont();
		~HXGLFreeTypeFont();

		virtual void Initialize(const char* fontFile, int fontSize);
		virtual void BeginText();
		virtual void _DrawText(float x, float y, const wchar_t* text, const HXCOLOR& color);
		virtual void EndText();

	private:
		HXCharacter* GetCharacter(wchar_t ch);
	
		unsigned    _textureId;
		//unsigned	_samplerId;	使用默认采样器
		unsigned	_vaoId;
		// TODO: 是否不要每帧赋值传输不变的数据,在外层_DrawText时用renderlist管理起来,如何删除（用键值对？）
		unsigned	_vboId;
		unsigned	_programId;
	};
}


