#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	class HXRenderList;

	struct HXVertex
	{
		HXVector3D pos;
		HXCOLOR	color;
	};

	class HXSubMesh
	{
	public:
		HXSubMesh();
		~HXSubMesh();

		void Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList);

		std::vector<HXVertex>	vertexList;
		std::vector<int>	indexList;
	};

	class HXMesh
	{
	public:
		HXMesh();
		~HXMesh();

		// For Test
		void CreateCubeForTest();

		void LoadMeshFile(std::string strMeshName);

		void Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList);

		std::vector<HXSubMesh*> subMeshList;
	};
}


