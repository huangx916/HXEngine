#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXMesh;
	class HXIMeshLoader
	{
	public:
		HXIMeshLoader() {};
		virtual ~HXIMeshLoader() {};
		
		virtual bool LoadMeshFromFile(std::string strFileName, std::string strAnimName, HXMesh** ppMesh) = 0;
	};
}

