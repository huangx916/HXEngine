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
	//-----------------------------------------------------------------------------------
	// CONSTANT VALUE
	//-----------------------------------------------------------------------------------
	struct {
		int32_t pixel_format;
		int32_t internel_format;
		int32_t data_format;
		int32_t data_type;
		int32_t bpp;
	} kGLPixelFormatTbl[] = {
		{ TPFT_R8G8B8, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, 3 },
		{ TPFT_A8R8G8B8, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4 },
		{ TPFT_R8G8B8A8, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4 },
		{ TPFT_R16G16, GL_RG16, GL_RG, GL_UNSIGNED_SHORT, 4 },
		{ TPFT_G16R16, GL_RG16, GL_RG, GL_UNSIGNED_SHORT, 4 },
		{ TPFT_R16G16B16F, GL_RGB16F, GL_RGB, GL_FLOAT, 3 },
		{ TPFT_R16G16B16A16F, GL_RGBA16, GL_RGBA, GL_UNSIGNED_SHORT, 8 },
		{ TPFT_R32G32B32A32F, GL_RGBA32F, GL_RGBA, GL_FLOAT, 16 },
	};
	static_assert(HX_ARRAY_SIZE(kGLPixelFormatTbl) == TPFT_UNKOWN, "");

	HXGLTexture::HXGLTexture() 
		: texName("")
		, texObj(-1)
		//, texTexID(-1)
		, texType(TEX_NONE)
		, texFormat(FMT_R8G8B8A8)
		, texWidth(0)
		, texHeight(0)
		, texDepth(0)
		, texBPP(0)
		
	{

	}

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

	void HXGLTexture::CreateCubeBy6Texture2D(const char* texture_name, bool enableMipmapping)
	{
		GLuint tex_obj = 0;
		glGenTextures(1, &tex_obj);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_obj);

		std::string suffix[6] = { "_right","_left","_bottom","_top","_front","_back" };
		int8_t* texture_data = NULL;
		int32_t texture_width = 0;
		int32_t texture_height = 0;
		int32_t texture_type = TT_UNKOWN;
		int32_t texture_pixel_format = TPFT_UNKOWN;
		for (int i = 0; i < 6; ++i)
		{
			std::string tex_name = texture_name;
			tex_name.insert(tex_name.length() - 4, suffix[i]);
			if (HXTextureReader::ReadTexture(tex_name.c_str(), &texture_data, texture_width, texture_height, texture_type, texture_pixel_format))
			{
				for (int32_t j = 0; j < HX_ARRAY_SIZE(kGLPixelFormatTbl); j++) 
				{
					if (kGLPixelFormatTbl[j].pixel_format == texture_pixel_format) 
					{
						GLint alignment;
						glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
						glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, kGLPixelFormatTbl[j].internel_format, texture_width, texture_height, 0, kGLPixelFormatTbl[j].data_format, kGLPixelFormatTbl[j].data_type, texture_data);
						glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
						break;
					}
				}
				HXTextureReader::ReleaseData(&texture_data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (enableMipmapping) {
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else {
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		texObj = tex_obj;
		texName = texture_name;
		texType = TEX_CUBE;
		texWidth = texture_width;
		texHeight = texture_height;
		texDepth = 0;
		SetTexturePixelFormat(this, texture_pixel_format);
	}

	void HXGLTexture::CreateGLTexture2D(int32_t tex_obj, int32_t width, int32_t height, int8_t* texture_data, int32_t texture_pixel_format, bool enableMipmapping)
	{
		for (int32_t i = 0; i < HX_ARRAY_SIZE(kGLPixelFormatTbl); i++) 
		{
			if (kGLPixelFormatTbl[i].pixel_format == texture_pixel_format) 
			{
				glBindTexture(GL_TEXTURE_2D, tex_obj);
				if (kGLPixelFormatTbl[i].data_type == GL_FLOAT) 
				{
					float* data = reinterpret_cast<float*>(texture_data);
					glTexImage2D(GL_TEXTURE_2D, 0, kGLPixelFormatTbl[i].internel_format, width, height, 0, kGLPixelFormatTbl[i].data_format, kGLPixelFormatTbl[i].data_type, data);
				}
				else 
				{
					glTexImage2D(GL_TEXTURE_2D, 0, kGLPixelFormatTbl[i].internel_format, width, height, 0, kGLPixelFormatTbl[i].data_format, kGLPixelFormatTbl[i].data_type, texture_data);
				}

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				if (enableMipmapping) 
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					glGenerateMipmap(GL_TEXTURE_2D);
				}
				else 
				{
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				}
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glBindTexture(GL_TEXTURE_2D, 0);
				break;
			}
		}
	}

	void HXGLTexture::CreateGLTextureCube(int32_t tex_obj, int32_t width, int32_t height, int8_t* texture_data, int32_t texture_pixel_format, bool enableMipmapping)
	{
		// Warning: The cube map's 6 texture must be square and have the same size
		if (width > 0 && height > 0 && width == height) {
			glBindTexture(GL_TEXTURE_CUBE_MAP, tex_obj);

			for (int32_t i = 0; i < HX_ARRAY_SIZE(kGLPixelFormatTbl); i++) {
				if (kGLPixelFormatTbl[i].pixel_format == texture_pixel_format) {
					int32_t gl_faces[] = {
						GL_TEXTURE_CUBE_MAP_POSITIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,  // TODO: Just flip y, i do not know why
						GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
						GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
						GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
					};
					for (int32_t j = 0; j < 6; j++) {
						glTexImage2D(gl_faces[j], 0, kGLPixelFormatTbl[i].internel_format, width, height, 0, kGLPixelFormatTbl[i].data_format, kGLPixelFormatTbl[i].data_type, texture_data + j * height * width * kGLPixelFormatTbl[i].bpp);
					}
					break;
				}
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::CreateGLTexture3D()
	{
		// TODO:
	}

	void HXGLTexture::SetTexturePixelFormat(HXGLTexture* texture, int32_t texture_pixel_format)
	{
		if (texture != NULL) {
			struct {
				TEXTURE_PIXEL_FORMAT_TYPE pixel_format_from_file;
				TextureFormat pixel_format_from_lib;
				int32_t bytes_per_pixel;
			} pixel_format[] = {
				{ TPFT_R8G8B8, FMT_R8G8B8, 3 },
				{ TPFT_A8R8G8B8, FMT_R8G8B8A8, 4 },
				{ TPFT_R8G8B8A8, FMT_R8G8B8A8, 4 },
				{ TPFT_R16G16, FMT_R16G16, 4 },
				{ TPFT_G16R16, FMT_R16G16, 4 },
				{ TPFT_R16G16B16F, FMT_R16G16B16F, 3 },
				{ TPFT_R16G16B16A16F, FMT_R16G16B16A16F, 8 },
				{ TPFT_R32G32B32A32F, FMT_R32G32B32A32F, 16 },
			};
			static_assert(HX_ARRAY_SIZE(pixel_format) == TPFT_UNKOWN, "");

			for (int32_t i = 0; i < HX_ARRAY_SIZE(pixel_format); i++) {
				if (pixel_format[i].pixel_format_from_file == texture_pixel_format) {
					texture->texFormat = pixel_format[i].pixel_format_from_lib;
					texture->texBPP = pixel_format[i].bytes_per_pixel;
					break;
				}
			}
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::Create(int32_t width, int32_t height, bool enableMipmapping)
	{
		if (width > 0 && height > 0) {
			int32_t tex_id = 0;
			glGenTextures(1, reinterpret_cast<GLuint*>(&tex_id));
			glBindTexture(GL_TEXTURE_2D, tex_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			texName = "DefaultEmpty";
			texObj = tex_id;
			texType = TEX_2D;
			texFormat = FMT_R8G8B8A8;
			texWidth = width;
			texHeight = height;
			texBPP = 4;
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::CreateFloat32Texture(int32_t width, int32_t height, bool enableMipmapping)
	{
		if (width > 0 && height > 0) {
			int32_t tex_id = 0;
			glGenTextures(1, reinterpret_cast<GLuint*>(&tex_id));
			glBindTexture(GL_TEXTURE_2D, tex_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

			texName = "DefaultEmpty";
			texObj = tex_id;
			texType = TEX_2D;
			texFormat = FMT_R32G32B32A32F;
			texWidth = width;
			texHeight = height;
			texBPP = 16;
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::CreateFloat32DepthTexture(int32_t width, int32_t height, bool enableMipmapping)
	{
		if (width > 0 && height > 0) {
			int32_t tex_id = 0;
			glGenTextures(1, reinterpret_cast<GLuint*>(&tex_id));
			glBindTexture(GL_TEXTURE_2D, tex_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			texName = "DefaultEmpty";
			texObj = tex_id;
			texType = TEX_2D;
			texFormat = FMT_DEPTH32F;
			texWidth = width;
			texHeight = height;
			texDepth = 0;
			texBPP = 4;
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::CreateFloat32CubeTexture(int32_t width, int32_t height, bool enableMipmapping)
	{
		// Warning: The cube map's 6 texture must be square and have the same size
		if (width > 0 && height > 0 && width == height) {
			int32_t tex_id = 0;
			glGenTextures(1, reinterpret_cast<GLuint*>(&tex_id));
			glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);

			for (int32_t i = 0; i < 6; i++) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

			texName = "DefaultEmpty";
			texObj = tex_id;
			texType = TEX_CUBE;
			texFormat = FMT_R32G32B32A32F;
			texWidth = width;
			texHeight = height;
			texDepth = 0;
			texBPP = 16;
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::CreateFloat16CubeTexture(int32_t width, int32_t height, bool enableMipmapping)
	{
		// Warning: The cube map's 6 texture must be square and have the same size
		if (width > 0 && height > 0 && width == height) {
			int32_t tex_id = 0;
			glGenTextures(1, reinterpret_cast<GLuint*>(&tex_id));
			glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);

			for (int32_t i = 0; i < 6; i++) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT, NULL);
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

			texName = "DefaultEmpty";
			texObj = tex_id;
			texType = TEX_CUBE;
			texFormat = FMT_R16G16B16A16F;
			texWidth = width;
			texHeight = height;
			texDepth = 0;
			texBPP = 8;
		}
		else {
			assert(false);
		}
	}

	void HXGLTexture::CreateFloat323DTexture(int32_t width, int32_t height, int32_t depth, bool enableMipmapping)
	{
		if (width > 0 && height > 0 && depth > 0) {
			int32_t tex_id = 0;
			glGenTextures(1, reinterpret_cast<GLuint*>(&tex_id));
			glBindTexture(GL_TEXTURE_3D, tex_id);

			glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, width, height, depth, 0, GL_RGBA, GL_FLOAT, NULL);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			if (enableMipmapping) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

			texName = "DefaultEmpty";
			texObj = tex_id;
			texType = TEX_3D;
			texFormat = FMT_R32G32B32A32F;
			texWidth = width;
			texHeight = height;
			texDepth = depth;
			texBPP = 16;
		}
		else {
			assert(false);
		}
	}
}