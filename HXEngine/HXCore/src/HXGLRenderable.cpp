#include "..\include\HXGLRenderable.h"
#include "HXVector.h"
#include "HXMesh.h"
#include "LoadShaders.h"
// #include "vmath.h"
#include "HXGLCamera.h"
#include "HXResourceManager.h"
#include "HXLoadConfigMat.h"
//#include "HXGLTextureDDS.h"
//#include "HXGLTexturePNG.h"
#include "HXGLTexture.h"
#include "HXGLTransform.h"
#include "HXRenderSystem.h"
#include "HXSceneManager.h"
#include "HXFogLinear.h"

namespace HX3D
{
	HXGLRenderable::HXGLRenderable()
	{
	}


	HXGLRenderable::~HXGLRenderable()
	{
	}

	//void HXGLRenderable::SetModelMatrix(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale)
	//{
	//	// 缩放处理S
	//	vmath::mat4 matS = vmath::scale(scale.x, scale.y, scale.z);
	//	// 旋转处理Q
	//	vmath::mat4 matX = vmath::rotate(eulerDegree.x, 1.0f, 0.0f, 0.0f);
	//	vmath::mat4 matY = vmath::rotate(eulerDegree.y, 0.0f, 1.0f, 0.0f);
	//	vmath::mat4 matZ = vmath::rotate(eulerDegree.z, 0.0f, 0.0f, 1.0f);
	//	// 平移一定要最后处理T
	//	vmath::mat4 matT = vmath::translate(pos.x, pos.y, pos.z);

	//	// 模型空间到世界空间转换 SQT(OPENGL右手坐标系，从右往左结合)
	//	mMatrixModel = matT*matX*matZ*matY*matS;
	//	// mMatrixModel = matS * matY * matZ * matX * matT;
	//}

	void HXGLRenderable::SetModelMatrix(HXMatrix44& mat)
	{
		mMatrixModel = HXGLTransform::ConvertMatrix(mat);
	}

	void HXGLRenderable::SetViewMatrix(HXICamera* pCamera)
	{
		// UVN相机
		// 为增加效率，外层计算了
		// mMatrixView = vmath::lookat(vmath::vec3(eye.x, eye.y, eye.z), vmath::vec3(at.x, at.y, at.z), vmath::vec3(up.x, up.y, up.z));
		mMatrixView = ((HXGLCamera*)pCamera)->mMatrixView;
	}

	void HXGLRenderable::SetProjectionMatrix(HXICamera* pCamera)
	{
		// 为增加效率，外层计算了
		// mMatrixProjection = vmath::frustum(left, right, bottom, top, n, f);
		mMatrixProjection = ((HXGLCamera*)pCamera)->mMatrixProjection;
	}


	GLuint texture;

