#include "..\include\HXCore.h"
#include "HXGameObject.h"
#include "HXMath.h"
#include "HXFrustum.h"
#include "HXGraphics.h"
#include "HXRenderState.h"
//#include "HXMaterial.h"
#include "HXLight.h"
#include "HXGDITextureBMP.h"
#include "HXLoadConfigMat.h"
#include"HXGLMaterial.h"

namespace HX3D
{
	void Frustum_Culling_GameObject(HXGameObject* pGameObject)
	{

	}

	/*void Local_To_World_RenderList(HXGameObject* pGameObject, HXRenderList* pRenderList)
	{
		pGameObject->Insert_To_RenderList(pRenderList);
	}*/

	void Culling_Backface_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); /*itr++*/)
		{
			HXVector3D u = (*itr).vertexList[0].pos - (*itr).vertexList[1].pos;
			HXVector3D v = (*itr).vertexList[0].pos - (*itr).vertexList[2].pos;
			HXVector3D normal = u.crossProduct(v);
			HXVector3D view = HXVector3D(pFrustum->transform->mLocalPostion.x, pFrustum->transform->mLocalPostion.y, pFrustum->transform->mLocalPostion.z) - (*itr).vertexList[0].pos;
			float dot = view.dotProduct(normal);
			if(dot < 0)
			{
				//pRenderList->triangleList.remove(*itr);
				//itr = pRenderList->triangleList.erase(itr);
				pRenderList->triangleList.erase(itr++);
			}
			else
			{
				itr++;
			}
		}
	}

	/*void World_Space_Vertex_Lighting(HXRenderList* pRenderList, std::vector<HXLight*>* pLightVct)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			for (int i = 0; i < 3; i++)
			{
				HXCOLOR col(0,0,0);
				for (std::vector<HXLight*>::iterator itr1 = pLightVct->begin(); itr1 != pLightVct->end(); ++itr1)
				{
					col += (*itr1)->VertexLighting(&(*itr).vertexList[i]);
				}
				(*itr).vertexList[i].color = col;
			}
		}
	}*/

	void World_To_Camera_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			for (int i = 0; i < 3; i++)
			{
				(*itr).vertexList[i].pos = GetVector3DMulMatrix44((*itr).vertexList[i].pos, pFrustum->matWorldToCamera);
				// important 为和OPENGL保持方向一致 X轴需要反向
				(*itr).vertexList[i].pos.x = -(*itr).vertexList[i].pos.x;
			}
		}
	}

	void Camera_To_Project_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum)
	{
		// 相似三角形
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			for (int i = 0; i < 3; i++)
			{
				(*itr).vertexList[i].pos.x = pFrustum->view_dist / (*itr).vertexList[i].pos.z * (*itr).vertexList[i].pos.x;
				(*itr).vertexList[i].pos.y = pFrustum->view_dist / (*itr).vertexList[i].pos.z * (*itr).vertexList[i].pos.y * pFrustum->aspect_ratio;
			}
		}
	}

	void Project_To_ViewPort_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum)
	{
		float fXOffset = 0.5f * (pFrustum->viewport_width - 1);
		float fYOffset = 0.5f * (pFrustum->viewport_heigth - 1);
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			for (int i = 0; i < 3; i++)
			{
				(*itr).vertexList[i].pos.x = fXOffset * (1 + (*itr).vertexList[i].pos.x);
				(*itr).vertexList[i].pos.y = fYOffset * (1 - (*itr).vertexList[i].pos.y);
			}
		}
	}

	void Draw_RenderList_Wire(HXRenderList* pRenderList)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			HXGraphics::GetInstance()->DrawLine((*itr).vertexList[0].pos.x, (*itr).vertexList[0].pos.y, (*itr).vertexList[1].pos.x, (*itr).vertexList[1].pos.y);
			HXGraphics::GetInstance()->DrawLine((*itr).vertexList[0].pos.x, (*itr).vertexList[0].pos.y, (*itr).vertexList[2].pos.x, (*itr).vertexList[2].pos.y);
			HXGraphics::GetInstance()->DrawLine((*itr).vertexList[1].pos.x, (*itr).vertexList[1].pos.y, (*itr).vertexList[2].pos.x, (*itr).vertexList[2].pos.y);
		}
		pRenderList->triangleList.clear();
	}
	//=============================================================================================
	void Sort_Vertex(HXVertex& v1, HXVertex& v2, HXVertex& v3)
	{
		if (v1.pos.y > v2.pos.y || (v1.pos.y == v2.pos.y && v1.pos.x > v2.pos.x))
		{
			std::swap(v1, v2);
		}
		if (v2.pos.y > v3.pos.y || (v2.pos.y == v3.pos.y && v2.pos.x > v3.pos.x))
		{
			std::swap(v2, v3);
		}
		if (v1.pos.y > v2.pos.y || (v1.pos.y == v2.pos.y && v1.pos.x > v2.pos.x))
		{
			std::swap(v1, v2);
		}
	}

	HXScanline Generate_Scanline(const HXVertex& vl, const HXVertex& vr)
	{
		int nX = vl.pos.x + 0.5f;
		int nY = vl.pos.y + 0.5f;
		float fWidth = vr.pos.x - vl.pos.x;
		HXVertex step((vr - vl)/fWidth);
		return HXScanline(vl, step, nX, nY, fWidth);
	}

	void Draw_Scanline(const HXVertex& vl, const HXVertex& vr)
	{
		HXScanline scanline = Generate_Scanline(vl, vr);
		int length = scanline.width + 0.5f;

		if (HXRenderState::m_pTex->mBitmap)
		{
			for (int i = 0; i <= length; i++)
			{
				//HXCOLOR color = pMat->GetPixelRatio(scanline.v.u, 1.0f - scanline.v.v);
				HXCOLOR color = HXRenderState::m_pTex->mBitmap->GetPixelRatio(scanline.v.u, 1.0f - scanline.v.v);

				HXGraphics::GetInstance()->SetBufferPixel(scanline.x + i, scanline.y, scanline.v.pos.z, color*scanline.v.color);
				scanline.v += scanline.step;
			}
		}
		else 
		{
			if (HXRenderState::m_pMat->mMatInfo->strShaderFile == "builtin/Error")
			{
				scanline.v.color = HXCOLOR(255, 0, 255, 255);
			}
			for (int i = 0; i <= length; i++)
			{
				HXGraphics::GetInstance()->SetBufferPixel(scanline.x + i, scanline.y, scanline.v.pos.z, scanline.v.color);
				scanline.v += scanline.step;
			}
		}		
	}

	// 平底三角形
	//		v1
	//		/\
	//	   /  \
	// v2 ------ v3
	void Draw_Flat_Bottom_Triangle(HXVertex& v1, HXVertex& v2, HXVertex& v3)
	{
		int nYBegin = v1.pos.y + 0.5f;
		int nYEnd = v3.pos.y + 0.5f;
		int nYStart = (nYBegin < 0) ? 0 : nYBegin;
		int nYStop = (nYEnd > SCREEN_HEIGHT-1) ? SCREEN_HEIGHT-1 : nYEnd;
		for (int i = nYStart; i <= nYStop; i++)
		{
			float factor = static_cast<float>(i - nYBegin) / (nYEnd - nYBegin);
			HXVertex vl = v1.interp(v2, factor);
			HXVertex vr = v1.interp(v3, factor);
			Draw_Scanline(vl, vr);
		}
	}

	// 平顶三角形
	// v1 ------ v2
	//	   \  /
	//      \/
	//		v3
	void Draw_Flat_Top_Triangle(HXVertex& v1, HXVertex& v2, HXVertex& v3)
	{
		int nYBegin = v1.pos.y + 0.5f;
		int nYEnd = v3.pos.y + 0.5f;
		int nYStart = (nYBegin < 0) ? 0 : nYBegin;
		int nYStop = (nYEnd > SCREEN_HEIGHT-1) ? SCREEN_HEIGHT-1 : nYEnd;
		for (int i = nYStart; i <= nYStop; i++)
		{
			float factor = static_cast<float>(i - nYBegin) / (nYEnd - nYBegin);
			HXVertex vl = v1.interp(v3, factor);
			HXVertex vr = v2.interp(v3, factor);
			Draw_Scanline(vl, vr);
		}
	}

	void DrawTriangle(HXVertex& v1, HXVertex& v2, HXVertex& v3)
	{
		Sort_Vertex(v1, v2, v3);
		if (v1.pos.y == v2.pos.y)
		{
			Draw_Flat_Top_Triangle(v1, v2, v3);
		}
		else if (v2.pos.y == v3.pos.y)
		{
			Draw_Flat_Bottom_Triangle(v1, v2, v3);
		}
		else
		{
			float factor = (v2.pos.y - v1.pos.y) / (v3.pos.y - v1.pos.y);
			HXVertex v4 = v1.interp(v3, factor);
			if (v4.pos.x < v2.pos.x)
			{
				std::swap(v4, v2);
			}
			Draw_Flat_Bottom_Triangle(v1,v2,v4);
			Draw_Flat_Top_Triangle(v2,v4,v3);
		}
	}

	void Draw_RenderList_Texture_Solid(HXRenderList* pRenderList)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			DrawTriangle((*itr).vertexList[0], (*itr).vertexList[1], (*itr).vertexList[2]);
		}
		pRenderList->triangleList.clear();
	}
}