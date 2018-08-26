#include "..\include\HXGLRenderTarget.h"

namespace HX3D
{
	HXGLRenderTarget::HXGLRenderTarget()
	{
		// default
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_FBO);
	}

	HXGLRenderTarget::HXGLRenderTarget(int width, int height)
	{

	}

	HXGLRenderTarget::~HXGLRenderTarget()
	{
	}
}