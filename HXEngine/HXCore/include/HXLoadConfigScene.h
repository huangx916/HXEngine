#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXFogBase.h"
#include "HXLight.h"

namespace HX3D
{
	struct HXPrefabGameObjInfo
	{
		std::string strGameObjName;
		std::string strPrefabFile;
		int nPriority;
		bool bCastShadow;
		HXVector3D position;
		HXVector3D rotation;
		HXVector3D scale;
	};
	struct HXCameraInfo
	{
		HXVector3D eye;
		HXVector3D at;
		HXVector3D up;
		float ffov;
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
		// TODO: Add other etc.
		std::vector<HXPrefabGameObjInfo> vctGameObjInfo;
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

		bool LoadFile(std::string strFileName);

		HXSceneInfo mSceneInfo;
	};
}