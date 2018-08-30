#include "..\include\HXGLRenderTarget.h"
#include "HXGLTexture.h"

namespace HX3D
{
	HXGLRenderTarget::HXGLRenderTarget()
	: m_FBO(0)
	, m_DepthRBO(0)
	, m_Width(0)
	, m_Height(0)
	{
		memset(m_bDrawColorBuffers, 0, sizeof(m_bDrawColorBuffers));

		// Get default frame buffer object
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_FBO);
	}

	HXGLRenderTarget::HXGLRenderTarget(int width, int height)
	: m_FBO(0)
	, m_DepthRBO(0)
	, m_Width(0)
	, m_Height(0)
	{
		memset(m_bDrawColorBuffers, 0, sizeof(m_bDrawColorBuffers));

		GLint preFBO = 0;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &preFBO);

		// Create frame buffer object
		glGenFramebuffers(1, reinterpret_cast<GLuint*>(&m_FBO));
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

		//------------------------------------------------------------------------
		// Must attach a depth buffer. If do not, the image won't have the effect of depth
		//------------------------------------------------------------------------

		// Create depth render buffer object
		glGenRenderbuffers(1, reinterpret_cast<GLuint*>(&m_DepthRBO));
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRBO);

		// Allocate memory for depth render buffer object
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

		// Attach to frame buffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRBO);

		m_Width = width;
		m_Height = height;

		glBindFramebuffer(GL_FRAMEBUFFER, preFBO);

		// Check the status
		/*GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		assert(status == GL_FRAMEBUFFER_COMPLETE);*/
	}

	HXGLRenderTarget::~HXGLRenderTarget()
	{
		if (m_DepthRBO != 0) {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glDeleteRenderbuffers(1, reinterpret_cast<const GLuint*>(&m_DepthRBO));
			m_DepthRBO = 0;
		}

		if (m_FBO != 0) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDeleteFramebuffers(1, reinterpret_cast<const GLuint*>(&m_FBO));
			m_FBO = 0;
		}
	}

	void HXGLRenderTarget::AttachDepthTexture(HXITexture* depth_tex)
	{
		if (depth_tex != NULL)
		{
			GLint preFBO = 0;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &preFBO);

			HXGLTexture* tex = (HXGLTexture*)depth_tex;
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glBindTexture(GL_TEXTURE_2D, tex->texObj);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex->texObj, 0);

			glBindFramebuffer(GL_FRAMEBUFFER, preFBO);
		}
	}

	void HXGLRenderTarget::AttachColorTexture(DrawColorBuffer index, HXITexture* color_tex, int32_t level)
	{
		if (COLORBUF_COLOR_ATTACHMENT0 <= index && index <= COLORBUF_COLOR_ATTACHMENT7
			&& color_tex != NULL) 
		{
			GLint preFBO = 0;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &preFBO);

			HXGLTexture* tex = (HXGLTexture*)color_tex;
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glBindTexture(GL_TEXTURE_2D, tex->texObj);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index - COLORBUF_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex->texObj, level);
			
			glBindFramebuffer(GL_FRAMEBUFFER, preFBO);
		}
	}

	void HXGLRenderTarget::AttachCubeTexture(DrawColorBuffer* index, HXITexture* cube_tex, int32_t level)
	{
		if (cube_tex != NULL) 
		{
			GLint preFBO = 0;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &preFBO);

			HXGLTexture* tex = (HXGLTexture*)cube_tex;
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glBindTexture(GL_TEXTURE_CUBE_MAP, tex->texObj);
			GLint face[6] = {
				GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			};
			for (int32_t i = 0; i < 6; i++) 
			{
				if (COLORBUF_COLOR_ATTACHMENT0 <= index[i] && index[i] <= COLORBUF_COLOR_ATTACHMENT7) 
				{
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index[i] - COLORBUF_COLOR_ATTACHMENT0
						, face[i], tex->texObj, level);
				}
			}

			glBindFramebuffer(GL_FRAMEBUFFER, preFBO);
		}
	}

	void HXGLRenderTarget::Attach3DColorTexture(DrawColorBuffer index, HXITexture* color_tex_3d, int32_t layer, int32_t level)
	{
		if (COLORBUF_COLOR_ATTACHMENT0 <= index && index <= COLORBUF_COLOR_ATTACHMENT7
			&& color_tex_3d != NULL) 
		{
			GLint preFBO = 0;
			glGetIntegerv(GL_FRAMEBUFFER_BINDING, &preFBO);

			HXGLTexture* tex = (HXGLTexture*)color_tex_3d;
			glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
			glBindTexture(GL_TEXTURE_3D, tex->texObj);
			glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index - COLORBUF_COLOR_ATTACHMENT0, GL_TEXTURE_3D, tex->texObj, level, layer);
		
			glBindFramebuffer(GL_FRAMEBUFFER, preFBO);
		}
	}

	void HXGLRenderTarget::EnableDrawColorBuffer(DrawColorBuffer index)
	{
		if (COLORBUF_COLOR_ATTACHMENT0 <= index && index <= COLORBUF_COLOR_ATTACHMENT7) 
		{
			m_bDrawColorBuffers[index - COLORBUF_COLOR_ATTACHMENT0] = true;
		}
	}

	void HXGLRenderTarget::DisableDrawColorBuffer(DrawColorBuffer index)
	{
		if (COLORBUF_COLOR_ATTACHMENT0 <= index && index <= COLORBUF_COLOR_ATTACHMENT7) 
		{
			m_bDrawColorBuffers[index - COLORBUF_COLOR_ATTACHMENT0] = false;
		}
	}

	void HXGLRenderTarget::DisableAllDrawColorBuffers()
	{
		for (int32_t i = 0; i < kMaxDrawColorBuffers; i++) 
		{
			m_bDrawColorBuffers[i] = false;
		}
	}

	void* HXGLRenderTarget::GetNativeRenderTarget()
	{
		return reinterpret_cast<void*>(m_FBO);
	}

	int HXGLRenderTarget::GetWidth() const
	{
		return m_Width;
	}

	int HXGLRenderTarget::GetHeight() const
	{
		return m_Height;
	}
}