#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXFogBase.h"
#include "HXLight.h"
#include "tinyxml.h"
#include "HXLoadConfigPrefab.h"

namespace HX3D
{
	struct HXCameraInfo
	{
		HXVector3D position;
		HXVector3D rotation;
		float nearZ;
		float farZ;
	};
	struct HXFogInfo
	{
		bool bUse;
		HXFogType type;
		HXCOLOR color;
		float start;
		float end;
	};
	struct HXLightInfo
	{
		std::string name;

		bool isEnable;
		LIGHT_TYPE lightType;
		HXCOLOR lightColor;
		HXVector3D lightDir;
		float shininess;	// 高光尖锐程度指数
		float strength;		// 用于调整光泽度的数据

		HXVector3D lightPos;
		float constantAttenuation;	// 衰减系数
		float LinearAttenuation;
		float QuadraticAttenuation;

		HXVector3D ConeDirection;	// 聚光灯
		float SpotCosCutoff;
		float SpotExponent;
	};
	struct HXSceneInfo
	{
		HXSceneInfo() {};
		~HXSceneInfo()
		{
			// TODO: 递归删除
			for (std::vector<HXGameObjectInfo*>::iterator itr = vctGameObjInfo.begin(); itr != vctGameObjInfo.end(); ++itr)
			{
				delete (*itr);
			}
		}
		// TODO: Add other etc.
		std::vector<HXGameObjectInfo*> vctGameObjInfo;
		HXCameraInfo cameraInfo;
		HXFogInfo fogInfo;
		HXCOLOR ambient;
		std::vector<HXLightInfo> vctLight;
	};

	class HXLoadConfigScene
	{
	public:
		HXLoadConfigScene();
		~HXLoadConfigScene();

		bool ReadGameObjectRecurve(TiXmlElement* gameobjElement, std::vector<HXGameObjectInfo*>& list, int fatherPriority);
		bool LoadFile(std::string strFileName);

		HXSceneInfo mSceneInfo;
	};
}