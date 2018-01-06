#include "..\include\HXSceneManager.h"
#include "HXMesh.h"
#include "HXGameObject.h"
#include "HXCore.h"
#include "DiscardHXCamera.h"
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

	HXSceneManager::HXSceneManager():m_pMainCamera(NULL), fog(NULL)
	{
		mRenderList = new HXRenderList();
		Ambient = HXCOLOR(0,0,0,255);
		////mMainCamera = new HXCamera();
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
		////delete mMainCamera;
		if (m_pMainCamera)
		{
			delete m_pMainCamera;
		}

		if (fog)
		{
			delete fog;
		}
	}

	void HXSceneManager::LoadScene(std::string strSceneCfgFile)
	{
		HXLoadConfigScene cfg;
		cfg.LoadFile(strSceneCfgFile);
		// fog
		CreateFog(&cfg.mSceneInfo.fogInfo);
		// ambient
		Ambient = cfg.mSceneInfo.ambient;
		// light
		for (std::vector<HXLightInfo>::iterator itr = cfg.mSceneInfo.vctLight.begin(); itr != cfg.mSceneInfo.vctLight.end(); ++itr)
		{
			HXLightInfo info = *itr;
			CreateLight(&info);
		}
		// 创建天空盒
		 CreateSkyBox(HXVector3D(200, 200, 200));
		// GameObject
		for (std::vector<HXPrefabGameObjInfo>::iterator itr = cfg.mSceneInfo.vctGameObjInfo.begin(); itr != cfg.mSceneInfo.vctGameObjInfo.end(); ++itr)
		{
			HXPrefabGameObjInfo& prefabgoinfo = *itr;
			HXGameObject* pFatherGameObject = CreateGameObject(prefabgoinfo.strGameObjName, "", prefabgoinfo.nPriority);
			if (NULL == pFatherGameObject)
			{
				return;
			}
			if (pFatherGameObject->GetMesh())
			{
				pFatherGameObject->GetMesh()->PlayDefaultAnimation();
			}
			pFatherGameObject->SetScale(prefabgoinfo.scale);
			pFatherGameObject->SetRotation(prefabgoinfo.rotation);
			pFatherGameObject->SetPostion(prefabgoinfo.position);

			HXLoadConfigPrefab cfgPrefab;
			cfgPrefab.LoadFile(prefabgoinfo.strPrefabFile);
			for (std::vector<HXModelGameObjInfo>::iterator itr1 = cfgPrefab.mPrefabInfo.vctGameObjInfo.begin(); itr1 != cfgPrefab.mPrefabInfo.vctGameObjInfo.end(); ++itr1)
			{
				HXModelGameObjInfo& modelgoinfo = *itr1;
				HXGameObject* pGameObject = CreateGameObject(modelgoinfo.strGameObjName, modelgoinfo.strModelFile, prefabgoinfo.nPriority);
				if (NULL == pGameObject)
				{
					return;
				}
				if (pGameObject->GetMesh())
				{
					pGameObject->GetMesh()->PlayDefaultAnimation();
				}
				pGameObject->SetScale(modelgoinfo.scale);
				pGameObject->SetRotation(modelgoinfo.rotation);
				pGameObject->SetPostion(modelgoinfo.position);

				pGameObject->SetFather(pFatherGameObject);
			}
		}
	}

	/*HXGameObject* HXSceneManager::CreateGameObject(std::string strGameObjectName, std::string strMeshName)
	{
		std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.find(strGameObjectName);
		if (itr != gameObjectMap.end())
		{
			return itr->second;
		}

		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh(strMeshName);
		if (NULL != pMesh)
		{
			HXGameObject* gameObject = new HXGameObject(pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem()), HXRoot::GetInstance()->GetRenderSystem());
			gameObjectMap.insert(make_pair(strGameObjectName, gameObject));
			return gameObject;
		}
		else
		{
			return NULL;
		}
	}*/

	HXGameObject* HXSceneManager::CreateGameObject(std::string strGameObjectName, std::string strModelName, int nPriority)
	{
		std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.find(strGameObjectName);
		if (itr != gameObjectMap.end())
		{
			std::cerr << strGameObjectName + " alreay existed" << std::endl;
			return itr->second;
		}
		HXModelInfo* pModelInfo = HXResourceManager::GetInstance()->GetModelInfo(strModelName);
		if (NULL == pModelInfo)
		{
			// 当strModelName = “”时，创建不带renderable的gameobject。例如父物体空gameobject
			HXGameObject* gameObject = new HXGameObject(NULL, HXRoot::GetInstance()->GetRenderSystem());
			gameObject->m_nPriority = nPriority;
			gameObjectMap.insert(make_pair(strGameObjectName, gameObject));
			return gameObject;
		}

		// 加载FBX
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh(pModelInfo->m_strMeshFile, pModelInfo->m_strAnimFile);
		if (NULL == pMesh)
		{
			return NULL;
		}
		
		// 加载材质
		int nMatCount = 0;
		for (std::vector<std::string>::iterator itr = pModelInfo->m_vctSubMeshMat.begin(); itr != pModelInfo->m_vctSubMeshMat.end(); ++itr)
		{
			HXMaterialInfo* pMat = HXResourceManager::GetInstance()->GetMaterialInfo(*itr);
			if (NULL == pMat)
			{
				// 如果不存在该材质球，则使用粉色材质
				*itr = "./builtin/ErrorMat.xml";
				HXResourceManager::GetInstance()->GetMaterialInfo(*itr);
			}
			++nMatCount;
		}
		// 如果没材质，则添加默认材质
		if (nMatCount == 0)
		{
			pModelInfo->m_vctSubMeshMat.push_back("./builtin/ErrorMat.xml");
			HXResourceManager::GetInstance()->GetMaterialInfo("./builtin/ErrorMat.xml");
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


		HXGameObject* gameObject = new HXGameObject(pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem()), HXRoot::GetInstance()->GetRenderSystem());
		gameObject->m_nPriority = nPriority;
		gameObjectMap.insert(make_pair(strGameObjectName, gameObject));
		return gameObject;

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

	/*HXCamera* HXSceneManager::GetMainCamera()
	{
		return mMainCamera;
	}*/

	HXLight* HXSceneManager::CreateLight(HXLightInfo* lightInfo)
	{
		HXLight* pLight = new HXLight(lightInfo);
		lightVct.push_back(pLight);
		return pLight;
	}

	HXICamera* HXSceneManager::CreateMainCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
		float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
		float left, float right, float bottom, float top)
	{
		if (HXRoot::GetInstance()->GetRenderSystem())
		{
			m_pMainCamera = HXRoot::GetInstance()->GetRenderSystem()->CreateCamera(eye, at, up, ffov, nearZ, farZ, viewportWidth, viewportHeigth,
				left, right, bottom, top);
		}
		return m_pMainCamera;
	}

	HXICamera* HXSceneManager::GetMainCamera()
	{
		return m_pMainCamera;
	}


	HXGameObject* HXSceneManager::CreateSkyBox(HXVector3D scale)
	{
		std::string strgoName = "HXSkyBox";

		std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.find(strgoName);
		if (itr != gameObjectMap.end())
		{
			std::cerr << "HXSkyBox alreay existed" << std::endl;
			return itr->second;
		}

		// 创建mesh
		HXMesh* pMesh = HXResourceManager::GetInstance()->GetMesh("HXSkyBoxMesh", "");
		if (NULL == pMesh)
		{
			return NULL;
		}

		// 加载材质
		HXMaterialInfo* pMat = HXResourceManager::GetInstance()->GetMaterialInfo("./FBX/SkyBox/SkyBox.material");
		if (NULL == pMat)
		{
			return NULL;
		}

		// 关联材质到SubMesh
		pMesh->subMeshList[0]->materialName = "./FBX/SkyBox/SkyBox.material";

		HXGameObject* gameObject = new HXGameObject(pMesh->Clone(HXRoot::GetInstance()->GetRenderSystem()), HXRoot::GetInstance()->GetRenderSystem());
		gameObject->SetScale(scale);
		gameObject->m_nPriority = 0;
		gameObjectMap.insert(make_pair(strgoName, gameObject));
		return gameObject;
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

	//void HXSceneManager::Update()
	//{
	//	mMainCamera->update();

	//	//for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
	//	//{
	//	//	Local_To_World_RenderList(itr->second, mRenderList);
	//	//}
	//	//Culling_Backface_RenderList(mRenderList, mMainCamera->mFrustum);
	//	//World_To_Camera_RenderList(mRenderList, mMainCamera->mFrustum);
	//	//Camera_To_Project_RenderList(mRenderList, mMainCamera->mFrustum);
	//	//Project_To_ViewPort_RenderList(mRenderList, mMainCamera->mFrustum);
	//	////Draw_RenderList_Wire(mRenderList);
	//	//Draw_RenderList_Texture_Solid(mRenderList);

	//	HXStatus::GetInstance()->nVertexCount = 0;
	//	HXStatus::GetInstance()->nTriangleCount = 0;
	//	// TODO: 以DrawCall为单位提交渲染，以便设置渲染状态。现在暂时以SubMesh为单位提交渲染
	//	// batch处理 先填充map<Pass*,RenderableList*>，然后遍历一个pass就是一个batch
	//	for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
	//	{
	//		HXMesh* pMesh = itr->second->GetMesh();
	//		// 更新动作
	//		pMesh->UpdateAnimation();
	//		
	//		HXStatus::GetInstance()->nVertexCount += pMesh->vertexCount;
	//		HXStatus::GetInstance()->nTriangleCount += pMesh->triangleCount;

	//		for (std::vector<HXSubMesh*>::iterator itr1 = pMesh->subMeshList.begin(); itr1 != pMesh->subMeshList.end(); itr1++)
	//		{
	//			HXRenderState::Reset();
	//			HXRenderState::SetMaterial((*itr1)->materialName);

	//			(*itr1)->Insert_To_RenderList(itr->second->GetPosition(), itr->second->GetRotation(), itr->second->GetScale(), mRenderList);
	//			Culling_Backface_RenderList(mRenderList, mMainCamera->mFrustum);
	//			World_Space_Vertex_Lighting(mRenderList, &lightVct);
	//			World_To_Camera_RenderList(mRenderList, mMainCamera->mFrustum);
	//			Camera_To_Project_RenderList(mRenderList, mMainCamera->mFrustum);
	//			Project_To_ViewPort_RenderList(mRenderList, mMainCamera->mFrustum);
	//			//Draw_RenderList_Wire(mRenderList);
	//			Draw_RenderList_Texture_Solid(mRenderList);
	//		}
	//	}
	//}

	bool mycompare(HXGameObject* i, HXGameObject* j)
	{
		return( i->m_nPriority < j->m_nPriority );
	}

	void HXSceneManager::OnDisplay(bool shadow)
	{
		if (shadow)
		{
			m_pMainCamera->Update();
		}
		else
		{
			HXStatus::GetInstance()->ResetStatus();
		}
		

		// TODO: OIT排序，暂时先简单排序
		std::vector<HXGameObject*> sortGameObject;
		for (std::map<std::string, HXGameObject*>::iterator itr = gameObjectMap.begin(); itr != gameObjectMap.end(); itr++)
		{
			sortGameObject.push_back(itr->second);
		}
		std::sort(sortGameObject.begin(), sortGameObject.end(), mycompare);

		for (std::vector<HXGameObject*>::iterator itr = sortGameObject.begin(); itr != sortGameObject.end(); itr++)
		{
			// For test
			// itr->second->Yaw(itr->second->GetRotation().y + 1.0f);
			// itr->second->Roll(itr->second->GetRotation().z + 1.0f);

			// 更新坐标ModelMatrix 动作等
			(*itr)->Update();

			HXMesh* pMesh = (*itr)->GetMesh();
			if (pMesh == NULL)
			{
				continue;
			}
			// 更新动作
			//pMesh->UpdateAnimation();

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
					(*itr1)->renderable->SetViewMatrix(m_pMainCamera);
					(*itr1)->renderable->SetProjectionMatrix(m_pMainCamera);
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
		if (m_pMainCamera)
		{
			m_pMainCamera->OnViewPortResize(nScreenWidth, nScreenHeight);
		}
	}

}

