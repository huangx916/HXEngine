#include "..\include\HXGLMaterial.h"
#include "HXGLTexture.h"
#include "LoadShaders.h"
#include "HXResourceManager.h"
#include "HXSceneManager.h"
#include "HXFog.h"
#include "HXGLCamera.h"
#include "HXGLTransform.h"
#include "HXRoot.h"
#include "HXGLRenderSystem.h"
#include "HXGLShadowMap.h"
#include "HXGLRenderable.h"
#include "HXStatus.h"
#include <algorithm>

namespace HX3D
{
	HXGLMaterial::HXGLMaterial(HXMaterialInfo* pMatInfo)
	{
		HXMaterial::SetMaterialInfo(pMatInfo);

		std::string strVertShaderFile = pMatInfo->strShaderFile + ".vert";
		std::string strFragShaderFile = pMatInfo->strShaderFile + ".frag";

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, strVertShaderFile.c_str() },
			{ GL_FRAGMENT_SHADER, strFragShaderFile.c_str() },
			{ GL_NONE, NULL }
		};

		render_scene_prog = LoadShaders(shaders);
		glUseProgram(render_scene_prog);

		// 每帧更新的变量
		render_scene_uniforms.render_eye_pos_loc = glGetUniformLocation(render_scene_prog, "eyePos");
		render_scene_uniforms.render_model_matrix_loc = glGetUniformLocation(render_scene_prog, "model_matrix");
		render_scene_uniforms.render_view_matrix_loc = glGetUniformLocation(render_scene_prog, "view_matrix");
		render_scene_uniforms.render_projection_matrix_loc = glGetUniformLocation(render_scene_prog, "projection_matrix");
		render_scene_uniforms.render_mvp_matrix_loc = glGetUniformLocation(render_scene_prog, "mvp_matrix");
		render_scene_uniforms.render_shadow_matrix_loc = glGetUniformLocation(render_scene_prog, "shadow_matrix");

		// 不需要每帧更新的变量（除编辑器模式下）
		int nTexIndex = 0;
		for (std::vector<HXMaterialProperty>::iterator itr = pMatInfo->vctMatProperty.begin(); itr != pMatInfo->vctMatProperty.end(); ++itr)
		{
			switch (itr->type)
			{
			case MPT_TEXTURE:
			{
				GLint tex_uniform_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture(itr->value);
				if (NULL == tex)
				{
					if (itr->value.find('.') == std::string::npos)
					{
						tex = new HXGLTexture(MPT_TEXTURE, "prefab/_Material/builtinPic/" + itr->value +".png");
					}
					else
					{
						//tex = new HXGLTexture(MPT_TEXTURE, itr->value);
						tex = new HXGLTexture();
						tex->Create(itr->value.c_str());
					}					
					HXResourceManager::GetInstance()->AddTexture(itr->value, tex);
				}
				// 采样器
				glUniform1i(tex_uniform_loc, nTexIndex);
				// 纹理单元
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				// 暂时不用其他类型的Texture,这里只使用GL_TEXTURE_2D
				/*glBindTexture(tex->mImageData.target, tex->texId);
				glTexParameteri(tex->mImageData.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				vglUnloadImage(&tex->mImageData);*/
				glBindTexture(GL_TEXTURE_2D, tex->texObj);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name + "_ST").c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);

				++nTexIndex;
			}
			break;
			case MPT_FLOAT:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (property_loc != -1)
				{
					glUniform1f(property_loc, itr->value1);
				}
			}
			break;
			case MPT_FLOAT2:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (property_loc != -1)
				{
					glUniform2f(property_loc, itr->value1, itr->value2);
				}
			}
			break;
			case MPT_FLOAT3:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (property_loc != -1)
				{
					glUniform3f(property_loc, itr->value1, itr->value2, itr->value3);
				}
			}
			break;
			case MPT_FLOAT4:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (property_loc != -1)
				{
					glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);
				}
			}
			break;
			case MPT_CUBEMAP:
			{
				GLint tex_uniform_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture(itr->value);
				if (NULL == tex)
				{
					tex = new HXGLTexture(MPT_CUBEMAP,itr->value);
					HXResourceManager::GetInstance()->AddTexture(itr->value, tex);
				}

				// 采样器
				glUniform1i(tex_uniform_loc, nTexIndex);
				// 纹理单元
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				// 暂时不用其他类型的Texture,这里只使用GL_TEXTURE_2D
				/*glBindTexture(tex->mImageData.target, tex->texId);
				glTexParameteri(tex->mImageData.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				vglUnloadImage(&tex->mImageData);*/
				glBindTexture(GL_TEXTURE_CUBE_MAP, tex->texObj);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name + "_ST").c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);

				++nTexIndex;
			}
			break;
			default:
				break;
			}
		}

		// FOG TODO: Uniform Block 共享
		GLint property_loc = glGetUniformLocation(render_scene_prog, "useFog");
		if (property_loc != -1)
		{
			HXFog* fog = HXSceneManager::GetInstance()->fog;
			GLint nUseFog = fog->useFog;
			glUniform1i(property_loc, nUseFog);
			if (nUseFog == 1)
			{
				property_loc = glGetUniformLocation(render_scene_prog, "fogType");
				GLint nfogType = fog->fogType;
				glUniform1i(property_loc, nfogType);

				property_loc = glGetUniformLocation(render_scene_prog, "fogColor");
				HXCOLOR color = fog->fogColor;
				glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

				property_loc = glGetUniformLocation(render_scene_prog, "fogStart");
				GLfloat nfogStart = fog->fogStart;
				glUniform1f(property_loc, nfogStart);

				property_loc = glGetUniformLocation(render_scene_prog, "fogEnd");
				GLfloat nfogEnd = fog->fogEnd;
				glUniform1f(property_loc, nfogEnd);

				property_loc = glGetUniformLocation(render_scene_prog, "fogDensity");
				GLfloat nfogDensity = fog->fogDensity;
				glUniform1f(property_loc, nfogDensity);

				property_loc = glGetUniformLocation(render_scene_prog, "fogGradiant");
				GLfloat nfogGradiant = fog->fogGradiant;
				glUniform1f(property_loc, nfogGradiant);
			}
		}
		
		property_loc = glGetUniformLocation(render_scene_prog, "ambient");
		HXCOLOR color = HXSceneManager::GetInstance()->ambient;
		glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

		// light
		for (int index = 0; index < HXSceneManager::GetInstance()->lightVct.size(); ++index)
		{
			HXLight* light = HXSceneManager::GetInstance()->lightVct[index];
			if (light && light->enable)
			{
				std::stringstream ss;
				std::string strIndex;
				ss << index;
				ss >> strIndex;
				std::string strLight = "Lights[" + strIndex + "]";
				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".isEnable").c_str());
				GLint isEnable = light->enable;
				glUniform1i(property_loc, isEnable);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightType").c_str());
				GLint lightType = light->lightType;
				glUniform1i(property_loc, lightType);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightColor").c_str());
				HXCOLOR lightColor = light->color;
				glUniform3f(property_loc, lightColor.r / 255.0f, lightColor.g / 255.0f, lightColor.b / 255.0f);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightDir").c_str());
				HXVector3D lightDir = light->direct;
				glUniform3f(property_loc, lightDir.x, lightDir.y, lightDir.z);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".shininess").c_str());
				GLfloat shininess = light->shininess;
				glUniform1f(property_loc, shininess);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".strength").c_str());
				GLfloat strength = light->strength;
				glUniform1f(property_loc, strength);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightPos").c_str());
				HXVector3D lightPos = light->position;
				glUniform3f(property_loc, lightPos.x, lightPos.y, lightPos.z);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".constantAttenuation").c_str());
				GLfloat constantAttenuation = light->constantAttenuation;
				glUniform1f(property_loc, constantAttenuation);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".LinearAttenuation").c_str());
				GLfloat LinearAttenuation = light->LinearAttenuation;
				glUniform1f(property_loc, LinearAttenuation);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".QuadraticAttenuation").c_str());
				GLfloat QuadraticAttenuation = light->QuadraticAttenuation;
				glUniform1f(property_loc, QuadraticAttenuation);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".SpotCosCutoff").c_str());
				GLfloat SpotCosCutoff = light->SpotCosCutoff;
				glUniform1f(property_loc, SpotCosCutoff);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".SpotExponent").c_str());
				GLfloat SpotExponent = light->SpotExponent;
				glUniform1f(property_loc, SpotExponent);

				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".ConeDirection").c_str());
				HXVector3D ConeDirection = light->ConeDirection;
				glUniform3f(property_loc, ConeDirection.x, ConeDirection.y, ConeDirection.z);
			}
		}

		glUseProgram(0);
	}

	HXGLMaterial::~HXGLMaterial()
	{
		glDeleteProgram(render_scene_prog);
	}

	void HXGLMaterial::SetMaterialRenderStateAllRenderable(HXICamera* curCamera)
	{
		HXStatus::GetInstance()->nBatchCall += 1;

		if (mMatInfo->nCullFace > 0)
		{
			glEnable(GL_CULL_FACE);
			glFrontFace(mMatInfo->nCullFace - 1 + GL_CW);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		if (mMatInfo->nDepthTest > 0)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(mMatInfo->nDepthTest - 1 + GL_LESS);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
		
		if (mMatInfo->nAlphaBlend > 0)
		{
			glEnable(GL_BLEND);
			glBlendFunc(mMatInfo->nSrcAlpha + GL_SRC_COLOR, mMatInfo->nDestAlpha + GL_SRC_COLOR);
			glDepthMask(GL_FALSE);
		}
		else
		{
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
		}
		
		//glEnable(GL_TEXTURE_2D);

		glUseProgram(render_scene_prog);

		//HXGLCamera* pCamera = (HXGLCamera*)HXSceneManager::GetInstance()->mainCamera;
		HXGLCamera* pCamera = (HXGLCamera*)curCamera;
		HXVector3D eyePos = pCamera->transform->mLocalPostion;
		glUniform3f(render_scene_uniforms.render_eye_pos_loc, eyePos.x, eyePos.y, eyePos.z);
		glUniformMatrix4fv(render_scene_uniforms.render_view_matrix_loc, 1, GL_FALSE, pCamera->mMatrixView);
		glUniformMatrix4fv(render_scene_uniforms.render_projection_matrix_loc, 1, GL_FALSE, pCamera->mMatrixProjection);

		// 每次渲染，状态都要重新赋值
		HXMaterialInfo* pMatInfo = mMatInfo;
		int nTexIndex = 0;
		for (std::vector<HXMaterialProperty>::iterator itr = pMatInfo->vctMatProperty.begin(); itr != pMatInfo->vctMatProperty.end(); ++itr)
		{
			switch (itr->type)
			{
			case MPT_TEXTURE:
			{
				//每帧渲染时shader uniform的texture变量需要重新处理（赋值的只是纹理绑定点，纹理绑定点绑定的纹理可能被改掉了）
				GLint tex_uniform_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture(itr->value);

				glUniform1i(tex_uniform_loc, nTexIndex);
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				glBindTexture(GL_TEXTURE_2D, tex->texObj);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				if (HXRoot::GetInstance()->IsEditorMode())
				{
					GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name + "_ST").c_str());
					glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);
				}
				++nTexIndex;
			}
			break;
			if (HXRoot::GetInstance()->IsEditorMode())
			{
			case MPT_FLOAT:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				glUniform1f(property_loc, itr->value1);
			}
			break;
			case MPT_FLOAT2:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				glUniform2f(property_loc, itr->value1, itr->value2);
			}
			break;
			case MPT_FLOAT3:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				glUniform3f(property_loc, itr->value1, itr->value2, itr->value3);
			}
			break;
			case MPT_FLOAT4:
			{
				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);
			}
			break;
			case MPT_CUBEMAP:
			{
				GLint tex_uniform_loc = glGetUniformLocation(render_scene_prog, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture(itr->value);
				if (NULL == tex)
				{
					tex = new HXGLTexture(MPT_CUBEMAP, itr->value);
					HXResourceManager::GetInstance()->AddTexture(itr->value, tex);
				}

				// 采样器
				glUniform1i(tex_uniform_loc, nTexIndex);
				// 纹理单元
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				// 暂时不用其他类型的Texture,这里只使用GL_TEXTURE_2D
				/*glBindTexture(tex->mImageData.target, tex->texId);
				glTexParameteri(tex->mImageData.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				vglUnloadImage(&tex->mImageData);*/
				glBindTexture(GL_TEXTURE_CUBE_MAP, tex->texObj);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				GLint property_loc = glGetUniformLocation(render_scene_prog, (itr->name + "_ST").c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);

				++nTexIndex;
			}
			break;
			}
			default:
				break;
			}
		}

		// shadow
		GLint tex_uniform_loc = glGetUniformLocation(render_scene_prog, "depth_texture");
		if (tex_uniform_loc != -1)
		{
			HXGLRenderSystem* rs = (HXGLRenderSystem*)HXRoot::GetInstance()->GetRenderSystem();
			HXGLShadowMap* sm = rs->mShadowMap;
			if (sm && sm->IsEnable())
			{
				// 每帧需要更新
				const vmath::mat4 scale_bias_matrix = vmath::mat4(vmath::vec4(0.5f, 0.0f, 0.0f, 0.0f),
					vmath::vec4(0.0f, 0.5f, 0.0f, 0.0f),
					vmath::vec4(0.0f, 0.0f, 0.5f, 0.0f),
					vmath::vec4(0.5f, 0.5f, 0.5f, 1.0f));
				glUniformMatrix4fv(render_scene_uniforms.render_shadow_matrix_loc, 1, GL_FALSE, scale_bias_matrix * sm->light_projection_matrix * sm->light_view_matrix);

				glUniform1i(tex_uniform_loc, nTexIndex);
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				glBindTexture(GL_TEXTURE_2D, sm->depth_texture);
				++nTexIndex;
			}
		}

		if (HXRoot::GetInstance()->IsEditorMode())
		{
			// FOG TODO: Uniform Block 共享
			GLint property_loc = glGetUniformLocation(render_scene_prog, "useFog");
			if (property_loc != -1)
			{
				HXFog* fog = HXSceneManager::GetInstance()->fog;
				GLint nUseFog = fog->useFog;
				glUniform1i(property_loc, nUseFog);
				if (nUseFog == 1)
				{
					property_loc = glGetUniformLocation(render_scene_prog, "fogType");
					GLint nfogType = fog->fogType;
					glUniform1i(property_loc, nfogType);

					property_loc = glGetUniformLocation(render_scene_prog, "fogColor");
					HXCOLOR color = fog->fogColor;
					glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

					property_loc = glGetUniformLocation(render_scene_prog, "fogStart");
					GLfloat nfogStart = fog->fogStart;
					glUniform1f(property_loc, nfogStart);

					property_loc = glGetUniformLocation(render_scene_prog, "fogEnd");
					GLfloat nfogEnd = fog->fogEnd;
					glUniform1f(property_loc, nfogEnd);

					property_loc = glGetUniformLocation(render_scene_prog, "fogDensity");
					GLfloat nfogDensity = fog->fogDensity;
					glUniform1f(property_loc, nfogDensity);

					property_loc = glGetUniformLocation(render_scene_prog, "fogGradiant");
					GLfloat nfogGradiant = fog->fogGradiant;
					glUniform1f(property_loc, nfogGradiant);
				}
			}

			// light
			// 如果有删除的light，则需要刷新
			for (int index = 0; index < 5; ++index)
			{
				std::stringstream ss;
				std::string strIndex;
				ss << index;
				ss >> strIndex;
				std::string strLight = "Lights[" + strIndex + "]";
				property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".isEnable").c_str());
				GLint isEnable = 0;
				glUniform1i(property_loc, isEnable);
			}
			for (int index = 0; index < HXSceneManager::GetInstance()->lightVct.size(); ++index)
			{
				HXLight* light = HXSceneManager::GetInstance()->lightVct[index];
				if (light)
				{
					std::stringstream ss;
					std::string strIndex;
					ss << index;
					ss >> strIndex;
					std::string strLight = "Lights[" + strIndex + "]";
					property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".isEnable").c_str());
					GLint isEnable = light->enable;
					glUniform1i(property_loc, isEnable);
					if (isEnable)
					{
						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightType").c_str());
						GLint lightType = light->lightType;
						glUniform1i(property_loc, lightType);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightColor").c_str());
						HXCOLOR lightColor = light->color;
						glUniform3f(property_loc, lightColor.r / 255.0f, lightColor.g / 255.0f, lightColor.b / 255.0f);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightDir").c_str());
						HXVector3D lightDir = light->direct;
						glUniform3f(property_loc, lightDir.x, lightDir.y, lightDir.z);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".shininess").c_str());
						GLfloat shininess = light->shininess;
						glUniform1f(property_loc, shininess);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".strength").c_str());
						GLfloat strength = light->strength;
						glUniform1f(property_loc, strength);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".lightPos").c_str());
						HXVector3D lightPos = light->position;
						glUniform3f(property_loc, lightPos.x, lightPos.y, lightPos.z);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".constantAttenuation").c_str());
						GLfloat constantAttenuation = light->constantAttenuation;
						glUniform1f(property_loc, constantAttenuation);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".LinearAttenuation").c_str());
						GLfloat LinearAttenuation = light->LinearAttenuation;
						glUniform1f(property_loc, LinearAttenuation);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".QuadraticAttenuation").c_str());
						GLfloat QuadraticAttenuation = light->QuadraticAttenuation;
						glUniform1f(property_loc, QuadraticAttenuation);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".SpotCosCutoff").c_str());
						GLfloat SpotCosCutoff = light->SpotCosCutoff;
						glUniform1f(property_loc, SpotCosCutoff);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".SpotExponent").c_str());
						GLfloat SpotExponent = light->SpotExponent;
						glUniform1f(property_loc, SpotExponent);

						property_loc = glGetUniformLocation(render_scene_prog, (strLight + ".ConeDirection").c_str());
						HXVector3D ConeDirection = light->ConeDirection;
						glUniform3f(property_loc, ConeDirection.x, ConeDirection.y, ConeDirection.z);
					}
				}
			}

			property_loc = glGetUniformLocation(render_scene_prog, "ambient");
			HXCOLOR color = HXSceneManager::GetInstance()->ambient;
			glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
		}

	}

	void HXGLMaterial::SetMaterialRenderStateEachRenderable(HXRenderable* renderable)
	{
		HXGLRenderable* glrenderable = (HXGLRenderable*)renderable;

		glUniformMatrix4fv(render_scene_uniforms.render_model_matrix_loc, 1, GL_FALSE, glrenderable->mMatrixModel);
		glUniformMatrix4fv(render_scene_uniforms.render_mvp_matrix_loc, 1, GL_FALSE, glrenderable->mMatrixProjection * glrenderable->mMatrixView * glrenderable->mMatrixModel);
	}

	void HXGLMaterial::SetShadowMapMaterialRenderStateAllRenderable()
	{
		HXStatus::GetInstance()->nBatchCall += 1;

		HXGLRenderSystem* rs = (HXGLRenderSystem*)HXRoot::GetInstance()->GetRenderSystem();
		HXGLShadowMap* sm = rs->mShadowMap;
		// Alpha test
		for (std::vector<HXMaterialProperty>::iterator itr = mMatInfo->vctMatProperty.begin(); itr != mMatInfo->vctMatProperty.end(); ++itr)
		{
			switch (itr->type)
			{
			case MPT_TEXTURE:
			{
				GLint tex_uniform_loc = glGetUniformLocation(sm->render_light_prog, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture(itr->value);

				glUniform1i(tex_uniform_loc, 0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex->texObj);

				GLint property_loc = glGetUniformLocation(sm->render_light_prog, (itr->name + "_ST").c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);

				return;
			}
			break;
			default:
				break;
			}
		}
	}

	void HXGLMaterial::SetShadowMapMaterialRenderStateEachRenderable(HXRenderable* renderable)
	{
		HXGLRenderable* glrenderable = (HXGLRenderable*)renderable;

		HXGLRenderSystem* rs = (HXGLRenderSystem*)HXRoot::GetInstance()->GetRenderSystem();
		HXGLShadowMap* sm = rs->mShadowMap;

		glUniformMatrix4fv(sm->render_light_uniforms.model_view_projection_matrix, 1, GL_FALSE, sm->light_projection_matrix * sm->light_view_matrix * glrenderable->mMatrixModel);
	}
}
