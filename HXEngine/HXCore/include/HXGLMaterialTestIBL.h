#pragma once
#include "HXCommon.h"
#include "HXMaterial.h"
#include "vgl.h"
#include "HXGLRenderTarget.h"

namespace HX3D
{
	class HXRenderable;
	class HXGLTexture;
	class HXGLMaterial : public HXMaterial
	{
	public:
		HXGLMaterial(HXMaterialInfo* pMatInfo);
		~HXGLMaterial();
		
		virtual void SetMaterialRenderStateAllRenderable(HXICamera* curCamera);
		virtual void SetMaterialRenderStateEachRenderable(HXRenderable* renderable);
		virtual void SetShadowMapMaterialRenderStateAllRenderable();
		virtual void SetShadowMapMaterialRenderStateEachRenderable(HXRenderable* renderable);

		GLuint render_scene_prog;

		struct
		{
			GLint render_eye_pos_loc;
			GLint render_model_matrix_loc;
			GLint render_view_matrix_loc;
			GLint render_projection_matrix_loc;
			GLint render_mvp_matrix_loc;
			GLint render_shadow_matrix_loc;
		}render_scene_uniforms;

		bool isIBL;
		HXGLRenderTarget* m_CubeMapRT;
		HXGLTexture* m_CubeMap;
		GLuint render_target_prog;
		GLint m_WVPLoc;
		GLint m_ERMapLoc;
	};
}


