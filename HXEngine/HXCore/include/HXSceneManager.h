#pragma once
#include "HXCommon.h"
#include <map>
#include "HXLight.h"


namespace HX3D
{
	////class HXCamera;
	class HXGameObject;
	class HXLight;
	struct HXRenderList;
	class HXICamera;
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

		//HXGameObject* CreateGameObject(std::string strGameObjectName, std::string strMeshName);
		HXGameObject* CreateGameObject(std::string strGameObjectName, std::string strModelName, int nPriority);
		HXGameObject* GetGameObject(std::string strGameObjectName);
		////HXCamera* GetMainCamera();
		// 平行光、点光源、聚光灯
		HXLight* CreateLight(LIGHT_TYPE lightType);
		// 环境光单独保存
		void CreateAmbient(const HXCOLOR& color);
		HXICamera* CreateMainCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up = HXVector3D(0, 1, 0),
			float ffov = 90.0f, float nearZ = 1.0f, float farZ = 1000.0f, 
			float viewportWidth = SCREEN_WIDTH, float viewportHeigth = SCREEN_HEIGHT,
			float left = -1.0f, float right = 1.0f, 
			float bottom = -(float)SCREEN_HEIGHT / (float)SCREEN_WIDTH, float top = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH);
		HXICamera* GetMainCamera();

		HXGameObject* CreateSkyBox(HXVector3D scale);
		void UseFog(bool useFog);

		//void Update();
		void OnDisplay();
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
		

		// 平行光、点光源、聚光灯
		std::vector<HXLight*>		lightVct;
		// 环境光单独保存 保证唯一性
		HXLight* lightAmbient;
	private:
		static HXSceneManager* m_pInstance;
		HXSceneManager();

		std::map<std::string, HXGameObject*>	gameObjectMap;
		////HXCamera*	mMainCamera;
		HXRenderList*	mRenderList;
		HXICamera* m_pMainCamera;
	};
}


