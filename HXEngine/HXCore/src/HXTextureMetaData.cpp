#include "..\include\HXTextureMetaData.h"

namespace HX3D
{
	HXTextureMetaData::HXTextureMetaData()
	{
		wrapMode = ETextureWrapMode::TWM_REPEAT;
		filterMode = ETextureFilterMode::TFM_BILINEAR;
	}

	HXTextureMetaData::~HXTextureMetaData()
	{
	}

	void HXTextureMetaData::ParseMetaFile(std::string strPath)
	{
		std::ifstream t(strPath);
		if (!t.is_open())
		{
			SerializeMetaFile(strPath);
			return;
		}
		std::stringstream buffer;
		buffer << t.rdbuf();
		std::string contents(buffer.str());
		auto j = json::parse(contents);
		version = j["version"].get<string>();
		uuid = j["uuid"].get<string>();
		wrapMode = (ETextureWrapMode)j["wrapMode"].get<int>();
		filterMode = (ETextureFilterMode)j["filterMode"].get<int>();
	}

	void HXTextureMetaData::SerializeMetaFile(std::string strPath)
	{

	}
}
