#pragma once
#include "HXCommon.h"
#include "HXRenderTarget.h"
#include "vgl.h"

namespace HX3D
{
	static const int32_t kMaxDrawColorBuffers = 8;

	class HXGLRenderTarget : public HXRenderTarget
	{
	public:
		HXGLRenderTarget();
		HXGLRenderTarget(int width, int height);
		~HXGLRenderTarget();

	public:
		virtual void AttachDepthTexture(HXITexture* depth_tex);
		virtual void AttachColorTexture(DrawColorBuffer index, HXITexture* color_tex, int32_t level = 0);
		virtual void AttachCubeTexture(DrawColorBuffer* index, HXITexture* cube_tex, int32_t level = 0);
		virtual void Attach3DColorTexture(DrawColorBuffer index, HXITexture* color_tex_3d, int32_t layer, int32_t level = 0);

		virtual void EnableDrawColorBuffer(DrawColorBuffer index);
		virtual void DisableDrawColorBuffer(DrawColorBuffer index);
		virtual void DisableAllDrawColorBuffers();

		virtual void* GetNativeRenderTarget();

		virtual int GetWidth() const;
		virtual int GetHeight() const;

		GLint m_FBO;
		GLint m_DepthRBO;
		int m_Width;
		int m_Height;
		bool m_bDrawColorBuffers[kMaxDrawColorBuffers];
	};
}