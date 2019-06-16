#pragma once
#include "HXCommon.h"
#include "HXIMetaData.h"

namespace HX3D
{
	class HXTextureMetaData : public HXIMetaData
	{
	public:
		HXTextureMetaData();
		~HXTextureMetaData();

		virtual void ParseMetaFile(std::string strPath);
		virtual void SerializeMetaFile(std::string strPath);

		ETextureWrapMode wrapMode;
		ETextureFilterMode filterMode;
	};
}

