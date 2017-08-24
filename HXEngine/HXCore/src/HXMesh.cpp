#include "..\include\HXMesh.h"
#include "HXCore.h"

namespace HX3D
{

	//----------------------------------SubMesh-------------------------------------------
	HXSubMesh::HXSubMesh()
	{

	}
	HXSubMesh::~HXSubMesh()
	{

	}

	void HXSubMesh::Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList)
	{
		for (std::vector<int>::iterator itr = indexList.begin(); itr != indexList.end(); ++itr)
		{
			// TODO: 模型空间到世界空间转换
			HXTriangle triangle;
			triangle.vertexList[0] = vertexList[*itr];
			triangle.vertexList[1] = vertexList[*++itr];
			triangle.vertexList[2] = vertexList[*++itr];

			pRenderList->triangleList.push_back(triangle);
		}
	}

	//----------------------------------Mesh-------------------------------------------
	HXMesh::HXMesh()
	{
	}


	HXMesh::~HXMesh()
	{
		for (std::vector<HXSubMesh*>::iterator itr = subMeshList.begin(); itr != subMeshList.end(); itr++)
		{
			delete (*itr);
		}
	}

	void HXMesh::CreateCubeForTest()
	{
		HXSubMesh* subMesh = new HXSubMesh();
		// 立方体
		// reserve配合pushback使用	resize配合[]使用

		subMesh->vertexList.reserve(8);

		HXVertex vertex0;
		vertex0.pos = HXVector3D(-1, 1, 1);
		subMesh->vertexList.push_back(vertex0);

		HXVertex vertex1;
		vertex1.pos = HXVector3D(1, 1, 1);
		subMesh->vertexList.push_back(vertex1);

		HXVertex vertex2;
		vertex2.pos = HXVector3D(-1, 1, -1);
		subMesh->vertexList.push_back(vertex2);

		HXVertex vertex3;
		vertex3.pos = HXVector3D(1, 1, -1);
		subMesh->vertexList.push_back(vertex3);

		HXVertex vertex4;
		vertex4.pos = HXVector3D(-1, -1, 1);
		subMesh->vertexList.push_back(vertex4);

		HXVertex vertex5;
		vertex5.pos = HXVector3D(1, -1, 1);
		subMesh->vertexList.push_back(vertex5);

		HXVertex vertex6;
		vertex6.pos = HXVector3D(-1, -1, -1);
		subMesh->vertexList.push_back(vertex6);

		HXVertex vertex7;
		vertex7.pos = HXVector3D(1, -1, -1);
		subMesh->vertexList.push_back(vertex7);

		// 上0,1,3	0,3,2	前2,3,7	2,7,6	右3,1,5	3,5,7	左0,2,6	0,6,4	后1,0,4	1,4,5	下6,7,5	6,5,4
		subMesh->indexList.reserve(36);
		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(1);
		subMesh->indexList.push_back(3);

		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(3);
		subMesh->indexList.push_back(2);

		subMesh->indexList.push_back(2);
		subMesh->indexList.push_back(3);
		subMesh->indexList.push_back(7);

		subMesh->indexList.push_back(2);
		subMesh->indexList.push_back(7);
		subMesh->indexList.push_back(6);

		subMesh->indexList.push_back(3);
		subMesh->indexList.push_back(1);
		subMesh->indexList.push_back(5);

		subMesh->indexList.push_back(3);
		subMesh->indexList.push_back(5);
		subMesh->indexList.push_back(7);

		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(2);
		subMesh->indexList.push_back(6);

		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(6);
		subMesh->indexList.push_back(4);

		subMesh->indexList.push_back(1);
		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(4);

		subMesh->indexList.push_back(1);
		subMesh->indexList.push_back(4);
		subMesh->indexList.push_back(5);

		subMesh->indexList.push_back(6);
		subMesh->indexList.push_back(7);
		subMesh->indexList.push_back(5);

		subMesh->indexList.push_back(6);
		subMesh->indexList.push_back(5);
		subMesh->indexList.push_back(4);

		subMeshList.push_back(subMesh);
	}

	void HXMesh::LoadMeshFile(std::string strMeshName)
	{

	}

	void HXMesh::Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList)
	{
		for (std::vector<HXSubMesh*>::iterator itr = subMeshList.begin(); itr != subMeshList.end(); ++itr)
		{
			(*itr)->Insert_To_RenderList(pos, eulerDegree, scale, pRenderList);
		}
	}
}