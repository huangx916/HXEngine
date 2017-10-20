#pragma once
#include "HXCommon.h"

namespace HX3D
{
	struct HXAnimInfo
	{
		std::string strAnimName;
		std::string strFileName;
	};

	class HXLoadConfigAnim
	{
	public:
		HXLoadConfigAnim();
		~HXLoadConfigAnim();

		bool LoadFile(std::string strFileName);

		std::vector<HXAnimInfo> vctAnimsInfo;
	};
}