#pragma once
#include "HXCommon.h"
#include "HXIMeshLoader.h"
#include <fbxsdk.h>

namespace HX3D
{
	class HXMesh;
	class HXMeshFBX;
	class HXVertex;
	class HXFBXLoader : public HXIMeshLoader
	{
	public:
		HXFBXLoader();
		~HXFBXLoader();

		bool LoadScene(std::string strFileName);
		void ProcessNode(FbxNode* pNode, HXMeshFBX* pMesh);
		void ProcessMesh(FbxNode* pNode, HXMeshFBX* pMesh);
		// 读取顶点坐标、颜色、UV、法线等。划分SUBMESH。关联材质名。
		void ProcessPolygons(FbxMesh* pFbxMesh, HXMeshFBX* pMesh);
		// 读取加载材质和贴图
		void ProcessMaterial(FbxMesh* pFbxMesh);
		virtual bool LoadMeshFromFile(std::string strFileName, HXMesh** ppMesh);

		// 用于保存Material及Mesh唯一名字
		static std::string gCurPathFileName;
	private:
		FbxManager* m_pFbxManager;
		FbxScene* m_pScene;
		
	};
}