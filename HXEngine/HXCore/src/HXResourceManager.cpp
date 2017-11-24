#include "..\include\HXResourceManager.h"
#include "HXMesh.h"
//#include "HXMaterial.h"
#include "HXBitmap.h"
#include "HXIMeshLoader.h"
#include "HXFBXLoader.h"

#include "HXLoadConfigPrefab.h"
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

		for (std::map<std::string, HXMaterial*>::iterator itr = materialMap.begin(); itr != materialMap.end(); itr++)
		{
			delete itr->second;
		}
		materialMap.clear();

		for (std::map<std::string, HXBitmap*>::iterator itr = bitmapMap.begin(); itr != bitmapMap.end(); itr++)
		{
			delete itr->second;
		}
		bitmapMap.clear();

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

	/*HXMaterial* HXResourceManager::GetMaterial(std::string strMaterialName)
	{
		std::map<std::string, HXMaterial*>::iterator itr = materialMap.find(strMaterialName);
		if (itr != materialMap.end())
		{
			return itr->second;
		}
		else
		{
			HXMaterial* pMaterial = new HXMaterial;
			if (pMaterial->LoadMaterialFile(strMaterialName))
			{
				materialMap.insert(make_pair(strMaterialName, pMaterial));
				return pMaterial;
			}
			else
			{
				delete pMaterial;
				return NULL;
			}
		}
	}*/

	HXBitmap* HXResourceManager::GetBitmap(std::string strBitmap)
	{
		std::map<std::string, HXBitmap*>::iterator itr = bitmapMap.find(strBitmap);
		if (itr != bitmapMap.end())
		{
			return itr->second;
		}
		else
		{
			HXBitmap* pBitmap = new HXBitmap;
			if (pBitmap->LoadBitmapFile(strBitmap))
			{
				bitmapMap.insert(make_pair(strBitmap, pBitmap));
				return pBitmap;
			}
			else
			{
				delete pBitmap;
				return NULL;
			}
		}
	}

	void HXResourceManager::AddMaterial(std::string strMaterialName, HXMaterial* pMaterial)
	{
		materialMap.insert(make_pair(strMaterialName, pMaterial));
	}

	HXPrefabInfo* HXResourceManager::GetPrefabInfo(std::string strPrefabFile)
	{
		std::map<std::string, HXPrefabInfo*>::iterator itr = prefabMap.find(strPrefabFile);
		if (itr != prefabMap.end())
		{
			return itr->second;
		}
		else
		{
			HXLoadConfigPrefab cfg;
			if (cfg.LoadFile(strPrefabFile))
			{
				HXPrefabInfo* pPrefabInfo = new HXPrefabInfo(cfg.mPrefabInfo);
				prefabMap.insert(make_pair(strPrefabFile, pPrefabInfo));
				return pPrefabInfo;
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
