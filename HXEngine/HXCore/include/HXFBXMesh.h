#pragma once
#include <fbxsdk.h>
#include "HXMesh.h"

namespace HX3D
{
	class HXFBXMesh : public HXMesh
	{
	public:
		HXFBXMesh();
		~HXFBXMesh();

		bool Initialize(FbxMesh* pFbxMesh);
		void UpdateVertexPosition(const FbxVector4* pVertices);
		virtual HXMesh* Clone(HXRenderSystem* pRenderSystem);
		

	private:
		void ReadVertex(FbxMesh* pFbxMesh, int nCtrlPointIndex, HXVertex& vertex);
		void ReadColor(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex);
		// TODO: 多层UV读取
		void ReadUV(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nTextureUVIndex, HXVertex& vertex);
		void ReadNormal(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex);

		// important 跟导出时坐标系转换有关(同一个mesh下的所有submesh这个矩阵都一样的)包含轴对换、缩放、旋转、位移等
		FbxAMatrix matrixMeshGlobalPositionIn3DMax;

		// 新的成员变量clone时要赋值
	};
}