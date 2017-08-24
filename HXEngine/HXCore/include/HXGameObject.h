#pragma once
#include "HXCommon.h"
#include "HXVector.h"


namespace HX3D
{
	class HXMesh;
	class HXRenderList;

	class HXGameObject
	{
	public:
		HXGameObject(HXMesh* pMesh);
		~HXGameObject();
	
		void Insert_To_RenderList(HXRenderList* pRenderList);

		HXVector3D mPostion;
		HXVector3D mEulerDegree;
		HXVector3D mScale;

		HXMesh* m_pMesh;
	};
}


