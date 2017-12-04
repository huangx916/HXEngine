#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "vermilion.h"

namespace HX3D
{ 
	class HXGLTextureDDS : public HXITexture
	{
	public:
		HXGLTextureDDS(std::string strDDSFile);
		~HXGLTextureDDS();

		// 具体纹理数据保存在显存上了，系统内存不需要再保存一份
		//vglImageData mImageData;
		GLuint texId;
	};
}


