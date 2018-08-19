#include "HXGLLoadPNG.h"
#include "png.h"
#include "vermilion.h"

namespace HX3D
{
	GLuint HXGLLoadPNG::vglLoadPNGTexture(const char *filename)
	{
		gl_texture_t *png_tex = NULL;
		GLuint tex_id = 0;
		GLint alignment;
		png_tex = ReadPNGFromFile(filename);
		if (png_tex && png_tex->texels)
		{
			/* Generate texture */
			glGenTextures(1, &png_tex->id);
			glBindTexture(GL_TEXTURE_2D, png_tex->id);
			/* Setup some parameters for texture filters and mipmapping */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, png_tex->internalFormat, png_tex->width, png_tex->height, 0, png_tex->format, GL_UNSIGNED_BYTE, png_tex->texels);
			glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			tex_id = png_tex->id;
			/* OpenGL has its own copy of texture data */
			free(png_tex->texels);
			free(png_tex);
		}
		return tex_id;
	}

	GLuint HXGLLoadPNG::vglLoadPNGTextureCubeMap(const char *filename)
	{
		gl_texture_t *png_tex = NULL;
		GLuint tex_id = 0;

		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tex_id);
		glEnable(GL_TEXTURE_CUBE_MAP);
		glActiveTexture(GL_TEXTURE0);

		GLint alignment;
		std::string subfilename = filename;
		int pos = subfilename.length();
		for (int i = 0; i < 6; ++i)
		{
			switch(i)
			{
			case 0:
				subfilename = filename;
				subfilename.insert(pos - 4, "_right");
				break;
			case 1:
				subfilename = filename;
				subfilename.insert(pos - 4, "_left");
				break;
			case 2:
				subfilename = filename;
				subfilename.insert(pos - 4, "_bottom");
				break;
			case 3:
				subfilename = filename;
				subfilename.insert(pos - 4, "_top");
				break;
			case 4:
				subfilename = filename;
				subfilename.insert(pos - 4, "_front");
				break;
			case 5:
				subfilename = filename;
				subfilename.insert(pos - 4, "_back");
				break;
			default:
				break;
			}
			png_tex = ReadPNGFromFile(subfilename.c_str());
			if (png_tex && png_tex->texels)
			{
				///* Generate texture */
				//glGenTextures(1, &png_tex->id);
				//glBindTexture(GL_TEXTURE_2D, png_tex->id);
				///* Setup some parameters for texture filters and mipmapping */
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

				//glGetIntegerv(GL_UNPACK_ALIGNMENT, &alignment);
				//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				//glTexImage2D(GL_TEXTURE_2D, 0, png_tex->internalFormat, png_tex->width, png_tex->height, 0, png_tex->format, GL_UNSIGNED_BYTE, png_tex->texels);
				//glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				//glGenerateMipmap(GL_TEXTURE_2D);

				//tex_id = png_tex->id;
				///* OpenGL has its own copy of texture data */
				//free(png_tex->texels);
				//free(png_tex);


				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, png_tex->internalFormat, png_tex->width, png_tex->height, 0, png_tex->format, GL_UNSIGNED_BYTE, png_tex->texels);
				
				free(png_tex->texels);
				free(png_tex);
				png_tex = NULL;
			}
		}
		return tex_id;
	}

	gl_texture_t * HXGLLoadPNG::ReadPNGFromFile(const char *filename)
	{
		gl_texture_t *texinfo;
		png_byte magic[8];
		png_structp png_ptr;
		png_infop info_ptr;
		int bit_depth, color_type;
		FILE *fp = NULL;
		png_bytep *row_pointers = NULL;
		png_uint_32 w, h;
		int i;
		/* Open image file */
		fopen_s(&fp, filename, "rb");
		if (!fp)
		{
			fprintf(stderr, "error: couldn't open \"%s\"!\n", filename);
			return NULL;
		}
		/* Read magic number */
		fread(magic, 1, sizeof(magic), fp);
		/* Check for valid magic number */
		if (!png_check_sig(magic, sizeof(magic)))
		{
			fprintf(stderr, "error: \"%s\" is not a valid PNG image!\n", filename);
			fclose(fp);
			return NULL;
		}
		/* Create a png read struct */
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
		{
			fclose(fp);
			return NULL;
		}
		/* Create a png info struct */
		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
		{
			fclose(fp);
			png_destroy_read_struct(&png_ptr, NULL, NULL);
			return NULL;
		}
		/* Create our OpenGL texture object */
		texinfo = (gl_texture_t *)malloc(sizeof(gl_texture_t));
		/* Initialize the setjmp for returning properly after a libpng error occured */
		if (setjmp(png_jmpbuf(png_ptr)))
		{
			fclose(fp);
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
			if (row_pointers) free(row_pointers);
			if (texinfo) {
				if (texinfo->texels)
					free(texinfo->texels);
				free(texinfo);
			}
			return NULL;
		}
		/* Setup libpng for using standard C fread() function with our FILE pointer */
		png_init_io(png_ptr, fp);
		/* Tell libpng that we have already read the magic number */
		png_set_sig_bytes(png_ptr, sizeof(magic));
		/* Read png info */
		png_read_info(png_ptr, info_ptr);
		/* Get some usefull information from header */
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);
		/* Convert index color images to RGB images */
		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);
		/* Convert 1-2-4 bits grayscale images to 8 bits grayscale. */
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
			png_set_expand_gray_1_2_4_to_8(png_ptr);

		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png_ptr);
		if (bit_depth == 16) png_set_strip_16(png_ptr);
		else if (bit_depth < 8) png_set_packing(png_ptr);
		/* Update info structure to apply transformations */
		png_read_update_info(png_ptr, info_ptr);
		/* Retrieve updated information */
		png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);
		texinfo->width = w;
		texinfo->height = h;
		/* Get image format and components per pixel */
		GetPNGtextureInfo(color_type, texinfo);
		/* We can now allocate memory for storing pixel data */
		texinfo->texels = (unsigned char *)malloc(sizeof(unsigned char) * texinfo->width * texinfo->height * texinfo->internalFormat);
		/* Setup a pointer array. Each one points at the begening of a row. */
		row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * texinfo->height);
		for (i = 0; i < texinfo->height; ++i)
		{
			row_pointers[i] = (png_bytep)(texinfo->texels + ((texinfo->height - (i + 1)) * texinfo->width * texinfo->internalFormat));
		}
		/* Read pixel data using row pointers */
		png_read_image(png_ptr, row_pointers);
		/* Finish decompression and release memory */
		png_read_end(png_ptr, NULL);
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		/* We don't need row pointers anymore */
		free(row_pointers);
		fclose(fp);
		return texinfo;
	}

	void HXGLLoadPNG::GetPNGtextureInfo(int color_type, gl_texture_t *texinfo)
	{
		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
			texinfo->format = GL_LUMINANCE;
			texinfo->internalFormat = 1;
			break;

		case PNG_COLOR_TYPE_GRAY_ALPHA:
			texinfo->format = GL_LUMINANCE_ALPHA;
			texinfo->internalFormat = 2;
			break;

		case PNG_COLOR_TYPE_RGB:
			texinfo->format = GL_RGB;
			texinfo->internalFormat = 3;
			break;

		case PNG_COLOR_TYPE_RGB_ALPHA:
			texinfo->format = GL_RGBA;
			texinfo->internalFormat = 4;
			break;

		default:
			/* Badness */
			break;
		}
	}

}