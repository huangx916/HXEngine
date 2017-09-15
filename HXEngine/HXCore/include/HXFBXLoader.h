#pragma once
#include "HXCommon.h"
#include "HXIMeshLoader.h"
#include <fbxsdk.h>

namespace HX3D
{
	class HXMesh;
	class HXVertex;
	class HXFBXLoader : public HXIMeshLoader
	{
	public:
		HXFBXLoader();
		~HXFBXLoader();

		bool LoadScene(std::string strFileName);
		void ProcessNode(FbxNode* pNode, HXMesh* pMesh);
		void ProcessMesh(FbxNode* pNode, HXMesh* pMesh);
		void ReadVertex(FbxMesh* pFbxMesh, int nCtrlPointIndex, HXVertex& vertex);
		void ReadColor(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex);
		// TODO: ∂‡≤„UV∂¡»°
		void ReadUV(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nTextureUVIndex, HXVertex& vertex);
		void ReadNormal(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex);
		virtual bool LoadMeshFromFile(std::string strFileName, HXMesh* pMesh);

	private:
		FbxManager* m_pFbxManager;
		FbxScene* m_pScene;
	};
}