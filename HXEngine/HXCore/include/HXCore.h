#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMesh.h"


namespace HX3D
{
#define EOBJECT_STATE_CULLED	0x0001

	class HXGameObject;
	class HXFrustum;

	struct HXTriangle
	{		
		HXVertex vertexList[3];
	};

	struct HXRenderList 
	{
		std::list<HXTriangle> triangleList;
		// typedef std::list<HXTriangle>::iterator Itr;
	};
	
	// CullSphere(只需把中心点转换到视图空间进行判断)
	void Frustum_Culling_GameObject(HXGameObject* pGameObject);
	// 顶点从模型空间到世界空间转换并出入到渲染列表
	void Local_To_World_RenderList(HXGameObject* pGameObject, HXRenderList* pRenderList);
	void World_To_Camera_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum);
	void Camera_To_Project_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum);
	void Project_To_ViewPort_RenderList(HXRenderList* pRenderList, HXFrustum* pFrustum);
	void Draw_RenderList_Wire(HXRenderList* pRenderList);
	void Draw_RenderList_Texture_Solid(HXRenderList* pRenderList);
}


