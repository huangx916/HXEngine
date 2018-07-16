#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXLoadConfigGameIni
	{
	public:
		HXLoadConfigGameIni();
		~HXLoadConfigGameIni();

		bool LoadFile(std::string strFileName);

		ERenderSystem renderSystem;
		std::string strScene;
	};
}