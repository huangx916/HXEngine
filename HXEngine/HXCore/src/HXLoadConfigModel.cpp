#include "..\include\HXLoadConfigModel.h"
#include "tinyxml.h"

namespace HX3D
{
	HXLoadConfigModel::HXLoadConfigModel()
	{
	}


	HXLoadConfigModel::~HXLoadConfigModel()
	{
	}

	bool HXLoadConfigModel::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		//doc.Print();
		if (!bLoaded)
		{
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();
		TiXmlElement* meshElement = rootElement->FirstChildElement();
		mModelInfo.m_strMeshFile = meshElement->Attribute("File");
		TiXmlElement* animElement = meshElement->NextSiblingElement();
		mModelInfo.m_strAnimFile = animElement->Attribute("File");
		TiXmlElement* matElement = animElement->NextSiblingElement();
		for (; matElement != NULL; matElement = matElement->NextSiblingElement())
		{
			mModelInfo.m_vctSubMeshMat.push_back(matElement->Attribute("File"));
		}

		return true;
	}
}