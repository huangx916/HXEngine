#include "..\include\HXSceneManager.h"
#include "HXMesh.h"
#include "HXGameObject.h"
#include "HXCore.h"
#include "HXFrustum.h"
#include "HXResourceManager.h"
#include "HXRenderState.h"
#include "HXStatus.h"
#include "HXRoot.h"
#include "HXRenderSystem.h"
#include "HXRenderable.h"
#include "HXICamera.h"
#include "HXLoadConfigModel.h"
#include "HXLoadConfigMat.h"
#include <algorithm>
#include "HXFogLinear.h"
#include "HXLoadConfigScene.h"
#include "HXLoadConfigPrefab.h"

namespace HX3D
{
	HXSceneManager* HXSceneManager::m_pInstance = NULL;

	HXSceneManager::HXSceneManager():mainCamera(NULL), fog(NULL)
	{
		ambient = HXCOLOR(0,0,0,255);
		gameObjectTreeRoot = new HXGameObject(NULL, HXRoot::GetInstance()->GetRenderSystem());
		gameObjectTreeRoot->SetName("GameObjectTreeRoot");
	}

	HXSceneManager::~HXSceneManager()
	{
		// 在HXGameObject析构函数中进行了递归卸载
		delete gameObjectTreeRoot;
		gameObjectTreeRoot = NULL;
		
		for (std::vector<HXLight*>::iterator itr = lightVct.begin(); itr != lightVct.end(); itr++)
		{
			delete *itr;
		}
		lightVct.clear();

		if (mainCamera)
		{
			delete mainCamera;
		}

		if (fog)
		{
			delete fog;
		}
	}

	void HXSceneManager::LoadScene(std::string strSceneCfgFile)
	{
		// GDI由于性能原因使用场景简单版本
		if (HXRoot::GetInstance()->GetRenderSystem() && 
			HXRoot::GetInstance()->GetRenderSystem()->GetRenderSystemType() == RenderSystem_GDI)
		{
			//strSceneCfgFile.insert(strSceneCfgFile.length() - 6, "_GDI");
			strSceneCfgFile += ".gdi";
		}

		HXLoadConfigScene cfg;
		cfg.LoadFile(strSceneCfgFile);
		// camera
		CreateMainCamera(cfg.mSceneInfo.cameraInfo.position, cfg.mSceneInfo.cameraInfo.rotation
			, cfg.mSceneInfo.cameraInfo.nearZ, cfg.mSceneInfo.cameraInfo.farZ);
		// fog
		CreateFog(&cfg.mSceneInfo.fogInfo);
		// ambient
		ambient = cfg.mSceneInfo.ambient;
		// light
		for (std::vector<HXLightInfo>::iterator itr = cfg.mSceneInfo.vctLight.begin(); itr != cfg.mSceneInfo.vctLight.end(); ++itr)
		{
			HXLightInfo info = *itr;
			CreateLight(&info);
		}

		// GameObject
		CreateGameObjectRecurve(cfg.mSceneInfo.vctGameObjInfo, gameObjectTreeRoot);
	}

	void HXSceneManager::UnLoadScene()
	{
		if (mainCamera)
		{
			delete mainCamera;
			mainCamera = NULL;
		}
		if (fog)
		{
			delete fog;
			fog = NULL;
		}
		for (std::vector<HXLight*>::iterator itr = lightVct.begin(); itr != lightVct.end(); ++itr)
		{
			delete *itr;
		}
		lightVct.clear();
		// 在HXGameObject析构函数中进行了递归卸载
		for (std::vector<HXGameObject*>::iterator itr = gameObjectTreeRoot->GetChildren().begin(); itr != gameObjectTreeRoot->GetChildren().end(); ++itr)
		{
			delete *itr;
		}
		gameObjectTreeRoot->GetChildren().clear();
	}

	void HXSceneManager::CreateGameObjectRecurve(std::vector<HXGameObjectInfo*>& list, HXGameObject* father)
	{
		for (std::vector<HXGameObjectInfo*>::iterator itr = list.begin(); itr != list.end(); ++itr)
		{
			HXGameObjectInfo* gameobjectinfo = *itr;
			HXGameObject* gameobject = CreateGameObject(father, gameobjectinfo);
			if (NULL == gameobject)
			{
				continue;
			}
			CreateGameObjectRecurve(gameobjectinfo->children, gameobject);
		}
	}

