#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXFogBase.h"

namespace HX3D
{
	struct HXPrefabGameObjInfo
	{
		std::string strGameObjName;
		std::string strPrefabFile;
		int nPriority;
		HXVector3D position;
		HXVector3D rotation;
		HXVector3D scale;
	};
	struct HXFogInfo
	{
		bool bUse;
		HXFogType type;
		HXCOLOR color;
		float start;
		float end;
	};
	struct HXSceneInfo
	{
		// TODO: Add Camera etc.
		std::vector<HXPrefabGameObjInfo> vctGameObjInfo;
		HXFogInfo fogInfo;
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