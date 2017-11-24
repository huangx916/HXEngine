#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "vermilion.h"

namespace HX3D
{ 
	class HXGLTextureDDS : public HXITexture
	{
	public:
		HXGLTextureDDS();
		~HXGLTextureDDS();

		vglImageData mImageData;
		GLuint texId;
	};
}