	HXGameObject* HXSceneManager::CreateGameObject(HXGameObject* pFather, HXGameObjectInfo* gameobjectinfo)
	{
		HXGameObject* gameObject = new HXGameObject(pFather, HXRoot::GetInstance()->GetRenderSystem());
		gameObject->Initialize(gameobjectinfo);
		InsertGameObjectToOrderQueue(gameObject);
		return gameObject;
	}

	HXGameObject* HXSceneManager::GetGameObjectTreeRoot()
	{
		return gameObjectTreeRoot;
	}

	void HXSceneManager::InsertGameObjectToOrderQueue(HXGameObject* gameobject)
	{
		HXMesh* pMesh = gameobject->GetMesh();
		if (pMesh == NULL)
		{
			return;
		}
		int renderQueue = gameobject->m_nRenderQueue;

		if (renderQueue < ERenderQueue::RQ_TRANSPARENT)
		{
			// opaque
			for (std::vector<HXSubMesh*>::iterator itr = pMesh->subMeshList.begin(); itr != pMesh->subMeshList.end(); itr++)
			{
				HXSubMesh* subMesh = (*itr);
				std::string materialName = subMesh->materialName;
				std::map<int, mapStringVector>::iterator itr1 = opaqueMap.find(renderQueue);
				if (itr1 != opaqueMap.end())
				{
					mapStringVector::iterator itr2 = itr1->second.find(materialName);
					if (itr2 != itr1->second.end())
					{
						itr2->second.push_back(subMesh->renderable);
					}
					else
					{
						vectorRenderable vct;
						vct.push_back(subMesh->renderable);
						itr1->second.insert(std::make_pair(materialName, vct));
					}
				}
				else
				{
					mapStringVector sv;
					vectorRenderable vct;
					vct.push_back(subMesh->renderable);
					sv.insert(std::make_pair(materialName, vct));
					opaqueMap.insert(std::make_pair(renderQueue, sv));
				}
			}
		}
		else
		{
			// transparent
			for (std::vector<HXSubMesh*>::iterator itr = pMesh->subMeshList.begin(); itr != pMesh->subMeshList.end(); itr++)
			{
				HXSubMesh* subMesh = (*itr);
				std::map<int, vectorRenderable>::iterator itr1 = transparentMap.find(renderQueue);
				if (itr1 != transparentMap.end())
				{
					itr1->second.push_back(subMesh->renderable);
				}
				else
				{
					vectorRenderable vct;
					vct.push_back(subMesh->renderable);
					transparentMap.insert(std::make_pair(renderQueue, vct));
				}
			}
		}
	}

	HXLight* HXSceneManager::CreateLight(HXLightInfo* lightInfo)
	{
		HXLight* pLight = new HXLight(lightInfo);
		lightVct.push_back(pLight);
		return pLight;
	}

	HXICamera* HXSceneManager::CreateMainCamera(const HXVector3D& position, const HXVector3D& rotate,
		float nearZ, float farZ)
	{
		if (HXRoot::GetInstance()->GetRenderSystem())
		{
			mainCamera = HXRoot::GetInstance()->GetRenderSystem()->CreateCamera(position, rotate, nearZ, farZ);
		}
		return mainCamera;
	}

	void HXSceneManager::CreateFog(HXFogInfo* info)
	{
		if (info->type == HXFogType::FOG_Linear)
		{
			fog = new HXFogLinear(info);
		}
	}

	void HXSceneManager::UseFog(bool useFog)
	{
		if (fog)
		{
			fog->useFog = useFog;
		}
	}

	bool mycompare(HXGameObject* i, HXGameObject* j)
	{
		return( i->m_nRenderQueue < j->m_nRenderQueue );
	}

	void HXSceneManager::PushSortListRecurve(HXGameObject* src, std::vector<HXGameObject*>& dest)
	{
		dest.push_back(src);
		for (std::vector<HXGameObject*>::iterator itr = src->GetChildren().begin(); itr != src->GetChildren().end(); itr++)
		{
			PushSortListRecurve(*itr, dest);
		}
	}

