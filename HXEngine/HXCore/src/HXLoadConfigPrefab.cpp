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
		TiXmlElement* meshElement = rootElement->FirstChildElement();
		mPrefabInfo.m_strMeshFile = meshElement->Attribute("File");
		TiXmlElement* animElement = meshElement->NextSiblingElement();
		mPrefabInfo.m_strAnimFile = animElement->Attribute("File");
		TiXmlElement* matElement = animElement->NextSiblingElement();
		for (; matElement != NULL; matElement = matElement->NextSiblingElement())
		{
			mPrefabInfo.m_vctSubMeshMat.push_back(matElement->Attribute("File"));
		}

		return true;
	}
}