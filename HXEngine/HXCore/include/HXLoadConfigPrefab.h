#pragma once
#include "HXCommon.h"

namespace HX3D
{
	struct HXPrefabInfo
	{
		std::string m_strMeshFile;
		std::string m_strAnimFile;
		std::vector<std::string> m_vctSubMeshMat;
	};
	class HXLoadConfigPrefab
	{
	public:
		HXLoadConfigPrefab();
		~HXLoadConfigPrefab();

		bool LoadFile(std::string strFileName);

		HXPrefabInfo mPrefabInfo;
	};
}


