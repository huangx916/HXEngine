#include "..\include\HXResourceManager.h"
#include "HXMesh.h"
#include "HXBitmap.h"
#include "HXIMeshLoader.h"
#include "HXFBXLoader.h"

#include "HXLoadConfigModel.h"
#include "HXLoadConfigMat.h"

namespace HX3D
{
	HXResourceManager* HXResourceManager::m_pInstance = NULL;

	HXResourceManager::HXResourceManager()
	{
		m_pMeshLoader = new HXFBXLoader();
	}


	HXResourceManager::~HXResourceManager()
	{
		for (std::map<std::string, HXMesh*>::iterator itr = meshMap.begin(); itr != meshMap.end(); itr++)
		{
			delete(itr->second);
		}
		meshMap.clear();

		if (m_pMeshLoader)
		{
			delete m_pMeshLoader;
			m_pMeshLoader = NULL;
		}
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

	HXMaterialInfo* HXResourceManager::GetMaterialInfo(std::string strMaterialFile)
	{
		std::map<std::string, HXMaterialInfo*>::iterator itr = matMap.find(strMaterialFile);
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
				matMap.insert(make_pair(strMaterialFile, pMatInfo));
				return pMatInfo;
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
}
