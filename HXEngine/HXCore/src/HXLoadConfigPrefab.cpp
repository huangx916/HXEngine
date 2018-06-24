#include "..\include\HXLoadConfigPrefab.h"
#include "tinyxml.h"

namespace HX3D
{
	HXLoadConfigPrefab::HXLoadConfigPrefab()
	{

	}

	HXLoadConfigPrefab::~HXLoadConfigPrefab()
	{
		// TODO: µÝ¹édelete vctGameObjInfo
	}

	bool HXLoadConfigPrefab::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		//doc.Print();
		if (!bLoaded)
		{
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();
		TiXmlElement* gameobjElement = rootElement->FirstChildElement();

		ReadGameObjectRecurve(gameobjElement, vctGameObjInfo, 0);

		return true;
	}

	bool HXLoadConfigPrefab::ReadGameObjectRecurve(TiXmlElement* gameobjElement, std::vector<HXGameObjectInfo*>& list, int fatherPriority)
	{
		for (; gameobjElement != NULL; gameobjElement = gameobjElement->NextSiblingElement())
		{
			HXGameObjectInfo* gameObjInfo = new HXGameObjectInfo();

			gameObjInfo->strGameObjName = gameobjElement->Attribute("Name");
			gameObjInfo->strModelFile = gameobjElement->Attribute("Model");
			gameObjInfo->nPriority = atoi(gameobjElement->Attribute("Priority")) + fatherPriority;
			gameObjInfo->bCastShadow = atoi(gameobjElement->Attribute("CastShadow"));
			TiXmlElement* positionElement = gameobjElement->FirstChildElement();
			gameObjInfo->position.x = atof(positionElement->Attribute("Px"));
			gameObjInfo->position.y = atof(positionElement->Attribute("Py"));
			gameObjInfo->position.z = atof(positionElement->Attribute("Pz"));
			TiXmlElement* rotationElement = positionElement->NextSiblingElement();
			gameObjInfo->rotation.x = atof(rotationElement->Attribute("Rx"));
			gameObjInfo->rotation.y = atof(rotationElement->Attribute("Ry"));
			gameObjInfo->rotation.z = atof(rotationElement->Attribute("Rz"));
			TiXmlElement* scaleElement = rotationElement->NextSiblingElement();
			gameObjInfo->scale.x = atof(scaleElement->Attribute("Sx"));
			gameObjInfo->scale.y = atof(scaleElement->Attribute("Sy"));
			gameObjInfo->scale.z = atof(scaleElement->Attribute("Sz"));

			list.push_back(gameObjInfo);

			TiXmlElement* child = scaleElement->NextSiblingElement();
			ReadGameObjectRecurve(child, gameObjInfo->children, gameObjInfo->nPriority);
		}
		return true;
	}
}