#pragma once
#include "HXCommon.h"
#include "HXITexture.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	class HXRenderTarget
	{
	public:
		HXRenderTarget();
		virtual ~HXRenderTarget();

	public:
		virtual void AttachDepthTexture(HXITexture* depth_tex) {};
		virtual void AttachColorTexture(DrawColorBuffer index, HXITexture* color_tex, int32_t level = 0) {};
		virtual void AttachCubeTexture(DrawColorBuffer* index, HXITexture* cube_tex, int32_t level = 0) {};
		virtual void Attach3DColorTexture(DrawColorBuffer index, HXITexture* color_tex_3d, int32_t layer, int32_t level = 0) {};

		virtual void EnableDrawColorBuffer(DrawColorBuffer index) {};
		virtual void DisableDrawColorBuffer(DrawColorBuffer index) {};
		virtual void DisableAllDrawColorBuffers() {};

		virtual void* GetNativeRenderTarget() { return NULL; };

		virtual int GetWidth() const { return 0; };
		virtual int GetHeight() const { return 0; };
	};
}
