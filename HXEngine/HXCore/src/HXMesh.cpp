#include "..\include\HXMesh.h"
#include "HXCore.h"
#include "HXMatrix.h"
#include "HXMath.h"

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
			HXTriangle triangle;
			triangle.vertexList[0] = vertexList[*itr];
			triangle.vertexList[1] = vertexList[*++itr];
			triangle.vertexList[2] = vertexList[*++itr];
			
			// 缩放处理S
			HXMatrix44 matS = GetScaleMatrix44(scale.x, scale.y, scale.z);
			// 旋转处理Q
			HXMatrix44 matX = GetRotateMatrix44X(eulerDegree.x);
			HXMatrix44 matY = GetRotateMatrix44Y(eulerDegree.y);
			HXMatrix44 matZ = GetRotateMatrix44Z(eulerDegree.z);
			// 平移一定要最后处理T
			HXMatrix44 matT = GetTranslateMatrix44(pos.x, pos.y, pos.z);

			// 模型空间到世界空间转换 SQT
			HXMatrix44 mat = matS*matX*matY*matZ*matT;
			triangle.vertexList[0].pos = GetVector3DMulMatrix44(triangle.vertexList[0].pos, mat);
			triangle.vertexList[1].pos = GetVector3DMulMatrix44(triangle.vertexList[1].pos, mat);
			triangle.vertexList[2].pos = GetVector3DMulMatrix44(triangle.vertexList[2].pos, mat);

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
		vertex0.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex0);

		HXVertex vertex1;
		vertex1.pos = HXVector3D(1, 1, 1);
		vertex1.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex1);

		HXVertex vertex2;
		vertex2.pos = HXVector3D(-1, 1, -1);
		vertex2.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex2);

		HXVertex vertex3;
		vertex3.pos = HXVector3D(1, 1, -1);
		vertex3.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex3);

		HXVertex vertex4;
		vertex4.pos = HXVector3D(-1, -1, 1);
		vertex4.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex4);

		HXVertex vertex5;
		vertex5.pos = HXVector3D(1, -1, 1);
		vertex5.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex5);

		HXVertex vertex6;
		vertex6.pos = HXVector3D(-1, -1, -1);
		vertex6.color = HXCOLOR(255, 0, 0, 255);
		subMesh->vertexList.push_back(vertex6);

		HXVertex vertex7;
		vertex7.pos = HXVector3D(1, -1, -1);
		vertex7.color = HXCOLOR(255, 0, 0, 255);
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

	void HXMesh::CreateTriangleForTest()
	{
		HXSubMesh* subMesh = new HXSubMesh();
		subMesh->vertexList.reserve(3);

		HXVertex vertex0;
		vertex0.pos = HXVector3D(0, 1, 0);
		vertex0.color = HXCOLOR(255, 0, 0, 255);
		vertex0.u = 0.5f;
		vertex0.v = 1;
		subMesh->vertexList.push_back(vertex0);

		HXVertex vertex1;
		vertex1.pos = HXVector3D(1, 0, 0);
		vertex1.color = HXCOLOR(0, 255, 0, 255);
		vertex1.u = 1;
		vertex1.v = 0;
		subMesh->vertexList.push_back(vertex1);

		HXVertex vertex2;
		vertex2.pos = HXVector3D(-1, 0, 0);
		vertex2.color = HXCOLOR(0, 0, 255, 255);
		vertex2.u = 0;
		vertex2.v = 0;
		subMesh->vertexList.push_back(vertex2);

		// 顺时针方向为正面
		subMesh->indexList.reserve(3);
		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(1);
		subMesh->indexList.push_back(2);
		/*subMesh->indexList.push_back(2);
		subMesh->indexList.push_back(1);*/

		subMesh->materialName = "icon.bmp";

		subMeshList.push_back(subMesh);
	}

	void HXMesh::CreateQuadForTest()
	{
		HXSubMesh* subMesh = new HXSubMesh();
		
		// 顶点
		subMesh->vertexList.reserve(4);

		HXVertex vertex0;
		vertex0.pos = HXVector3D(-1, 1, 0);
		vertex0.color = HXCOLOR(255, 0, 0, 255);
		vertex0.u = 0;
		vertex0.v = 1;
		subMesh->vertexList.push_back(vertex0);

		HXVertex vertex1;
		vertex1.pos = HXVector3D(1, 1, 0);
		vertex1.color = HXCOLOR(0, 255, 0, 255);
		vertex1.u = 1;
		vertex1.v = 1;
		subMesh->vertexList.push_back(vertex1);

		HXVertex vertex2;
		vertex2.pos = HXVector3D(1, -1, 0);
		vertex2.color = HXCOLOR(255, 0, 0, 255);
		vertex2.u = 1;
		vertex2.v = 0;
		subMesh->vertexList.push_back(vertex2);

		HXVertex vertex3;
		vertex3.pos = HXVector3D(-1, -1, 0);
		vertex3.color = HXCOLOR(0, 0, 255, 255);
		vertex3.u = 0;
		vertex3.v = 0;
		subMesh->vertexList.push_back(vertex3);

		// 索引
		subMesh->indexList.reserve(6);

		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(1);
		subMesh->indexList.push_back(2);

		subMesh->indexList.push_back(0);
		subMesh->indexList.push_back(2);
		subMesh->indexList.push_back(3);
		
		subMesh->materialName = "icon.bmp";

		subMeshList.push_back(subMesh);
	}

	bool HXMesh::LoadMeshFile(std::string strMeshName)
	{
		if (strMeshName == "Cube")
		{
			CreateCubeForTest();
		}
		else if (strMeshName == "Triangle")
		{
			CreateTriangleForTest();
		}
		else if (strMeshName == "Quad")
		{
			CreateQuadForTest();
		}
		else
		{
			// TODO: 读取模型文本文档
		}
		return true;
	}

	void HXMesh::Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList)
	{
		for (std::vector<HXSubMesh*>::iterator itr = subMeshList.begin(); itr != subMeshList.end(); ++itr)
		{
			(*itr)->Insert_To_RenderList(pos, eulerDegree, scale, pRenderList);
		}
	}
}