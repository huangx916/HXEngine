#include "..\include\HXGLTexture.h"
#include "png.h"
#include "vermilion.h"
#include <algorithm>
#include "HXGLLoadPNG.h"

namespace HX3D
{
	HXGLTexture::HXGLTexture(std::string strTextureFile)
	{
		size_t size = strTextureFile.length();
		std::string type = strTextureFile.substr(size - 3);
		transform(type.begin(), type.end(), type.begin(), ::tolower);
		if (type == "dds")
		{
			texId = LoadDDSTexture(strTextureFile.c_str());
		}
		else if (type == "png")
		{
			texId = LoadPNGTexture(strTextureFile.c_str());
		}
	}

	HXGLTexture::~HXGLTexture()
	{
		if (texId)
		{
			glDeleteTextures(1, &texId);
		}
	}

	GLuint HXGLTexture::LoadPNGTexture(const char *filename)
	{
		return HXGLLoadPNG::vglLoadPNGTexture(filename);
	}

	GLuint HXGLTexture::LoadDDSTexture(const char *filename)
	{
		return vglLoadTexture(filename, 0, NULL);
	}
}