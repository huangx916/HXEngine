#include "..\include\HXFBXLoader.h"
#include "HXMesh.h"
//#include "HXFBXMaterial.h"
#include "HXFBXMesh.h"
#include "HXResourceManager.h"
#include <Windows.h>
#include "HXFBXSkeleton.h"
#include "HXLoadConfigAnim.h"

namespace HX3D
{
	std::string HXFBXLoader::gCurPathFileName = "";

	HXFBXLoader::HXFBXLoader()
	{
		m_pFbxManager = FbxManager::Create();
		if (m_pFbxManager)
		{
			m_pScene = FbxScene::Create(m_pFbxManager, "HXScene");
			FbxIOSettings *ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
			m_pFbxManager->SetIOSettings(ios);
		}
	}

	HXFBXLoader::~HXFBXLoader()
	{
		if (m_pFbxManager)
		{
			m_pFbxManager->Destroy();
		}
		if (m_pScene)
		{
			m_pScene->Destroy();
		}
	}

	bool HXFBXLoader::LoadScene(std::string strFileName)
	{
		if (!m_pFbxManager || !m_pScene)
		{
			return false;
		}
		bool status = false;
		m_pScene->Clear();
		FbxImporter* pSceneImporter = FbxImporter::Create(m_pFbxManager, "");
		if (pSceneImporter == NULL)
		{
			return false;
		}
		status = pSceneImporter->Initialize(strFileName.c_str(), -1, m_pFbxManager->GetIOSettings());
		if (status == false)
		{
			return false;
		}
		status = pSceneImporter->Import(m_pScene);
		if (status == false)
		{
			return false;
		}

		// Convert Axis System to what is used in this example, if needed
		FbxAxisSystem SceneAxisSystem = m_pScene->GetGlobalSettings().GetAxisSystem();
		FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
		if (SceneAxisSystem != OurAxisSystem)
		{
			OurAxisSystem.ConvertScene(m_pScene);
		}

		// Convert Unit System to what is used in this example, if needed
		FbxSystemUnit SceneSystemUnit = m_pScene->GetGlobalSettings().GetSystemUnit();
		if (SceneSystemUnit.GetScaleFactor() != 1.0)
		{
			//The unit in this example is centimeter.
			//FbxSystemUnit::cm.ConvertScene(m_pScene);

			//The unit in this example is meter.
			FbxSystemUnit::m.ConvertScene(m_pScene);
		}

		// Convert mesh, NURBS and patch into triangle mesh
		FbxGeometryConverter lGeomConverter(m_pFbxManager);
		lGeomConverter.Triangulate(m_pScene, /*replace*/true);

		pSceneImporter->Destroy();

		return true;
	}

	void HXFBXLoader::ProcessNode(FbxNode* pNode, HXFBXMesh* pMesh)
	{
		if (pNode->GetNodeAttribute())
		{
			switch (pNode->GetNodeAttribute()->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
				ProcessMesh(pNode, pMesh);
				break;
			}
		}
		for (int i = 0; i < pNode->GetChildCount(); i++)
		{
			ProcessNode(pNode->GetChild(i), pMesh);
		}
	}

	void HXFBXLoader::ProcessMesh(FbxNode* pNode, HXFBXMesh* pMesh)
	{
		FbxMesh* pFbxMesh = pNode->GetMesh();
		if (pFbxMesh == NULL)
		{
			return;
		}

		//FbxAMatrix mat1 = pFbxMesh->GetNode()->EvaluateGlobalTransform();

		ProcessPolygons(pFbxMesh, pMesh);
		//ProcessMaterial(pFbxMesh);
	}

	void HXFBXLoader::ProcessPolygons(FbxMesh* pFbxMesh, HXFBXMesh* pMesh)
	{
		pMesh->Initialize(pFbxMesh);
	}

