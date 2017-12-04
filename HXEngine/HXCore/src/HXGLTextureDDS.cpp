#include "..\include\HXGLTextureDDS.h"

namespace HX3D
{
	HXGLTextureDDS::HXGLTextureDDS(std::string strDDSFile)
	{
		//tex->texId = vglLoadTexture((strDDSFile + ".dds").c_str(), 0, &(mImageData));
		texId = vglLoadTexture((strDDSFile + ".dds").c_str(), 0, 0);
	}

	HXGLTextureDDS::~HXGLTextureDDS()
	{
	}
}
