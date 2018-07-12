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
		gameObjectTreeRoot = new HXGameObject("GameObjectTreeRoot", NULL, HXRoot::GetInstance()->GetRenderSystem());
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
		HXModelInfo* pModelInfo = HXResourceManager::GetInstance()->GetModelInfo(gameobjectinfo->strModelFile);
		if (NULL == pModelInfo)
		{
			// 当strModelName = ""时，创建不带renderable的gameobject。例如父物体空gameobject
			HXGameObject* gameObject = new HXGameObject(gameobjectinfo->strGameObjName, NULL, HXRoot::GetInstance()->GetRenderSystem());
			gameObject->m_nPriority = gameobjectinfo->nPriority;
			gameObject->m_bCastShadow = gameobjectinfo->bCastShadow;
			
			if (NULL == pFather)
			{
				pFather = gameObjectTreeRoot;
			}
			pFather->AddChild(gameObject);
			
			gameObject->SetFather(pFather);

			gameObject->GetTransform()->SetScale(gameobjectinfo->scale);
			gameObject->GetTransform()->SetRotation(gameobjectinfo->rotation);
			gameObject->GetTransform()->SetPosition(gameobjectinfo->position);

			gameObject->m_strModelFile = gameobjectinfo->strModelFile;

			return gameObject;
		}

		// 加载FBX
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh(pModelInfo->m_strMeshFile, pModelInfo->m_strAnimFile);
		if (NULL == pMesh)
		{
			std::cout << pModelInfo->m_strMeshFile << " not exist" << std::endl;
			return NULL;
		}
		
		// 加载材质
		int nMatCount = 0;
		for (std::vector<std::string>::iterator itr = pModelInfo->m_vctSubMeshMat.begin(); itr != pModelInfo->m_vctSubMeshMat.end(); ++itr)
		{
			HXMaterial* pMat = HXResourceManager::GetInstance()->GetMaterial(*itr);
			if (NULL == pMat)
			{
				// 如果不存在该材质球，则使用粉色材质
				*itr = "./prefab/_Material/Error/Error.material";
				HXResourceManager::GetInstance()->GetMaterial(*itr);
			}
			++nMatCount;
		}
		// 如果没材质，则添加默认材质
		if (nMatCount == 0)
		{
			pModelInfo->m_vctSubMeshMat.push_back("./prefab/_Material/Error/Error.material");
			HXResourceManager::GetInstance()->GetMaterial("./prefab/_Material/Error/Error.material");
		}
		
		// 关联材质到SubMesh
		int nSubMeshIndex = 0;
		for (std::vector<HXSubMesh*>::iterator itr = pMesh->subMeshList.begin(); itr != pMesh->subMeshList.end(); ++itr)
		{
			if (nSubMeshIndex < nMatCount)
			{
				pMesh->subMeshList[nSubMeshIndex]->materialName = pModelInfo->m_vctSubMeshMat[nSubMeshIndex];
			}
			else
			{
				// 如果子网格数大于材质数，多出来的子网格使用第一个材质
				pMesh->subMeshList[nSubMeshIndex]->materialName = pModelInfo->m_vctSubMeshMat[0];
			}
			++nSubMeshIndex;
		}

		HXGameObject* gameObject = new HXGameObject(gameobjectinfo->strGameObjName, pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem()), HXRoot::GetInstance()->GetRenderSystem());
		gameObject->m_nPriority = gameobjectinfo->nPriority;
		gameObject->m_bCastShadow = gameobjectinfo->bCastShadow;
		
		if (NULL == pFather)
		{
			pFather = gameObjectTreeRoot;
		}
		pFather->AddChild(gameObject);
		
		gameObject->SetFather(pFather);

		gameObject->GetTransform()->SetScale(gameobjectinfo->scale);
		gameObject->GetTransform()->SetRotation(gameobjectinfo->rotation);
		gameObject->GetTransform()->SetPosition(gameobjectinfo->position);

		gameObject->m_strModelFile = gameobjectinfo->strModelFile;

		gameObject->GetMesh()->PlayDefaultAnimation();

		return gameObject;
	}

	HXGameObject* HXSceneManager::GetGameObjectTreeRoot()
	{
		return gameObjectTreeRoot;
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
		return( i->m_nPriority < j->m_nPriority );
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
			
			if (shadow && !(*itr)->m_bCastShadow)
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
				HXRenderSystem* pRenderSystem = HXRoot::GetInstance()->GetRenderSystem();
				if (pRenderSystem)
				{
					//(*itr1)->renderable->SetModelMatrix(itr->second->GetPosition(), itr->second->GetRotation(), itr->second->GetScale());
					(*itr1)->renderable->SetModelMatrix((*itr)->GetTransform()->mCurModelMatrix);
					// TODO: 提取到外层Camera里增加效率   Just for test here
					(*itr1)->renderable->SetViewMatrix(mainCamera);
					(*itr1)->renderable->SetProjectionMatrix(mainCamera);
					pRenderSystem->RenderSingle((*itr1)->renderable, shadow);
				}
			}
		}

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

	HXGameObject* HXSceneManager::CreateGameObjectInEditor(HXGameObject* father, std::string strPrefabPath)
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

