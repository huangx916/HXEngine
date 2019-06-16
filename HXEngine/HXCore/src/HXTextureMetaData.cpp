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
		std::ifstream i(strPath);
		if (!i.is_open())
		{
			SerializeMetaFile(strPath);
			return;
		}
		json j;
		i >> j;

		/*std::stringstream buffer;
		buffer << i.rdbuf();
		std::string contents(buffer.str());
		auto j = json::parse(contents);*/

		version = j["version"].get<string>();
		uuid = j["uuid"].get<string>();
		wrapMode = (ETextureWrapMode)j["wrapMode"].get<int>();
		filterMode = (ETextureFilterMode)j["filterMode"].get<int>();
		i.close();
	}

	void HXTextureMetaData::SerializeMetaFile(std::string strPath)
	{
		json j;
		j["version"] = version;
		j["uuid"] = uuid;
		j["wrapMode"] = wrapMode;
		j["filterMode"] = filterMode;

		std::ofstream o(strPath);
		if (o.is_open())
		{
			o << j.dump(4) << endl;
			o.flush();
			o.close();
		}
	}
}
