#pragma once
#include <fbxsdk.h>
#include "HXMesh.h"

namespace HX3D
{
	class HXMeshFBX : public HXMesh
	{
	public:
		HXMeshFBX();
		~HXMeshFBX();

		bool Initialize(FbxMesh* pFbxMesh);

		void ReadVertex(FbxMesh* pFbxMesh, int nCtrlPointIndex, HXVertex& vertex);
		void ReadColor(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex);
		// TODO: ∂‡≤„UV∂¡»°
		void ReadUV(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nTextureUVIndex, HXVertex& vertex);
		void ReadNormal(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex);
	};
}