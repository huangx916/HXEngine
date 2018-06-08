#pragma once
#include "HXCommon.h"
#include <map>

namespace HX3D
{
	class HXMesh;
	class HXMaterial;
	class HXBitmap;
	class HXIMeshLoader;
	class HXModelInfo;
	class HXMaterialInfo;
	class HXITexture;
	class HXResourceManager
	{
	public:
		static HXResourceManager* GetInstance()
		{
			if (NULL == m_pInstance)
			{
				m_pInstance = new HXResourceManager();
			}
			return m_pInstance;
		}
		~HXResourceManager();

		HXMesh* GetMesh(std::string strMeshName, std::string strAnimName);

		HXModelInfo* GetModelInfo(std::string strModelFile);
		HXMaterialInfo* GetMaterialInfo(std::string strMaterialFile);
		HXITexture* GetTexture(std::string strTextureFile);
		void AddTexture(std::string strTextureFile, HXITexture* pTexture);

	private:
		HXResourceManager();
		static HXResourceManager* m_pInstance;

		HXIMeshLoader*	m_pMeshLoader;

		std::map<std::string, HXModelInfo*> ModelMap;
		std::map<std::string, HXMesh*>	meshMap;
		std::map<std::string, HXMaterialInfo*> matMap;
		std::map<std::string, HXITexture*> textureMap;
	};
}


