#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXGLFontBG
	{
	public:
		HXGLFontBG();
		~HXGLFontBG();

		void Initialize();
		void BeginRender();
		void Render();
		void EndRender();
		unsigned	_vaoId;
		unsigned	_vboId;
		unsigned	_programId;
	};
}