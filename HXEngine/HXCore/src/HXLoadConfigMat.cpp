#include "..\include\HXLoadConfigMat.h"
#include "tinyxml.h"

namespace HX3D
{
	HXLoadConfigMat::HXLoadConfigMat()
	{
	}


	HXLoadConfigMat::~HXLoadConfigMat()
	{
	}

	bool HXLoadConfigMat::LoadFile(std::string strFileName)
	{
		TiXmlDocument doc(strFileName.c_str());
		bool bLoaded = doc.LoadFile();
		doc.Print();
		if (!bLoaded)
		{
			return false;
		}

		TiXmlElement* rootElement = doc.RootElement();
		TiXmlElement* shaderElement = rootElement->FirstChildElement();
		mMatInfo.strShaderFile = shaderElement->Attribute("File");
		TiXmlElement* propertyElement = shaderElement->FirstChildElement();
		for (; propertyElement != NULL; propertyElement = propertyElement->NextSiblingElement())
		{
			HXMaterialProperty matpropert;
			matpropert.type = (EMatPropertyType)atoi(propertyElement->Attribute("Type"));
			matpropert.name = propertyElement->Attribute("Name");
			matpropert.value = propertyElement->Attribute("Value");
			matpropert.value1 = atof(propertyElement->Attribute("Value1"));
			matpropert.value2 = atof(propertyElement->Attribute("Value2"));
			matpropert.value3 = atof(propertyElement->Attribute("Value3"));
			matpropert.value4 = atof(propertyElement->Attribute("Value4"));
			mMatInfo.vctMatProperty.push_back(matpropert);
		}

		return true;
	}
}