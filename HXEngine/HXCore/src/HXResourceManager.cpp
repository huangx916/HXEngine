#include "..\include\HXResourceManager.h"
#include "HXMesh.h"
#include "HXBitmap.h"
#include "HXIMeshLoader.h"
#include "HXFBXLoader.h"
#include "HXMaterial.h"
#include "HXLoadConfigModel.h"
#include "HXLoadConfigMat.h"
#include "HXRoot.h"
#include "HXRenderSystem.h"
#include "HXGLPreprocessHandler.h"

namespace HX3D
{
	HXResourceManager* HXResourceManager::m_pInstance = NULL;

	HXResourceManager::HXResourceManager()
	{
		m_pMeshLoader = new HXFBXLoader();
		preprocessHandler = new HXGLPreprocessHandler();
	}

	HXResourceManager::~HXResourceManager()
	{
		for (std::map<std::string, HXMesh*>::iterator itr = meshMap.begin(); itr != meshMap.end(); itr++)
		{
			delete(itr->second);
		}
		meshMap.clear();

		HX_SAFE_DELETE(m_pMeshLoader);
		HX_SAFE_DELETE(preprocessHandler);
	}

	HXMesh* HXResourceManager::GetMesh(std::string strMeshName, std::string strAnimName)
	{
		std::map<std::string, HXMesh*>::iterator itr = meshMap.find(strMeshName);
		if (itr != meshMap.end())
		{
			return itr->second;
		}
		else
		{
			HXMesh* pMesh = NULL;
			if (m_pMeshLoader->LoadMeshFromFile(strMeshName, strAnimName, &pMesh))
			{
				meshMap.insert(make_pair(strMeshName, pMesh));
				return pMesh;
			}
			else
			{
				delete pMesh;
				return NULL;
			}
		}
	}

	HXModelInfo* HXResourceManager::GetModelInfo(std::string strModelFile)
	{
		std::map<std::string, HXModelInfo*>::iterator itr = ModelMap.find(strModelFile);
		if (itr != ModelMap.end())
		{
			return itr->second;
		}
		else
		{
			HXLoadConfigModel cfg;
			if (cfg.LoadFile(strModelFile))
			{
				HXModelInfo* pModelInfo = new HXModelInfo(cfg.mModelInfo);
				ModelMap.insert(make_pair(strModelFile, pModelInfo));
				return pModelInfo;
			}
		}
		return NULL;
	}

	HXMaterial* HXResourceManager::GetMaterial(std::string strMaterialFile)
	{
		std::map<std::string, HXMaterial*>::iterator itr = matMap.find(strMaterialFile);
		if (itr != matMap.end())
		{
			return itr->second;
		}
		else
		{
			HXLoadConfigMat cfg;
			if (cfg.LoadFile(strMaterialFile))
			{
				HXMaterialInfo* pMatInfo = new HXMaterialInfo(cfg.mMatInfo);
				HXMaterial* mat = HXRoot::GetInstance()->GetRenderSystem()->CreateMaterial(pMatInfo);
				matMap.insert(make_pair(strMaterialFile, mat));
				return mat;
			}
		}

		return NULL;
	}

	HXITexture* HXResourceManager::GetTexture(std::string strTextureFile)
	{
		std::map<std::string, HXITexture*>::iterator itr = textureMap.find(strTextureFile);
		if (itr != textureMap.end())
		{
			return itr->second;
		}
		return NULL;
	}

	void HXResourceManager::AddTexture(std::string strTextureFile, HXITexture* pTexture)
	{
		textureMap.insert(make_pair(strTextureFile, pTexture));
	}

	void HXResourceManager::UnLoadAll()
	{
		for (std::map<std::string, HXModelInfo*>::iterator itr = ModelMap.begin(); itr != ModelMap.end(); ++itr)
		{
			delete itr->second;
		}
		ModelMap.clear();
		for (std::map<std::string, HXMesh*>::iterator itr = meshMap.begin(); itr != meshMap.end(); ++itr)
		{
			delete itr->second;
		}
		meshMap.clear();
		for (std::map<std::string, HXMaterial*>::iterator itr = matMap.begin(); itr != matMap.end(); ++itr)
		{
			delete itr->second;
		}
		matMap.clear();
		for (std::map<std::string, HXITexture*>::iterator itr = textureMap.begin(); itr != textureMap.end(); ++itr)
		{
			delete itr->second;
		}
		textureMap.clear();

		ResetPreprocess();
	}

	void HXResourceManager::Preprocess(std::string strERMapFile)
	{
		preprocessHandler->Preprocess(strERMapFile);
	}

	void HXResourceManager::ResetPreprocess()
	{
		HX_SAFE_DELETE(preprocessHandler);
		preprocessHandler = new HXGLPreprocessHandler();
	}

	HXGLPreprocessHandler* HXResourceManager::GetPreprocessHandler()
	{
		return preprocessHandler;
	}
}