	/*void HXFBXLoader::ProcessMaterial(FbxMesh* pFbxMesh)
	{
		FbxNode * pNode = pFbxMesh->GetNode();
		if (NULL == pNode)
		{
			return;
		}
		int lMaterialCount = pNode->GetMaterialCount();
		for (int lMaterialIndex = 0; lMaterialIndex < lMaterialCount; ++lMaterialIndex)
		{
			FbxSurfaceMaterial* lMaterial = pNode->GetMaterial(lMaterialIndex);
			if (lMaterial)
			{
				std::string strMaterialName = gCurPathFileName + "|" + lMaterial->GetName();
				if (HXResourceManager::GetInstance()->GetMaterial(strMaterialName) == NULL)
				{
					HXFBXMaterial* pMaterial = new HXFBXMaterial();
					pMaterial->mMaterialName = strMaterialName;
					pMaterial->Initialize(lMaterial);
					HXResourceManager::GetInstance()->AddMaterial(strMaterialName, pMaterial);
				}
			}
		}
	}*/

	bool HXFBXLoader::LoadMeshFromFile(std::string strFileName, std::string strAnimName, HXMesh** ppMesh)
	{
		//char* pCurDir = new char[256];
		//::GetCurrentDirectory(256, pCurDir);
		//std::string strPath = pCurDir;
		//delete pCurDir;

		///*char* pCurDir1 = new char[256];
		//::GetModuleFileName(NULL, pCurDir1,256);
		//std::string strPath1 = pCurDir1;
		//delete pCurDir1;

		//FbxString lPath = FbxGetApplicationDirectory();*/

		//strFileName = strPath + "\\" + strFileName;

		gCurPathFileName = strFileName;

		*ppMesh = new HXFBXMesh();

		if (strFileName == "Cube")
		{
			(*ppMesh)->CreateCubeForTest();
		}
		else if (strFileName == "Triangle")
		{
			(*ppMesh)->CreateTriangleForTest();
		}
		else if (strFileName == "Quad")
		{
			(*ppMesh)->CreateQuadForTest();
		}
		else
		{
			// 读取模型文本文档
			if (LoadScene(strFileName) == false)
			{
				return false;
			}			
			// 加载网格数据
			ProcessNode(m_pScene->GetRootNode(), (HXFBXMesh*)*ppMesh);

			// 加载骨骼数据
			if (HXFBXSkeleton::IsHaveSkeleton(m_pScene))
			{
				// 加载骨骼
				HXFBXSkeleton* pSkeleton = new HXFBXSkeleton();
				pSkeleton->LoadSkeleton(m_pScene);
				(*ppMesh)->skeleton = pSkeleton;
				(*ppMesh)->SetMeshNotStatic();
				// 加载骨骼动画
				/*std::string strAnimConfigFile;
				int index = strFileName.find_last_of("\\");
				std::string strPath;
				if (index != -1)
				{
					strAnimConfigFile = strFileName.substr(index + 1);
					strAnimConfigFile = strAnimConfigFile.substr(0, strAnimConfigFile.length() - 4) + "Anim.xml";
					strPath = strFileName.substr(0, index + 1);
					strAnimConfigFile = strPath + strAnimConfigFile;
				}
				else
				{
					strPath = "";
					strAnimConfigFile = strFileName.substr(0, strFileName.length() - 4) + "Anim.xml";
				}*/
				HXLoadConfigAnim animConfig;
				if (animConfig.LoadFile(strAnimName))
				{
					for (std::vector<HXAnimInfo>::iterator itr = animConfig.vctAnimsInfo.begin(); itr != animConfig.vctAnimsInfo.end(); itr++)
					{
						// 读取模型文本文档
						std::string strAnimFileName = /*strPath + */itr->strFileName/* + ".FBX"*/;
						if (LoadScene(strAnimFileName) == false)
						{
							return false;
						}
						pSkeleton->LoadAnimationCurve(itr->strAnimName, m_pScene);
					}
				}
			}
		}
		return true;
	}
}