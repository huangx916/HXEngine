#pragma once
#include "HXCommon.h"
#include <map>
#include "HXLight.h"
#include "HXFogBase.h"

namespace HX3D
{
	class HXGameObject;
	class HXLight;
	struct HXRenderList;
	class HXICamera;
	struct HXFogInfo;
	struct HXGameObjectInfo;
	class HXSceneManager
	{
	public:
		static HXSceneManager* GetInstance()
		{
			if (NULL == m_pInstance)
			{
				m_pInstance = new HXSceneManager;
			}
			return m_pInstance;
		}

		~HXSceneManager();

		void LoadScene(std::string strSceneCfgFile);
		void UnLoadScene();

		void CreateGameObjectRecurve(std::vector<HXGameObjectInfo*>& list, HXGameObject* father);
		HXGameObject* CreateGameObject(HXGameObject* pFather, HXGameObjectInfo* gameobjectinfo);
		HXGameObject* GetGameObject(std::string strGameObjectName);
		std::vector<HXGameObject*> GetGameObjectList();
		// 平行光、点光源、聚光灯
		HXLight* CreateLight(HXLightInfo* lightInfo);

		HXICamera* CreateMainCamera(const HXVector3D& position, const HXVector3D& rotate,
			float nearZ = 1.0f, float farZ = 1000.0f);
		HXICamera* GetMainCamera();

		//HXGameObject* CreateSkyBox(HXVector3D scale);
		void CreateFog(HXFogInfo* info);
		void UseFog(bool useFog);

		void PushSortListRecurve(std::vector<HXGameObject*>& src, std::vector<HXGameObject*>& dest);
		void OnDisplay(bool shadow);
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
		

		HXGameObject* CreateGameObjectInEditor(HXGameObject* father, std::string strPrefabPath);
		int nameSuffix;

		// 平行光、点光源、聚光灯
		std::vector<HXLight*>		lightVct;
		// 环境光单独保存 保证唯一性
		HXCOLOR ambient;

		HXFogBase* fog;
	private:
		static HXSceneManager* m_pInstance;
		HXSceneManager();

		std::vector<HXGameObject*>	gameObjectList;
		HXRenderList*	mRenderList;
		HXICamera* m_pMainCamera;
	};
}


