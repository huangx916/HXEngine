#pragma once
#include "HXCommon.h"

namespace HX3D
{
	struct HXModelInfo
	{
		std::string m_strMeshFile;
		std::string m_strAnimFile;
		std::vector<std::string> m_vctSubMeshMat;
	};

	class HXLoadConfigModel
	{
	public:
		HXLoadConfigModel();
		~HXLoadConfigModel();

		bool LoadFile(std::string strFileName);

		HXModelInfo mModelInfo;
	};
}
