#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "tinyxml.h"

namespace HX3D
{
	struct HXGameObjectInfo
	{
		HXGameObjectInfo() {}
		~HXGameObjectInfo()
		{
			for (std::vector<HXGameObjectInfo*>::iterator itr = children.begin(); itr != children.end(); ++itr)
			{
				delete (*itr);
			}
		}
		std::string strGameObjName;
		bool bActivity;
		std::string strModelFile;
		bool bCastShadow;
		bool bStatic;
		ELayer layer;
		HXVector3D position;
		HXVector3D rotation;
		HXVector3D scale;
		std::vector<HXGameObjectInfo*> children;
	};

	class HXLoadConfigPrefab
	{
	public:
		HXLoadConfigPrefab();
		~HXLoadConfigPrefab();

		bool ReadGameObjectRecurve(TiXmlElement* gameobjElement, std::vector<HXGameObjectInfo*>& list);
		bool LoadFile(std::string strFileName);

		// 最上层单个HXGameObjectInfo
		std::vector<HXGameObjectInfo*> vctGameObjInfo;
	};
}


