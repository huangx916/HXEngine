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

		HXGameObject* CreateGameObject(HXGameObject* pFather, std::string strGameObjectName, std::string strModelName, int nPriority, bool bCastShadow);
		HXGameObject* GetGameObject(std::string strGameObjectName);
		// 平行光、点光源、聚光灯
		HXLight* CreateLight(HXLightInfo* lightInfo);
		HXICamera* CreateMainCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up = HXVector3D(0, 1, 0),
			float ffov = 90.0f, float nearZ = 1.0f, float farZ = 1000.0f, 
			float viewportWidth = SCREEN_WIDTH, float viewportHeigth = SCREEN_HEIGHT,
			float left = -1.0f, float right = 1.0f, 
			float bottom = -(float)SCREEN_HEIGHT / (float)SCREEN_WIDTH, float top = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH);
		HXICamera* GetMainCamera();

		HXGameObject* CreateSkyBox(HXVector3D scale);
		void CreateFog(HXFogInfo* info);
		void UseFog(bool useFog);

		void OnDisplay(bool shadow);
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
		

		void LoadGameObjectInEditor(std::string strPath);
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


