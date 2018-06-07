#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "vgl.h"

namespace HX3D
{
	class gl_texture_t
	{
	public:
		GLsizei width;
		GLsizei height;
		GLenum format;
		GLint internalFormat;
		GLuint id;
		GLubyte* texels;
	};

	class HXGLLoadPNG
	{
	public:
		static GLuint vglLoadPNGTexture(const char *filename);
	private:
		static gl_texture_t * ReadPNGFromFile(const char *filename);
		static void GetPNGtextureInfo(int color_type, gl_texture_t *texinfo);
	};
}