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
		HXGLTexture();
		~HXGLTexture();
		////////////////////////////////////////////////////////////////////////////
		// 已废弃，请使用Create和CreateCubeBy6Texture2D代替
		//HXGLTexture(EMatPropertyType matType, std::string strTextureFile);
		//// PNG
		//GLuint LoadPNGTexture(const char *filename);
		//GLuint LoadPNGTextureCubeMap(const char *filename);
		//// DDS
		//GLuint LoadDDSTexture(const char *filename);
		//GLuint LoadDDSTextureCubeMap(const char *filename);
		////////////////////////////////////////////////////////////////////////////
	public:
		//----------------------------------------------------
		void Create(const char* texture_name, bool enableMipmapping = true);
		void CreateCubeBy6Texture2D(const char* texture_name, bool enableMipmapping = true);
		void CreatePrefilterCubeMap(const char* textureName);
		void CreatePrefilterTableMap(const char* textureName);
		void Create(int32_t width, int32_t height, bool enableMipmapping = true);
		void CreateFloat32Texture(int32_t width, int32_t height, bool enableMipmapping = true);
		void CreateFloat32DepthTexture(int32_t width, int32_t height, bool enableMipmapping = true);
		void CreateFloat32CubeTexture(int32_t width, int32_t height, bool enableMipmapping = true);
		void CreateFloat16CubeTexture(int32_t width, int32_t height, bool enableMipmapping = true);
		void CreateFloat323DTexture(int32_t width, int32_t height, int32_t depth, bool enableMipmapping = true);

	protected:
		static void CreateGLTexture2D(int32_t tex_obj, int32_t width, int32_t height, int8_t* texture_data, int32_t texture_pixel_format, bool enableMipmapping, ETextureWrapMode wrapMode);
		static void CreateGLTextureCube(int32_t tex_obj, int32_t width, int32_t height, int8_t* texture_data, int32_t texture_pixel_format, bool enableMipmapping);
		static void CreateGLTexture3D();// TODO:
		static void SetTexturePixelFormat(HXGLTexture* texture, int32_t texture_pixel_format);

	public:
		// int texID;
		std::string texName;
		GLuint texObj;	// 具体纹理数据保存在显存上了，系统内存不需要再保存一份
		TextureType texType;
		TextureFormat texFormat;
		int texWidth;
		int texHeight;
		int texDepth;
		int texBPP;		// The Bytes per pixel of the texture
	};
}


