#include "..\include\HXLoadConfigPrefab.h"
#include "tinyxml.h"

namespace HX3D
{
	HXLoadConfigPrefab::HXLoadConfigPrefab()
	{
	}


	HXLoadConfigPrefab::~HXLoadConfigPrefab()
	{
	}

	bool HXLoadConfigPrefab::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		doc.Print();
		if (!bLoaded)
		{
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();
		TiXmlElement* gameobjElement = rootElement->FirstChildElement();
		for (; gameobjElement != NULL; gameobjElement = gameobjElement->NextSiblingElement())
		{
			HXModelGameObjInfo gameObjInfo;

			gameObjInfo.strGameObjName = gameobjElement->Attribute("Name");
			gameObjInfo.strModelFile = gameobjElement->Attribute("Model");
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

			mPrefabInfo.vctGameObjInfo.push_back(gameObjInfo);
		}

		return true;
	}
}