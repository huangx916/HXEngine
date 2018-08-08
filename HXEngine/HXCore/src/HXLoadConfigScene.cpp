#include "..\include\HXLoadConfigScene.h"

namespace HX3D
{
	HXLoadConfigScene::HXLoadConfigScene()
	{
	}


	HXLoadConfigScene::~HXLoadConfigScene()
	{
	}

	bool HXLoadConfigScene::ReadGameObjectRecurve(TiXmlElement* gameobjElement, std::vector<HXGameObjectInfo*>& list)
	{
		for (; gameobjElement != NULL; gameobjElement = gameobjElement->NextSiblingElement())
		{
			HXGameObjectInfo* gameObjInfo = new HXGameObjectInfo();

			gameObjInfo->strGameObjName = gameobjElement->Attribute("Name");
			gameObjInfo->bActivity = atoi(gameobjElement->Attribute("Activity"));
			gameObjInfo->bStatic = atoi(gameobjElement->Attribute("Static"));
			gameObjInfo->strModelFile = gameobjElement->Attribute("Model");
			gameObjInfo->bCastShadow = atoi(gameobjElement->Attribute("CastShadow"));
			gameObjInfo->layer = (ELayer)atoi(gameobjElement->Attribute("Layer"));
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
			ReadGameObjectRecurve(child, gameObjInfo->children);
		}
		return true;
	}

	bool HXLoadConfigScene::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		//doc.Print();
		if (!bLoaded)
		{
			std::cout << "can not load file : " + strFileName << std::endl;
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();

		// camera
		TiXmlElement* cameraElement = rootElement->FirstChildElement();
		mSceneInfo.cameraInfo.nearZ = atof(cameraElement->Attribute("NearZ"));
		mSceneInfo.cameraInfo.farZ = atof(cameraElement->Attribute("FarZ"));
		mSceneInfo.cameraInfo.clearFlag = (EClearFlag)atoi(cameraElement->Attribute("ClearFlag"));
		mSceneInfo.cameraInfo.cullingMask = (ECullingMask)atoi(cameraElement->Attribute("CullingMask"));
		mSceneInfo.cameraInfo.projection = (ECameraProjection)atoi(cameraElement->Attribute("Projection"));
		mSceneInfo.cameraInfo.depth = (ECameraProjection)atoi(cameraElement->Attribute("Depth"));
		TiXmlElement* colorElement = cameraElement->FirstChildElement();
		mSceneInfo.cameraInfo.position.x = atof(colorElement->Attribute("Cr"));
		mSceneInfo.cameraInfo.position.y = atof(colorElement->Attribute("Cg"));
		mSceneInfo.cameraInfo.position.z = atof(colorElement->Attribute("Cb"));
		TiXmlElement* eyeElement = colorElement->NextSiblingElement();
		mSceneInfo.cameraInfo.position.x = atof(eyeElement->Attribute("Px"));
		mSceneInfo.cameraInfo.position.y = atof(eyeElement->Attribute("Py"));
		mSceneInfo.cameraInfo.position.z = atof(eyeElement->Attribute("Pz"));
		TiXmlElement* atElement = eyeElement->NextSiblingElement();
		mSceneInfo.cameraInfo.rotation.x = atof(atElement->Attribute("Rx"));
		mSceneInfo.cameraInfo.rotation.y = atof(atElement->Attribute("Ry"));
		mSceneInfo.cameraInfo.rotation.z = atof(atElement->Attribute("Rz"));

		// fog
		TiXmlElement* fogElement = cameraElement->NextSiblingElement();
		mSceneInfo.fogInfo.bUse = atoi(fogElement->Attribute("Use"));
		mSceneInfo.fogInfo.type = (HXFogType)atoi(fogElement->Attribute("Type"));
		mSceneInfo.fogInfo.color.r = atof(fogElement->Attribute("R"));
		mSceneInfo.fogInfo.color.g = atof(fogElement->Attribute("G"));
		mSceneInfo.fogInfo.color.b = atof(fogElement->Attribute("B"));
		mSceneInfo.fogInfo.start = atof(fogElement->Attribute("Start"));
		mSceneInfo.fogInfo.end = atof(fogElement->Attribute("End"));

		// ambient
		TiXmlElement* ambientElement = fogElement->NextSiblingElement();
		mSceneInfo.ambient.r = atof(ambientElement->Attribute("R"));
		mSceneInfo.ambient.g = atof(ambientElement->Attribute("G"));
		mSceneInfo.ambient.b = atof(ambientElement->Attribute("B"));

		// lights
		TiXmlElement* lights = ambientElement->NextSiblingElement();
		TiXmlElement* lightElement = lights->FirstChildElement();
		for (; lightElement != NULL; lightElement = lightElement->NextSiblingElement())
		{
			HXLightInfo lightInfo;

			lightInfo.name = lightElement->Attribute("Name");
			lightInfo.isEnable = atoi(lightElement->Attribute("Enable"));
			lightInfo.lightType = (LIGHT_TYPE)atoi(lightElement->Attribute("LightType"));
			lightInfo.shininess = atof(lightElement->Attribute("Shininess"));
			lightInfo.strength = atof(lightElement->Attribute("Strength"));
			lightInfo.constantAttenuation = atof(lightElement->Attribute("constantAttenuation"));
			lightInfo.LinearAttenuation = atof(lightElement->Attribute("LinearAttenuation"));
			lightInfo.QuadraticAttenuation = atof(lightElement->Attribute("QuadraticAttenuation"));
			lightInfo.SpotCosCutoff = atof(lightElement->Attribute("SpotCosCutoff"));
			lightInfo.SpotExponent = atof(lightElement->Attribute("SpotExponent"));
			TiXmlElement* colorElement = lightElement->FirstChildElement();
			lightInfo.lightColor.r = atof(colorElement->Attribute("Cr"));
			lightInfo.lightColor.g = atof(colorElement->Attribute("Cg"));
			lightInfo.lightColor.b = atof(colorElement->Attribute("Cb"));
			TiXmlElement* positionElement = colorElement->NextSiblingElement();
			lightInfo.lightPos.x = atof(positionElement->Attribute("Px"));
			lightInfo.lightPos.y = atof(positionElement->Attribute("Py"));
			lightInfo.lightPos.z = atof(positionElement->Attribute("Pz"));
			TiXmlElement* directElement = positionElement->NextSiblingElement();
			lightInfo.lightDir.x = atof(directElement->Attribute("Dx"));
			lightInfo.lightDir.y = atof(directElement->Attribute("Dy"));
			lightInfo.lightDir.z = atof(directElement->Attribute("Dz"));
			TiXmlElement* coneDirElement = directElement->NextSiblingElement();
			lightInfo.ConeDirection.x = atof(coneDirElement->Attribute("Cx"));
			lightInfo.ConeDirection.y = atof(coneDirElement->Attribute("Cy"));
			lightInfo.ConeDirection.z = atof(coneDirElement->Attribute("Cz"));

			mSceneInfo.vctLight.push_back(lightInfo);
		}

		// gameObject
		TiXmlElement* gameobjects = lights->NextSiblingElement();
		TiXmlElement* gameobjElement = gameobjects->FirstChildElement();
		ReadGameObjectRecurve(gameobjElement, mSceneInfo.vctGameObjInfo);

		return true;
	}
}