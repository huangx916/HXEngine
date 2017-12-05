#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	struct HXModelGameObjInfo
	{
		std::string strGameObjName;
		std::string strModelFile;
		HXVector3D position;
		HXVector3D rotation;
		HXVector3D scale;
	};
	struct HXPrefabInfo
	{
		// TODO: Add Camera etc.
		std::vector<HXModelGameObjInfo> vctGameObjInfo;
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


