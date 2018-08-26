#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXRenderTarget
	{
	public:
		HXRenderTarget();
		virtual ~HXRenderTarget();

		/*virtual HXRenderTarget* Create(int32_t width, int32_t height);
		virtual HXRenderTarget* DefaultRenderTarget();*/

	public:
		/*void AttachDepthTexture(texture::Texture* depth_tex);
		void AttachColorTexture(render::DrawColorBuffer index, texture::Texture* color_tex, int32_t level = 0);
		void AttachCubeTexture(render::DrawColorBuffer* index, texture::Texture* cube_tex, int32_t level = 0);
		void Attach3DColorTexture(render::DrawColorBuffer index, texture::Texture* color_tex_3d, int32_t layer, int32_t level = 0);

		void EnableDrawColorBuffer(render::DrawColorBuffer index);
		void DisableDrawColorBuffer(render::DrawColorBuffer index);
		void DisableAllDrawColorBuffers();

		void* GetNativeRenderTarget();

		int32_t GetWidth() const;
		int32_t GetHeight() const;*/
	};
}
