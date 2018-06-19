#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMatrix.h"
#include "HXITransform.h"

namespace HX3D
{
	class HXMesh;
	struct HXRenderList;
	class HXRenderSystem;
	class HXGameObject
	{
	public:
		HXGameObject(std::string strName, HXMesh* pMesh, HXRenderSystem* pRenderSystem);
		~HXGameObject();
	
		void Update();

		//void Insert_To_RenderList(HXRenderList* pRenderList);

		std::string GetName() { return m_strName; }
		HXMesh* GetMesh();
		HXGameObject* GetFather();
		void SetFather(HXGameObject* father);
		void AddChild(HXGameObject* child);
		std::vector<HXGameObject*> GetChildren();
		HXITransform* GetTransform();

		// 渲染优先级
		int m_nPriority;
		bool m_bCastShadow;
		std::string m_strPrefab;
		
	private:
		std::string m_strName;
		// Local Coordinate
		HXITransform* m_pTransform;

		HXMesh* m_pMesh;
		// TODO: config中暂时只支持两层 prefabgameobj--->modelgameobj
		HXGameObject* m_pFather;	// 用作计算World Coordinate
		std::vector<HXGameObject*> vctChildren;
	};
}


