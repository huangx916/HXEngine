#ifndef _VERMILION_H_
#define _VERMILION_H_

// #define USE_GL3W

#ifdef USE_GL3W

#include <GL3/gl3.h>
#include <GL3/gl3w.h>

#else

#define GLEW_STATIC
#include <GL/glew.h>

#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

// Enough mips for 16K x 16K, which is the minumum required for OpenGL 4.x
#define MAX_TEXTURE_MIPS    14

// Each texture image data structure contains an array of MAX_TEXTURE_MIPS
// of these mipmap structures. The structure represents the mipmap data for
// all slices at that level.
struct vglImageMipData
{
    GLsizei width;                              // Width of this mipmap level
    GLsizei height;                             // Height of this mipmap level
    GLsizei depth;                              // Depth pof mipmap level
    GLsizeiptr mipStride;                       // Distance in bytes between mip levels in memory
    GLvoid* data;                               // Pointer to data
};

// This is the main image data structure. It contains all the parameters needed
// to place texture data into a texture object using OpenGL.
struct vglImageData
{
    GLenum target;                              // Texture target (1D, 2D, cubemap, array, etc.)
    GLenum internalFormat;                      // Recommended internal format (GL_RGBA32F, etc).
    GLenum format;                              // Format in memory
    GLenum type;                                // Type in memory (GL_RED, GL_RGB, etc.)
    GLenum swizzle[4];                          // Swizzle for RGBA
    GLsizei mipLevels;                          // Number of present mipmap levels
    GLsizei slices;                             // Number of slices (for arrays)
    GLsizeiptr sliceStride;                     // Distance in bytes between slices of an array texture
    GLsizeiptr totalDataSize;                   // Complete amount of data allocated for texture
    vglImageMipData mip[MAX_TEXTURE_MIPS];      // Actual mipmap data
};

void vglLoadImage(const char* filename, vglImageData* image);
void vglUnloadImage(vglImageData* image);
GLuint vglLoadTexture(const char* filename,
                      GLuint texture,
                      vglImageData* image);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#if !defined VERMILION_BUILD_LIB
  #ifdef _M_X64
    #ifdef _DEBUG
      #pragma comment (lib, "vermilion64_d.lib")
    #else
      #pragma comment (lib, "vermilion64.lib")
    #endif /* _DEBUG */
  #else
    #ifdef _DEBUG
     #pragma comment (lib, "vermilion32_d.lib")
    #else
      #pragma comment (lib, "vermilion32.lib")
    #endif /* _DEBUG */
  #endif /* _M_X64 */
#endif /* VERMILION_BUILD_LIB */

#endif /* _VERMILION_H_ */
