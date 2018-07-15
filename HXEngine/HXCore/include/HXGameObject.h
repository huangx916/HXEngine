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
	class HXGameObjectInfo;
	class HXGameObject
	{
	public:
		HXGameObject(HXGameObject* pFather, HXRenderSystem* pRenderSystem);
		~HXGameObject();
	
		void Initialize(HXGameObjectInfo* gameobjectinfo);

		void Update();

		//void Insert_To_RenderList(HXRenderList* pRenderList);

		std::string GetName() { return m_strName; }
		void SetName(std::string strName) { m_strName = strName; }
		HXMesh* GetMesh();
		HXGameObject* GetFather();
		void SetFather(HXGameObject* father);
		void AddChild(HXGameObject* child);
		std::vector<HXGameObject*>& GetChildren();
		HXITransform* GetTransform();
		bool GetCastShadow() const;
		void SetCastShadow(bool bCastShadow);
		int GetRenderQueue() const;
		void SetRenderQueue(int nRenderQueue);

		std::string m_strName;
		std::string m_strModelFile;
		
	private:
		// Local Coordinate
		HXITransform* m_pTransform;
		bool m_bCastShadow;
		int m_nRenderQueue;	// 渲染优先级
		HXMesh* m_pMesh;
		HXGameObject* m_pFather;	// 用作计算World Coordinate
		std::vector<HXGameObject*> vctChildren;
	};
}