	void HXSceneManager::OnDisplay(bool shadow)
	{
		if (!mainCamera)
		{
			return;
		}
		HXRenderSystem* pRenderSystem = HXRoot::GetInstance()->GetRenderSystem();
		if (NULL == pRenderSystem)
		{
			return;
		}


		if (shadow)
		{
			mainCamera->Update();
			HXStatus::GetInstance()->ResetStatus();
		}
		
		// TODO: 暂时先简单排序
		std::vector<HXGameObject*> sortGameObject;
		PushSortListRecurve(gameObjectTreeRoot, sortGameObject);
		std::sort(sortGameObject.begin(), sortGameObject.end(), mycompare);

		for (std::vector<HXGameObject*>::iterator itr = sortGameObject.begin(); itr != sortGameObject.end(); itr++)
		{
			// 更新坐标ModelMatrix 动作等
			if (shadow)
			{
				(*itr)->Update();
			}
			
			if (shadow && !(*itr)->GetCastShadow())
			{
				continue;
			}

			HXMesh* pMesh = (*itr)->GetMesh();
			if (pMesh == NULL)
			{
				continue;
			}

			HXStatus::GetInstance()->nVertexCount += pMesh->vertexCount;
			HXStatus::GetInstance()->nTriangleCount += pMesh->triangleCount;

			for (std::vector<HXSubMesh*>::iterator itr1 = pMesh->subMeshList.begin(); itr1 != pMesh->subMeshList.end(); itr1++)
			{
				(*itr1)->renderable->SetModelMatrix((*itr)->GetTransform()->mCurModelMatrix);
				(*itr1)->renderable->SetViewMatrix(mainCamera);
				(*itr1)->renderable->SetProjectionMatrix(mainCamera);
				pRenderSystem->RenderSingle((*itr1)->renderable, shadow);
			}
		}

		

		//for (std::map<int, mapStringVector>::iterator itr = opaqueMap.begin(); itr != opaqueMap.end(); ++itr)
		//{
		//	for (mapStringVector::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
		//	{
		//		std::string strMaterialName = itr1->first;
		//		// TODO: SetMaterialRenderStateAllRenderable
		//		for (vectorRenderable::iterator itr2 = itr1->second.begin(); itr2 != itr1->second.end(); ++itr2)
		//		{
		//			HXRenderable* renderable = *itr2;
		//			// TODO: SetMaterialRenderStateEachRenderable
		//			pRenderSystem->RenderSingle(renderable, shadow);
		//		}
		//	}
		//}



		if (!shadow)
		{
			HXStatus::GetInstance()->ShowStatusInfo();
		}
	}

	void HXSceneManager::OnViewPortResize(int nScreenWidth, int nScreenHeight)
	{
		if (mainCamera)
		{
			mainCamera->OnViewPortResize(nScreenWidth, nScreenHeight);
		}
	}

	HXGameObject* HXSceneManager::CreateGameObjectFromPrefab(HXGameObject* father, std::string strPrefabPath)
	{
		HXLoadConfigPrefab cfgPrefab;
		cfgPrefab.LoadFile(strPrefabPath);
		if (cfgPrefab.vctGameObjInfo.size() > 0)
		{
			// 最上层一个HXGameObjectInfo就够了
			HXGameObjectInfo* gameobjectinfo = cfgPrefab.vctGameObjInfo[0];
			if (NULL == gameobjectinfo)
			{
				return NULL;
			}
			HXGameObject* gameobject = CreateGameObject(father, gameobjectinfo);
			if (gameobject)
			{
				CreateGameObjectRecurve(gameobjectinfo->children, gameobject);
			}
			return gameobject;
		}
		return NULL;
	}

	bool HXSceneManager::DeleteGameObject(HXGameObject* gameobject)
	{
		return DeleteGameObjectRecurve(gameObjectTreeRoot->GetChildren(), gameobject);
	}

	bool HXSceneManager::DeleteGameObjectRecurve(std::vector<HXGameObject*>& list, HXGameObject* gameobject)
	{
		for (std::vector<HXGameObject*>::iterator itr = list.begin(); itr != list.end(); ++itr)
		{
			if ((*itr) == gameobject)
			{
				list.erase(itr);
				delete gameobject;
				gameobject = NULL;
				return true;
			}
			if (DeleteGameObjectRecurve((*itr)->GetChildren(), gameobject))
			{
				return true;
			}
		}
		return false;
	}
}

