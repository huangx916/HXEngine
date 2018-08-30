#include "..\include\HXGLTexture.h"
#include "png.h"
#include "vermilion.h"
#include <algorithm>
#include "HXGLLoadPNG.h"
#include "HXTextureReader.h"
#include"HXTextureInfo.h"
#include <assert.h>

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
		// TODO:
		return 0;
	}

	//------------------------------------------------------
	void HXGLTexture::Create(const char* texture_name, bool enableMipmapping)
	{
		int8_t* texture_data = NULL;
		int32_t texture_width = 0;
		int32_t texture_height = 0;
		int32_t texture_type = TT_UNKOWN;
		int32_t texture_pixel_format = TPFT_UNKOWN;
		if (HXTextureReader::ReadTexture(texture_name, &texture_data, texture_width, texture_height, texture_type, texture_pixel_format))
		{
			GLuint tex_obj = 0;
			glGenTextures(1, &tex_obj);

			if (texture_type == TT_2D) {
				CreateGLTexture2D(tex_obj, texture_width, texture_height, texture_data, texture_pixel_format, enableMipmapping);
			}
			else if (texture_type == TT_3D) {
				// TODO:
				//glBindTexture(GL_TEXTURE_3D, tex_obj);
				//glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, texture_width, texture_width, texture_width, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
				//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // TODO: Enable mipmap if needed
				//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				//glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				//glGenerateMipmap(GL_TEXTURE_3D);
				//glBindTexture(GL_TEXTURE_3D, 0);
			}
			else if (texture_type == TT_CUBE) {
				CreateGLTextureCube(tex_obj, texture_width, texture_height, texture_data, texture_pixel_format, enableMipmapping);
			}

			HXTextureReader::ReleaseData(&texture_data);

			texObj = tex_obj;
			//memcpy(tex->m_TexName, texture_name, strlen(texture_name));
			//tex->m_TexName[strlen(texture_name)] = 0;
			texName = texture_name;

			if (texture_type == TT_2D) {
				texType = TEX_2D;
				texWidth = texture_width;
				texHeight = texture_height;
				texDepth = 0;
				SetTexturePixelFormat(this, texture_pixel_format);
			}
			else if (texture_type == TT_3D) {
				//tex->m_Type = TEX_3D;
				//tex->m_Width = texture_width;
				//tex->m_Height = texture_width;
				//tex->m_Depth = texture_width;
			}
			else if (texture_type == TT_CUBE) {
				texType = TEX_CUBE;
				texWidth = texture_width;
				texHeight = texture_height;
				texDepth = 0;
				SetTexturePixelFormat(this, texture_pixel_format);
			}
			else {
				assert(false);
			}
		}
	}


	void HXGLTexture::CreateGLTexture2D(int32_t tex_obj, int32_t width, int32_t height, int8_t* texture_data, int32_t texture_pixel_format, bool enableMipmapping)
	{

	}

	void HXGLTexture::CreateGLTextureCube(int32_t tex_obj, int32_t width, int32_t height, int8_t* texture_data, int32_t texture_pixel_format, bool enableMipmapping)
	{

	}

	void HXGLTexture::SetTexturePixelFormat(HXGLTexture* texture, int32_t texture_pixel_format)
	{

	}
}