#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	struct HXGameObjInfo
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
		std::vector<HXGameObjInfo> vctGameObjInfo;
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