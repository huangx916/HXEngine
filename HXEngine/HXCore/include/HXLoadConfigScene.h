#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXFog.h"
#include "HXLight.h"
#include "tinyxml.h"
#include "HXLoadConfigPrefab.h"

namespace HX3D
{
	struct HXCameraInfo
	{
		std::string name;
		bool enable;
		EClearFlag clearFlag;
		HXCOLOR background;
		ECullingMask cullingMask;
		ECameraProjection projection;
		float feild;
		float size;
		float nearZ;
		float farZ;
		float viewportRectX;
		float viewportRectY;
		float viewportRectW;
		float viewportRectH;
		int depth;
		HXVector3D position;
		HXVector3D rotation;
	};
	struct HXFogInfo
	{
		bool bUse;
		HXFogType type;
		HXCOLOR color;
		float start;
		float end;
		float density;
		float gradiant;
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
			// 已在析构函数里递归删除
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
		std::vector<HXCameraInfo> vctCamera;
	};

	class HXLoadConfigScene
	{
	public:
		HXLoadConfigScene();
		~HXLoadConfigScene();

		bool ReadGameObjectRecurve(TiXmlElement* gameobjElement, std::vector<HXGameObjectInfo*>& list);
		bool LoadFile(std::string strFileName);

		HXSceneInfo mSceneInfo;
	};
}