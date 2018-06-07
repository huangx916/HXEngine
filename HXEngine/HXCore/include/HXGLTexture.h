#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "vgl.h"

namespace HX3D
{
	class HXGLTexture : public HXITexture
	{
	public:
		HXGLTexture(std::string strTextureFile);
		~HXGLTexture();

		// PNG
		GLuint LoadPNGTexture(const char *filename);
		
		// DDS
		GLuint LoadDDSTexture(const char *filename);


		// 具体纹理数据保存在显存上了，系统内存不需要再保存一份
		GLuint texId;
	};
}