	void HXGLRenderable::GenerateArguments(HXSubMesh* pSubMesh)
	{
		HXRenderable::GenerateArguments(pSubMesh);

		if (m_pSubMesh->triangleCount > MAX_TRIANGLE_COUNT)
		{
			std::cerr << "Mesh over max triangle count !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			return;
		}

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glGenBuffers(1, &mVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		
		int nVertexCount = m_pSubMesh->triangleCount * 3;
		//GLfloat positions[nVertexCount * 3] = { 0 };
		//GLfloat positions[nVertexCount][3] = { 0 };	// 静态分配编译时必须知道其数组大小

		//GLfloat positions[MAX_TRIANGLE_COUNT * 3][3] = {0};
		GLfloat* positions = new GLfloat[nVertexCount * 3];
		GLfloat* colors = new GLfloat[nVertexCount * 4];
		GLfloat* uvs = new GLfloat[nVertexCount * 2];
		GLfloat* normals = new GLfloat[nVertexCount * 3];
		int nIndex = 0;
		for (std::vector<HXVertex>::iterator itr = m_pSubMesh->vertexList.begin(); itr != m_pSubMesh->vertexList.end(); ++itr)
		{
			positions[nIndex * 3 + 0] = itr->pos.x;
			positions[nIndex * 3 + 1] = itr->pos.y;
			positions[nIndex * 3 + 2] = itr->pos.z;
			colors[nIndex * 4 + 0] = itr->color.r / 255.0f;
			colors[nIndex * 4 + 1] = itr->color.g / 255.0f;
			colors[nIndex * 4 + 2] = itr->color.b / 255.0f;
			colors[nIndex * 4 + 3] = itr->color.a / 255.0f;
			uvs[nIndex * 2 + 0] = itr->u;
			uvs[nIndex * 2 + 1] = 1.0f - itr->v;
			normals[nIndex * 3 + 0] = itr->normal.x;
			normals[nIndex * 3 + 1] = itr->normal.y;
			normals[nIndex * 3 + 2] = itr->normal.z;

			++nIndex;
		}
		
		int nSizePositions = nVertexCount * 3 * sizeof(GLfloat);
		int nSizeColors = nVertexCount * 4 * sizeof(GLfloat);
		int nSizeUVs = nVertexCount * 2 * sizeof(GLfloat);
		int nSizeNormals = nVertexCount * 3 * sizeof(GLfloat);
		glBufferData(GL_ARRAY_BUFFER, nSizePositions + nSizeColors + nSizeUVs + nSizeNormals, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, nSizePositions, positions);
		glBufferSubData(GL_ARRAY_BUFFER, nSizePositions, nSizeColors, colors);
		glBufferSubData(GL_ARRAY_BUFFER, nSizePositions + nSizeColors, nSizeUVs, uvs);
		glBufferSubData(GL_ARRAY_BUFFER, nSizePositions + nSizeColors + nSizeUVs, nSizeNormals, normals);

		delete[] positions;
		delete[] colors;
		delete[] uvs;
		delete[] normals;

		HXMaterialInfo* pMatInfo = HXResourceManager::GetInstance()->GetMaterialInfo(pSubMesh->materialName);
		std::string strVertShaderFile = pMatInfo->strShaderFile + ".vert";
		std::string strFragShaderFile = pMatInfo->strShaderFile + ".frag";

		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, strVertShaderFile.c_str() },
			{ GL_FRAGMENT_SHADER, strFragShaderFile.c_str() },
			{ GL_NONE, NULL }
		};

		program = LoadShaders(shaders);
		glUseProgram(program);

