#include "..\include\HXGLTexture.h"
#include "png.h"
#include "vermilion.h"
#include <algorithm>
#include "HXGLLoadPNG.h"

namespace HX3D
{
	HXGLTexture::HXGLTexture(EMatPropertyType matType, std::string strTextureFile)
	{
		texObj = 0;
		size_t size = strTextureFile.length();
		std::string type = strTextureFile.substr(size - 3);
		transform(type.begin(), type.end(), type.begin(), ::tolower);
		if (type == "dds")
		{
			if (matType == MPT_TEXTURE)
			{
				texObj = LoadDDSTexture(strTextureFile.c_str());
			}
			else if (matType == MPT_CUBEMAP)
			{
				texObj = LoadDDSTextureCubeMap(strTextureFile.c_str());
			}
		}
		else if (type == "png")
		{
			if (matType == MPT_TEXTURE)
			{
				texObj = LoadPNGTexture(strTextureFile.c_str());
			}
			else if (matType == MPT_CUBEMAP)
			{
				texObj = LoadPNGTextureCubeMap(strTextureFile.c_str());
			}
		}
	}

	HXGLTexture::~HXGLTexture()
	{
		if (texObj)
		{
			glDeleteTextures(1, &texObj);
		}
	}

	GLuint HXGLTexture::LoadPNGTexture(const char *filename)
	{
		return HXGLLoadPNG::vglLoadPNGTexture(filename);
	}

	GLuint HXGLTexture::LoadPNGTextureCubeMap(const char *filename)
	{
		return HXGLLoadPNG::vglLoadPNGTextureCubeMap(filename);
	}

	GLuint HXGLTexture::LoadDDSTexture(const char *filename)
	{
		return vglLoadTexture(filename, 0, NULL);
	}

	GLuint HXGLTexture::LoadDDSTextureCubeMap(const char *filename)
	{
		return 0;
	}
}