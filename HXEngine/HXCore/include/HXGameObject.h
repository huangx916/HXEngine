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
		bool GetActivity() const;
		void SetActivity(bool activity);
		bool GetCastShadow() const;
		void SetCastShadow(bool bCastShadow);
		void SetCastShadowRecurve(bool bCastShadow);
		bool GetStatic() const;
		void SetStatic(bool bStatic);
		void SetStaticRecurve(bool bStatic);
		ELayer GetLayer() const;
		void SetLayer(ELayer eLayer);
		void SetLayerRecurve(ELayer eLayer);

		std::string m_strName;
		std::string m_strModelFile;
		
	private:
		bool m_bActivity;
		bool m_bStatic;
		ELayer layer;
		// Local Coordinate
		HXITransform* m_pTransform;
		bool m_bCastShadow;
		HXMesh* m_pMesh;
		HXGameObject* m_pFather;	// ÓÃ×÷¼ÆËãWorld Coordinate
		std::vector<HXGameObject*> vctChildren;
	};
}