		int nTexIndex = 0;
		for (std::vector<HXMaterialProperty>::iterator itr = pMatInfo->vctMatProperty.begin(); itr != pMatInfo->vctMatProperty.end(); ++itr)
		{
			switch (itr->type)
			{
			case MPT_TEXTURE:
			{
				GLint tex_uniform_loc = glGetUniformLocation(program, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				/*HXGLTextureDDS* tex = (HXGLTextureDDS*)HXResourceManager::GetInstance()->GetTexture("GL_" + itr->value);
				if(NULL == tex)
				{
					tex = new HXGLTextureDDS(itr->value);
					HXResourceManager::GetInstance()->AddTexture("GL_" + itr->value, tex);
				}*/
				/*HXGLTexturePNG* tex = (HXGLTexturePNG*)HXResourceManager::GetInstance()->GetTexture("GL_" + itr->value);
				if (NULL == tex)
				{
					tex = new HXGLTexturePNG(itr->value);
					HXResourceManager::GetInstance()->AddTexture("GL_" + itr->value, tex);
				}*/
				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture("GL_" + itr->value);
				if (NULL == tex)
				{
					tex = new HXGLTexture(itr->value);
					HXResourceManager::GetInstance()->AddTexture("GL_" + itr->value, tex);
				}
				
				glUniform1i(tex_uniform_loc, nTexIndex);
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				// 暂时不用其他类型的Texture,这里只使用GL_TEXTURE_2D
				/*glBindTexture(tex->mImageData.target, tex->texId);
				glTexParameteri(tex->mImageData.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				vglUnloadImage(&tex->mImageData);*/
				glBindTexture(GL_TEXTURE_2D, tex->texId);

				GLint property_loc = glGetUniformLocation(program, (itr->name + "_ST").c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);

				++nTexIndex;
			}
			break;
			case MPT_FLOAT:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform1f(property_loc, itr->value1);
			}
			break;
			case MPT_FLOAT2:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform2f(property_loc, itr->value1, itr->value2);
			}
			break;
			case MPT_FLOAT3:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform3f(property_loc, itr->value1, itr->value2, itr->value3);
			}
			break;
			case MPT_FLOAT4:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);
			}
			break;
			default:
				break;
			}
		}

		render_model_matrix_loc = glGetUniformLocation(program, "model_matrix");
		render_view_matrix_loc = glGetUniformLocation(program, "view_matrix");
		render_projection_matrix_loc = glGetUniformLocation(program, "projection_matrix");
		render_mvp_matrix_loc = glGetUniformLocation(program, "mvp_matrix");

		// FOG TODO: 提取到外层
		GLint property_loc = glGetUniformLocation(program, "useFog");
		GLint nUseFog = HXSceneManager::GetInstance()->fog->useFog;
		glUniform1i(property_loc, nUseFog);
		if (nUseFog == 1)
		{
			property_loc = glGetUniformLocation(program, "fogType");
			GLint nfogType = HXSceneManager::GetInstance()->fog->fogType;
			glUniform1i(property_loc, nfogType);

			property_loc = glGetUniformLocation(program, "fogColor");
			HXCOLOR color = HXSceneManager::GetInstance()->fog->fogColor;
			glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

			if (nfogType == FOG_Linear)
			{
				HXFogLinear* fogLinear = (HXFogLinear*)HXSceneManager::GetInstance()->fog;

				property_loc = glGetUniformLocation(program, "fogStart");
				GLfloat nfogStart = fogLinear->fogStart;
				glUniform1f(property_loc, nfogStart);

				property_loc = glGetUniformLocation(program, "fogEnd");
				GLfloat nfogEnd = fogLinear->fogEnd;
				glUniform1f(property_loc, nfogEnd);
			}
		}

		property_loc = glGetUniformLocation(program, "ambient");
		HXCOLOR color = HXSceneManager::GetInstance()->lightAmbient->color;
		glUniform3f(property_loc, color.r, color.g, color.b);

		glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(0));
		glEnableVertexAttribArray(vPosition);
		glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (const void*)(nSizePositions));
		glEnableVertexAttribArray(vColor);
		glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 0, (const void*)(nSizePositions + nSizeColors));
		glEnableVertexAttribArray(vUV);
		glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(nSizePositions + nSizeColors + nSizeUVs));
		glEnableVertexAttribArray(vNormal);

		// 一定要加上，不然后续不是VBO绘制的物体无法显示
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void HXGLRenderable::Render()
	{
		if (m_pSubMesh->triangleCount > MAX_TRIANGLE_COUNT)
		{
			//std::cerr << "Mesh over max triangle count" << std::endl;
			return;
		}
		
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		//glFrontFace(GL_CW);

		// TODO:提取到material配置文件中
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		glBindVertexArray(mVAO);
		glUseProgram(program);
		glEnable(GL_TEXTURE_2D);

		if (m_pSubMesh->IsStaticMesh == false)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mVBO);

			int nVertexCount = m_pSubMesh->triangleCount * 3;			
			GLfloat* positions = new GLfloat[nVertexCount * 3];
			//GLfloat* colors = new GLfloat[nVertexCount * 4];
			int nIndex = 0;
			for (std::vector<HXVertex>::iterator itr = m_pSubMesh->vertexList.begin(); itr != m_pSubMesh->vertexList.end(); ++itr)
			{
				positions[nIndex * 3 + 0] = itr->pos.x;
				positions[nIndex * 3 + 1] = itr->pos.y;
				positions[nIndex * 3 + 2] = itr->pos.z;
				//colors[nIndex * 4 + 0] = itr->color.r / 255.0f;
				//colors[nIndex * 4 + 1] = itr->color.g / 255.0f;
				//colors[nIndex * 4 + 2] = itr->color.b / 255.0f;
				//colors[nIndex * 4 + 3] = itr->color.a / 255.0f;
				++nIndex;
			}

			//glBufferData(GL_ARRAY_BUFFER, nVertexCount * (3 + 4) * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, nVertexCount * 3 * sizeof(GLfloat), positions);
			//glBufferSubData(GL_ARRAY_BUFFER, nVertexCount * 3 * sizeof(GLfloat), nVertexCount * 4 * sizeof(GLfloat), colors);

			delete[] positions;
			//delete[] colors;
		}

		/////////////////////////////////////////////////////////////////////////////////
		//// for test  MVP后是投影平面上的坐标，之后(光栅化时?)渲染管线会自动映射到屏幕坐标
		//vmath::vec4 vec(0.5f, 0.5f, 0.5f, 1.0f);
		//vmath::mat4 matT = vmath::translate(100.0f, 0.0f, 0.0f);
		//// 为什么应用程序不能右乘，着色器里是右乘 ?  
		//// 因为vec * mMatrixModel 中的 static inline vecN<T,N> operator*(const vecN<T,M>& vec, const matNM<T,N,M>& mat)
		//// 行主序向量和列主序矩阵 主序不统一     不能用此乘法    
		//// vec = (mMatrixProjection * (mMatrixView * (mMatrixModel * vec)));
		//vmath::vec4 vec0 = vec * mMatrixModel;
		//vmath::vec4 vec1 = vec * mMatrixModel*mMatrixView;
		//vmath::vec4 vec2 = vec * mMatrixModel*mMatrixView*mMatrixProjection;
		//vmath::vec4 vec3 = vec * matT;
		//// 列主序向量: a11 a21 a31 a41  Mat[column][row]		// http://www.xuebuyuan.com/247515.html
		//// 不是列向量: 
		//// a11
		//// a12
		//// a13
		//// a14
		//// 此矩阵向量乘法是正确的  
		//vmath::vec4 vec4 = mMatrixModel * vec;		
		//vmath::vec4 vec5 = mMatrixView * mMatrixModel * vec;
		//vmath::vec4 vec6;
		//for (std::vector<HXVertex>::iterator itr = m_pSubMesh->vertexList.begin(); itr != m_pSubMesh->vertexList.end(); ++itr)
		//{
		//	vec6 = vmath::vec4(itr->pos.x, itr->pos.y, itr->pos.z, 1);
		//	vec6 = mMatrixProjection * mMatrixView * mMatrixModel * vec6;
		//	vec6[0] /= vec6[3];
		//	vec6[1] /= vec6[3];
		//	vec6[2] /= vec6[3];
		//	vec6[3] /= vec6[3];
		//	// 转换到了NDC标准设备坐标系统下了
		//	// shader顶点着色器变化后的坐标在[-1,+1]以外的都会被裁剪掉?(opengl: -w <= x <= w  -w <= y <= w  -w <= z <= w) (direct3d: -w <= x <= w  -w <= y <= w  0 <= z <= w) (标准齐次: w = 1)
		//	int test = 0;
		//}
		//vmath::vec4 vec7 = matT * vec;
		//// 矩阵间乘法正确
		//mMatrixModel*mMatrixView;
		////////////////////////////////////////////////////////////////////////////////


		// 每次渲染，状态都要重新赋值
		HXMaterialInfo* pMatInfo = HXResourceManager::GetInstance()->GetMaterialInfo(m_pSubMesh->materialName);
		int nTexIndex = 0;
		for (std::vector<HXMaterialProperty>::iterator itr = pMatInfo->vctMatProperty.begin(); itr != pMatInfo->vctMatProperty.end(); ++itr)
		{
			switch (itr->type)
			{
			case MPT_TEXTURE:
			{
				GLint tex_uniform_loc = glGetUniformLocation(program, (itr->name).c_str());
				if (tex_uniform_loc == -1)
				{
					// 未参被实际调用的变量编译后会被自动删除
					continue;
				}

				//HXGLTextureDDS* tex = (HXGLTextureDDS*)HXResourceManager::GetInstance()->GetTexture("GL_" + itr->value);
				//HXGLTexturePNG* tex = (HXGLTexturePNG*)HXResourceManager::GetInstance()->GetTexture("GL_" + itr->value);
				HXGLTexture* tex = (HXGLTexture*)HXResourceManager::GetInstance()->GetTexture("GL_" + itr->value);
				/*if (NULL == tex)
				{
					tex = new HXGLTextureDDS();
					tex->texId = vglLoadTexture((itr->value + ".dds").c_str(), 0, &(tex->mImageData));
					HXResourceManager::GetInstance()->AddTexture("GL_" + itr->value, tex);
				}*/

				glUniform1i(tex_uniform_loc, nTexIndex);
				glActiveTexture(GL_TEXTURE0 + nTexIndex);
				//glBindTexture(tex->mImageData.target, tex->texId);
				glBindTexture(GL_TEXTURE_2D, tex->texId);

				GLint property_loc = glGetUniformLocation(program, (itr->name + "_ST").c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);

				++nTexIndex;
			}
			break;
			case MPT_FLOAT:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform1f(property_loc, itr->value1);
			}
			break;
			case MPT_FLOAT2:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform2f(property_loc, itr->value1, itr->value2);
			}
			break;
			case MPT_FLOAT3:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform3f(property_loc, itr->value1, itr->value2, itr->value3);
			}
			break;
			case MPT_FLOAT4:
			{
				GLint property_loc = glGetUniformLocation(program, (itr->name).c_str());
				glUniform4f(property_loc, itr->value1, itr->value2, itr->value3, itr->value4);
			}
			break;
			default:
				break;
			}
		}

		glUniformMatrix4fv(render_model_matrix_loc, 1, GL_FALSE, mMatrixModel);
		glUniformMatrix4fv(render_view_matrix_loc, 1, GL_FALSE, mMatrixView);
		glUniformMatrix4fv(render_projection_matrix_loc, 1, GL_FALSE, mMatrixProjection);
		glUniformMatrix4fv(render_mvp_matrix_loc, 1, GL_FALSE, mMatrixProjection * mMatrixView * mMatrixModel);

		// FOG TODO: 提取到外层
		GLint property_loc = glGetUniformLocation(program, "useFog");
		GLint nUseFog = HXSceneManager::GetInstance()->fog->useFog;
		glUniform1i(property_loc, nUseFog);
		if (nUseFog == 1)
		{
			property_loc = glGetUniformLocation(program, "fogType");
			GLint nfogType = HXSceneManager::GetInstance()->fog->fogType;
			glUniform1i(property_loc, nfogType);

			property_loc = glGetUniformLocation(program, "fogColor");
			HXCOLOR color = HXSceneManager::GetInstance()->fog->fogColor;
			glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

			if (nfogType == FOG_Linear)
			{
				HXFogLinear* fogLinear = (HXFogLinear*)HXSceneManager::GetInstance()->fog;

				property_loc = glGetUniformLocation(program, "fogStart");
				GLfloat nfogStart = fogLinear->fogStart;
				glUniform1f(property_loc, nfogStart);

				property_loc = glGetUniformLocation(program, "fogEnd");
				GLfloat nfogEnd = fogLinear->fogEnd;
				glUniform1f(property_loc, nfogEnd);
			}
		}

		property_loc = glGetUniformLocation(program, "ambient");
		HXCOLOR color = HXSceneManager::GetInstance()->lightAmbient->color;
		glUniform3f(property_loc, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

		glDrawArrays(GL_TRIANGLES, 0, m_pSubMesh->triangleCount * 3);
		
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);

		// 外层 HXGLRenderSystem 已调用
		//glutSwapBuffers();
		//glutPostRedisplay();
	}
}
