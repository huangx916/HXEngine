#pragma once
#include "HXMesh.h"

namespace HX3D
{
	class HXMeshFBX;

	class HXISkeleton
	{
	public:
		HXISkeleton();
		~HXISkeleton();

		virtual void Update() = 0;
		virtual HXISkeleton* Clone(HXMesh* pMesh) = 0;
	};
}