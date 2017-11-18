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

		HXGameObject* CreateGameObject(std::string strGameObjectName, std::string strMeshName);
		HXGameObject* GetGameObject(std::string strGameObjectName);
		////HXCamera* GetMainCamera();
		HXLight* CreateLight(LIGHT_TYPE lightType);
		HXICamera* CreateMainCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up = HXVector3D(0, 1, 0),
			float ffov = 75.0f, float nearZ = 1.0f, float farZ = 1000.0f, 
			float viewportWidth = SCREEN_WIDTH, float viewportHeigth = SCREEN_HEIGHT,
			float left = -1.0f, float right = 1.0f, 
			float bottom = -(float)SCREEN_HEIGHT / (float)SCREEN_WIDTH, float top = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH);
		HXICamera* GetMainCamera();

		//void Update();
		void OnDisplay();
		void OnViewPortResize(int nScreenWidth, int nScreenHeight);
		
	private:
		static HXSceneManager* m_pInstance;
		HXSceneManager();

		std::map<std::string, HXGameObject*>	gameObjectMap;
		std::vector<HXLight*>		lightVct;
		////HXCamera*	mMainCamera;
		HXRenderList*	mRenderList;
		HXICamera* m_pMainCamera;
	};
}


