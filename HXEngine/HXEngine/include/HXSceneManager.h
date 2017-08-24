#pragma once
#include "HXCommon.h"
#include <map>


namespace HX3D
{
	class HXCamera;
	class HXGameObject;
	class HXMesh;
	class HXRenderList;

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

		HXCamera* GetMainCamera();

		void Update();
		
	private:
		static HXSceneManager* m_pInstance;
		HXSceneManager();

		std::map<std::string, HXGameObject*>	gameObjectMap;
		std::map<std::string, HXMesh*>	meshMap;
		HXRenderList*	mRenderList;
		HXCamera*	mMainCamera;
	};
}


