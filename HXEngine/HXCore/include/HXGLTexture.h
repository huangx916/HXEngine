#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "vgl.h"
#include "HXLoadConfigMat.h"

namespace HX3D
{
	class HXGLTexture : public HXITexture
	{
	public:
		HXGLTexture(EMatPropertyType matType, std::string strTextureFile);
		~HXGLTexture();

		// PNG
		GLuint LoadPNGTexture(const char *filename);
		GLuint LoadPNGTextureCubeMap(const char *filename);
		
		// DDS
		GLuint LoadDDSTexture(const char *filename);
		GLuint LoadDDSTextureCubeMap(const char *filename);

		// 
		GLuint CreateFloat32Texture(int32_t width, int32_t height, bool enableMipmapping = true);

		// 具体纹理数据保存在显存上了，系统内存不需要再保存一份
		GLuint texId;
	};
}


