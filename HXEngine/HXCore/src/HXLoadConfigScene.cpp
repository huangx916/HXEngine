#include "..\include\HXLoadConfigScene.h"
#include "tinyxml.h"

namespace HX3D
{
	HXLoadConfigScene::HXLoadConfigScene()
	{
	}


	HXLoadConfigScene::~HXLoadConfigScene()
	{
	}

	bool HXLoadConfigScene::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		//doc.Print();
		if (!bLoaded)
		{
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();
		TiXmlElement* prefabs = rootElement->FirstChildElement();
		TiXmlElement* gameobjElement = prefabs->FirstChildElement();
		for (; gameobjElement != NULL; gameobjElement = gameobjElement->NextSiblingElement())
		{
			HXPrefabGameObjInfo gameObjInfo;

			gameObjInfo.strGameObjName = gameobjElement->Attribute("Name");
			gameObjInfo.strPrefabFile = gameobjElement->Attribute("Prefab");
			gameObjInfo.nPriority = atoi(gameobjElement->Attribute("Priority"));
			TiXmlElement* positionElement = gameobjElement->FirstChildElement();
			gameObjInfo.position.x = atof(positionElement->Attribute("Px"));
			gameObjInfo.position.y = atof(positionElement->Attribute("Py"));
			gameObjInfo.position.z = atof(positionElement->Attribute("Pz"));
			TiXmlElement* rotationElement = positionElement->NextSiblingElement();
			gameObjInfo.rotation.x = atof(rotationElement->Attribute("Rx"));
			gameObjInfo.rotation.y = atof(rotationElement->Attribute("Ry"));
			gameObjInfo.rotation.z = atof(rotationElement->Attribute("Rz"));
			TiXmlElement* scaleElement = rotationElement->NextSiblingElement();
			gameObjInfo.scale.x = atof(scaleElement->Attribute("Sx"));
			gameObjInfo.scale.y = atof(scaleElement->Attribute("Sy"));
			gameObjInfo.scale.z = atof(scaleElement->Attribute("Sz"));
		
			mSceneInfo.vctGameObjInfo.push_back(gameObjInfo);
		}
		TiXmlElement* fogElement = prefabs->NextSiblingElement();
		mSceneInfo.fogInfo.bUse = atoi(fogElement->Attribute("Use"));
		mSceneInfo.fogInfo.type = (HXFogType)atoi(fogElement->Attribute("Type"));
		mSceneInfo.fogInfo.color.r = atof(fogElement->Attribute("R"));
		mSceneInfo.fogInfo.color.g = atof(fogElement->Attribute("G"));
		mSceneInfo.fogInfo.color.b = atof(fogElement->Attribute("B"));
		mSceneInfo.fogInfo.start = atof(fogElement->Attribute("Start"));
		mSceneInfo.fogInfo.end = atof(fogElement->Attribute("End"));
		return true;
	}
}