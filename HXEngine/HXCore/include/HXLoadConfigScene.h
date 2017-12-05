#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	struct HXPrefabGameObjInfo
	{
		std::string strGameObjName;
		std::string strPrefabFile;
		HXVector3D position;
		HXVector3D rotation;
		HXVector3D scale;
	};
	struct HXSceneInfo
	{
		// TODO: Add Camera etc.
		std::vector<HXPrefabGameObjInfo> vctGameObjInfo;
	};

	class HXLoadConfigScene
	{
	public:
		HXLoadConfigScene();
		~HXLoadConfigScene();

		bool LoadFile(std::string strFileName);

		HXSceneInfo mSceneInfo;
	};
}