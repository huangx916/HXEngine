#include "..\include\HXLoadConfigGameIni.h"
#include "tinyxml.h"

namespace HX3D
{
	HXLoadConfigGameIni::HXLoadConfigGameIni()
	{
	}

	HXLoadConfigGameIni::~HXLoadConfigGameIni()
	{
	}

	bool HXLoadConfigGameIni::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		//doc.Print();
		if (!bLoaded)
		{
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();
		renderSystem = (ERenderSystem)atoi(rootElement->Attribute("RenderSystem"));
		strScene = rootElement->Attribute("Scene");

		return true;
	}
}