#include "..\include\HXSceneManager.h"
#include "HXMesh.h"
#include "HXGameObject.h"
#include "HXCore.h"
#include "HXCamera.h"
#include "HXFrustum.h"
#include "HXResourceManager.h"
#include "HXRenderState.h"

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
		
		for (std::vector<HXLight*>::iterator itr = lightVct.begin(); itr != lightVct.end(); itr++)
		{
			delete *itr;
		}
		lightVct.clear();

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

		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh(strMeshName);
		if (NULL != pMesh)
		{
			HXGameObject* gameObject = new HXGameObject(pMesh->Clone());
			gameObjectMap.insert(make_pair(strGameObjectName, gameObject));
			return gameObject;
		}
		else
		{
			return NULL;
		}
	}

	HXGameObject* HXSceneManager::GetGameObject(std::string strGameObjectName)
	{
		std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.find(strGameObjectName);
		if (itr != gameObjectMap.end())
		{
			return itr->second;
		}
		return NULL;
	}

	HXCamera* HXSceneManager::GetMainCamera()
	{
		return mMainCamera;
	}

	HXLight* HXSceneManager::CreateLight(LIGHT_TYPE lightType)
	{
		HXLight* pLight = new HXLight(lightType);
		lightVct.push_back(pLight);
		return pLight;
	}

	void HXSceneManager::Update()
	{
		mMainCamera->update();

		//for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
		//{
		//	Local_To_World_RenderList(itr->second, mRenderList);
		//}
		//Culling_Backface_RenderList(mRenderList, mMainCamera->mFrustum);
		//World_To_Camera_RenderList(mRenderList, mMainCamera->mFrustum);
		//Camera_To_Project_RenderList(mRenderList, mMainCamera->mFrustum);
		//Project_To_ViewPort_RenderList(mRenderList, mMainCamera->mFrustum);
		////Draw_RenderList_Wire(mRenderList);
		//Draw_RenderList_Texture_Solid(mRenderList);

		// TODO: 以DrawCall为单位提交渲染，以便设置渲染状态。现在暂时以SubMesh为单位提交渲染
		for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
		{
			HXMesh* pMesh = itr->second->GetMesh();
			// 更新动作
			pMesh->UpdateAnimation();
			for (std::vector<HXSubMesh*>::iterator itr1 = pMesh->subMeshList.begin(); itr1 != pMesh->subMeshList.end(); itr1++)
			{
				HXRenderState::Reset();
				HXRenderState::SetMaterial((*itr1)->materialName);

				(*itr1)->Insert_To_RenderList(itr->second->GetPosition(), itr->second->GetRotation(), itr->second->GetScale(), mRenderList);
				Culling_Backface_RenderList(mRenderList, mMainCamera->mFrustum);
				World_Space_Vertex_Lighting(mRenderList, &lightVct);
				World_To_Camera_RenderList(mRenderList, mMainCamera->mFrustum);
				Camera_To_Project_RenderList(mRenderList, mMainCamera->mFrustum);
				Project_To_ViewPort_RenderList(mRenderList, mMainCamera->mFrustum);
				// Draw_RenderList_Wire(mRenderList);
				Draw_RenderList_Texture_Solid(mRenderList);
			}
		}
	}

}

