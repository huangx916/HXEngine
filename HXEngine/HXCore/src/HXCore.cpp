#include "..\include\HXCore.h"
#include "HXGameObject.h"
#include "HXMath.h"
#include "HXFrustum.h"
#include "HXGraphics.h"

namespace HX3D
{
	void Frustum_Culling_GameObject(HXGameObject* pGameObject)
	{

	}

	void Local_To_World_RenderList(HXGameObject* pGameObject, HXRenderList* pRenderList)
	{
		// TODO: GameObject从场景管理器遍历获取
		pGameObject->Insert_To_RenderList(pRenderList);
		
	}

	void World_To_Camera_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			for (int i = 0; i < 3; i++)
			{
				(*itr).vertexList[i].pos = GetVector3DMulMatrix44((*itr).vertexList[i].pos, pFrustum->matWorldToCamera);
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

	void DrawTopTriangle()
	{

	}

	void DrawBottomTriangle()
	{

	}

	void DrawTriangle(HXTriangle* triangle)
	{

	}

	void Draw_RenderList_Texture_Solid(HXRenderList* pRenderList)
	{
		for (std::list<HXTriangle>::iterator itr = pRenderList->triangleList.begin(); itr != pRenderList->triangleList.end(); ++itr)
		{
			DrawTriangle(&(*itr));
		}
	}
}