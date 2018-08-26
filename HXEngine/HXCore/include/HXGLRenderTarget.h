#pragma once
#include "HXCommon.h"
#include "HXRenderTarget.h"
#include "vgl.h"

namespace HX3D
{
	class HXGLRenderTarget : public HXRenderTarget
	{
	public:
		HXGLRenderTarget();
		HXGLRenderTarget(int width, int height);
		~HXGLRenderTarget();

		GLint m_FBO;
		GLint m_DepthRBO;
		int m_Width;
		int m_Height;
		//bool m_bDrawColorBuffers[kMaxDrawColorBuffers];
	};
}