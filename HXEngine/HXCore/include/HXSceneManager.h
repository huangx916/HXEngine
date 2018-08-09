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
	class HXRenderable;
	struct HXCameraInfo;
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

		HXGameObject* GetGameObjectTreeRoot();
		void CreateGameObjectRecurve(std::vector<HXGameObjectInfo*>& list, HXGameObject* father);
		HXGameObject* CreateGameObjectFromPrefab(HXGameObject* father, std::string strPrefabPath);
		HXGameObject* CreateGameObject(HXGameObject* pFather, HXGameObjectInfo* gameobjectinfo);
		bool DeleteGameObject(HXGameObject* gameobject);
		bool DeleteGameObjectRecurve(std::vector<HXGameObject*>& list, HXGameObject* gameobject);
		void InsertGameObjectToOrderQueueRecurve(HXGameObject* gameobject);

		// 平行光、点光源、聚光灯
		HXLight* CreateLight(LIGHT_TYPE type);
		bool DeleteLight(HXLight* light);
		HXLight* CreateLight(HXLightInfo* lightInfo);
		// 用于产生阴影的主平行光
		HXLight* GetMainLight();
		HXICamera* CreateMainCamera(const HXCameraInfo* cameraInfo);
		HXICamera* CreateCamera(const HXCameraInfo* cameraInfo);
		void CreateFog(HXFogInfo* info);
		void UseFog(bool useFog);

		void PushSortListRecurve(HXGameObject* src, std::vector<HXGameObject*>& dest);
		void OnDisplay(bool shadow);
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
		
		// 比较好性能，仅用于编辑器编辑时调用
		void UpdateRenderableQueue();

		// 平行光、点光源、聚光灯
		std::vector<HXLight*>		lightVct;
		// 环境光单独保存 保证唯一性
		HXCOLOR ambient;
		HXFogBase* fog;
		HXICamera* mainCamera;
		std::vector<HXICamera*>		cameraVct;

	private:
		static HXSceneManager* m_pInstance;
		HXSceneManager();

		// gameobject tree root
		HXGameObject* gameObjectTreeRoot;

		typedef std::vector<HXRenderable*> vectorRenderable;
		typedef std::map<std::string, vectorRenderable> mapStringVector;
		// opaque
		std::map<int, mapStringVector> opaqueMap;
		// transparent
		std::map<int, vectorRenderable> transparentMap;
	};
}