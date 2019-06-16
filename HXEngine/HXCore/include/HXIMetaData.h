#pragma once
#include "HXCommon.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;

namespace HX3D
{
	class HXIMetaData
	{
	public:
		HXIMetaData() 
		{
			version = Version;
			uuid = "0";
		};
		virtual ~HXIMetaData() {};

		virtual void ParseMetaFile(std::string strPath) = 0;

		std::string version;	// TODO:
		std::string uuid;	// TODO:
	};
}

