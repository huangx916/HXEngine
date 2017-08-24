#include "..\include\HXSceneManager.h"
#include "HXMesh.h"
#include "HXGameObject.h"
#include "HXCore.h"
#include "HXCamera.h"
#include "HXFrustum.h"

namespace HX3D
{
	HXSceneManager* HXSceneManager::m_pInstance = NULL;

	HXSceneManager::HXSceneManager()
	{
		mRenderList = new HXRenderList();
		mMainCamera = new HXCamera();
	}


	HXSceneManager::~HXSceneManager()
	{
		for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
		{
			delete(itr->second);
		}
		gameObjectMap.clear();
		for (std::map<std::string, HXMesh*>::iterator itr = meshMap.begin(); itr != meshMap.end(); itr++)
		{
			delete(itr->second);
		}
		meshMap.clear();

		delete mRenderList;
		delete mMainCamera;
	}

	HXGameObject* HXSceneManager::CreateGameObject(std::string strGameObjectName, std::string strMeshName)
	{
		std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.find(strGameObjectName);
		if (itr != gameObjectMap.end())
		{
			return itr->second;
		}
		std::map<std::string, HXMesh*>::iterator itr1 = meshMap.find(strMeshName);
		if (itr1 != meshMap.end())
		{
			HXGameObject* gameObject = new HXGameObject((itr1->second));
			gameObjectMap.insert(make_pair(strGameObjectName, gameObject));
			return gameObject;
		}
		else
		{
			// TODO: ´´½¨MESH
			HXMesh* pMesh = new HXMesh;
			pMesh->CreateCubeForTest();
			//pMesh->LoadMeshFile(strMeshName);
			meshMap.insert(make_pair(strMeshName, pMesh));
			
			HXGameObject* gameObject = new HXGameObject((pMesh));
			gameObjectMap.insert(make_pair(strGameObjectName, gameObject));
			return gameObject;
		}
	}

	HXCamera* HXSceneManager::GetMainCamera()
	{
		return mMainCamera;
	}

	void HXSceneManager::Update()
	{
		mMainCamera->update();

		for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
		{
			Local_To_World_RenderList(itr->second, mRenderList);
		}
		World_To_Camera_RenderList(mRenderList, mMainCamera->mFrustum);
		Camera_To_Project_RenderList(mRenderList, mMainCamera->mFrustum);
		Project_To_ViewPort_RenderList(mRenderList, mMainCamera->mFrustum);
		Draw_RenderList_Wire(mRenderList);
	}

}

