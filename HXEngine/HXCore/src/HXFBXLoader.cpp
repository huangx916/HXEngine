#include "..\include\HXFBXLoader.h"
#include "HXMesh.h"

namespace HX3D
{
	HXFBXLoader::HXFBXLoader()
	{
		m_pFbxManager = FbxManager::Create();
		if (m_pFbxManager)
		{
			m_pScene = FbxScene::Create(m_pFbxManager, "HXScene");
			FbxIOSettings *ios = FbxIOSettings::Create(m_pFbxManager, IOSROOT);
			m_pFbxManager->SetIOSettings(ios);
		}
	}

	HXFBXLoader::~HXFBXLoader()
	{
		if (m_pFbxManager)
		{
			m_pFbxManager->Destroy();
		}
		if (m_pScene)
		{
			m_pScene->Destroy();
		}
	}

	bool HXFBXLoader::LoadScene(std::string strFileName)
	{
		if (!m_pFbxManager || !m_pScene)
		{
			return false;
		}
		bool status = false;
		m_pScene->Clear();
		FbxImporter* pSceneImporter = FbxImporter::Create(m_pFbxManager, "");
		if (pSceneImporter == NULL)
		{
			return false;
		}
		status = pSceneImporter->Initialize(strFileName.c_str(), -1, m_pFbxManager->GetIOSettings());
		if (status == false)
		{
			return false;
		}
		status = pSceneImporter->Import(m_pScene);
		if (status == false)
		{
			return false;
		}
		pSceneImporter->Destroy();
		return true;
	}

	void HXFBXLoader::ProcessNode(FbxNode* pNode, HXMesh* pMesh)
	{
		if (pNode->GetNodeAttribute())
		{
			switch (pNode->GetNodeAttribute()->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
				ProcessMesh(pNode, pMesh);
				break;
			}
		}
		for (int i = 0; i < pNode->GetChildCount(); i++)
		{
			ProcessNode(pNode->GetChild(i), pMesh);
		}
	}

	void HXFBXLoader::ProcessMesh(FbxNode* pNode, HXMesh* pMesh)
	{
		FbxMesh* pFbxMesh = pNode->GetMesh();
		if (pFbxMesh == NULL)
		{
			return;
		}

		/*FbxVector4 fbxScale = pFbxMesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
		HXVector3D scale = HXVector3D(fbxScale.mData[0], fbxScale.mData[1], fbxScale.mData[2]);*/
		
		//FbxSystemUnit sceneSystemUnit = m_pScene->GetGlobalSettings().GetSystemUnit();
		/*if (sceneSystemUnit.GetScaleFactor() != 1.0)
		{
			FbxSystemUnit::cm.ConvertScene(m_pScene);
		}*/
		//double scale = sceneSystemUnit.GetScaleFactor();

		int nTriangleCount = pFbxMesh->GetPolygonCount();
		int nVertexCounter = 0;

		// TODO: 如何划分subMesh
		HXSubMesh* subMesh = new HXSubMesh();
		subMesh->useIndex = false;
		subMesh->vertexList.reserve(nTriangleCount*3);
		pMesh->subMeshList.push_back(subMesh);

		// for test
		subMesh->materialName = "BC_Gong.bmp";

		for (int i = 0; i < nTriangleCount; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				HXVertex vertex;

				int nCtrlPointIndex = pFbxMesh->GetPolygonVertex(i, j);
				int nTextureUVIndex = pFbxMesh->GetTextureUVIndex(i, j);
				// TODO: 读取比例因子矩阵乘以顶点坐标（3DMAX系统单位设置不同，顶点坐标会不同，需要乘以比例因子）
				// 顶点坐标会转化为系统设置单位，乘以比例因子后是导出时选择的单位
				// 3DMAX中调整单位及轴等，导出时需要重置变换
				// Read the vertex
				ReadVertex(pFbxMesh, nCtrlPointIndex, vertex);
				// Read the color of each vertex
				ReadColor(pFbxMesh, nCtrlPointIndex, nVertexCounter, vertex);
				// Read the UV of each vertex  
				ReadUV(pFbxMesh, nCtrlPointIndex, nTextureUVIndex, vertex);
				// Read the normal of each vertex
				ReadNormal(pFbxMesh, nCtrlPointIndex, nVertexCounter, vertex);
				// Read the tangent of each vertex  

				subMesh->vertexList.push_back(vertex);
				nVertexCounter++;
			}
		}
	}

	void HXFBXLoader::ReadVertex(FbxMesh* pFbxMesh, int nCtrlPointIndex, HXVertex& vertex)
	{
		FbxVector4* pCtrlPoint = pFbxMesh->GetControlPoints();
		vertex.pos.x = pCtrlPoint[nCtrlPointIndex][0];
		vertex.pos.y = pCtrlPoint[nCtrlPointIndex][1];
		vertex.pos.z = pCtrlPoint[nCtrlPointIndex][2];
	}

	void HXFBXLoader::ReadColor(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex)
	{
		if (pFbxMesh->GetElementVertexColorCount() < 1)
		{
			return;
		}

		FbxGeometryElementVertexColor* pVertexColor = pFbxMesh->GetElementVertexColor(0);
		switch (pVertexColor->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
		{
			switch (pVertexColor->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				vertex.color.r = pVertexColor->GetDirectArray().GetAt(nCtrlPointIndex)[0];
				vertex.color.g = pVertexColor->GetDirectArray().GetAt(nCtrlPointIndex)[1];
				vertex.color.b = pVertexColor->GetDirectArray().GetAt(nCtrlPointIndex)[2];
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int nId = pVertexColor->GetIndexArray().GetAt(nCtrlPointIndex);
				vertex.color.r = pVertexColor->GetDirectArray().GetAt(nId)[0];
				vertex.color.g = pVertexColor->GetDirectArray().GetAt(nId)[1];
				vertex.color.b = pVertexColor->GetDirectArray().GetAt(nId)[2];
			}
			break;
			default:
				break;
			}
		}
		break;
		case FbxGeometryElement::eByPolygonVertex:
		{
			switch (pVertexColor->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				vertex.color.r = pVertexColor->GetDirectArray().GetAt(nVertexCounter)[0];
				vertex.color.g = pVertexColor->GetDirectArray().GetAt(nVertexCounter)[1];
				vertex.color.b = pVertexColor->GetDirectArray().GetAt(nVertexCounter)[2];
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int nId = pVertexColor->GetIndexArray().GetAt(nVertexCounter);
				vertex.color.r = pVertexColor->GetDirectArray().GetAt(nId)[0] * 255.0f;
				vertex.color.g = pVertexColor->GetDirectArray().GetAt(nId)[1] * 255.0f;
				vertex.color.b = pVertexColor->GetDirectArray().GetAt(nId)[2] * 255.0f;
			}
			break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		}
	}

	void HXFBXLoader::ReadUV(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nTextureUVIndex, HXVertex& vertex)
	{
		if (pFbxMesh->GetElementUVCount() < 1)
		{
			return;
		}

		FbxGeometryElementUV* pVertexUV = pFbxMesh->GetElementUV(0);
		switch (pVertexUV->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
		{
			switch (pVertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				vertex.u = pVertexUV->GetDirectArray().GetAt(nCtrlPointIndex)[0];
				vertex.v = pVertexUV->GetDirectArray().GetAt(nCtrlPointIndex)[1];
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int nId = pVertexUV->GetIndexArray().GetAt(nCtrlPointIndex);
				vertex.u = pVertexUV->GetDirectArray().GetAt(nId)[0];
				vertex.v = pVertexUV->GetDirectArray().GetAt(nId)[1];
			}
			break;
			default:
				break;
			}
		}
		break;
		case FbxGeometryElement::eByPolygonVertex:
		{
			switch (pVertexUV->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			case FbxGeometryElement::eIndexToDirect:
			{
				vertex.u = pVertexUV->GetDirectArray().GetAt(nTextureUVIndex)[0];
				vertex.v = pVertexUV->GetDirectArray().GetAt(nTextureUVIndex)[1];
			}
			break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		}
	}

	void HXFBXLoader::ReadNormal(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex)
	{
		if (pFbxMesh->GetElementNormalCount() < 1)
		{
			return;
		}

		FbxGeometryElementNormal* pNormal = pFbxMesh->GetElementNormal(0);
		switch (pNormal->GetMappingMode())
		{
		case FbxGeometryElement::eByControlPoint:
		{
			switch (pNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				vertex.normal.x = pNormal->GetDirectArray().GetAt(nCtrlPointIndex)[0];
				vertex.normal.y = pNormal->GetDirectArray().GetAt(nCtrlPointIndex)[1];
				vertex.normal.z = pNormal->GetDirectArray().GetAt(nCtrlPointIndex)[2];
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int nId = pNormal->GetIndexArray().GetAt(nCtrlPointIndex);
				vertex.normal.x = pNormal->GetDirectArray().GetAt(nId)[0];
				vertex.normal.y = pNormal->GetDirectArray().GetAt(nId)[1];
				vertex.normal.z = pNormal->GetDirectArray().GetAt(nId)[2];
			}
			break;
			default:
				break;
			}
		}
		break;
		case FbxGeometryElement::eByPolygonVertex:
		{
			switch (pNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				vertex.normal.x = pNormal->GetDirectArray().GetAt(nVertexCounter)[0];
				vertex.normal.y = pNormal->GetDirectArray().GetAt(nVertexCounter)[1];
				vertex.normal.z = pNormal->GetDirectArray().GetAt(nVertexCounter)[2];
			}
			break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int nId = pNormal->GetIndexArray().GetAt(nVertexCounter);
				vertex.normal.x = pNormal->GetDirectArray().GetAt(nId)[0];
				vertex.normal.y = pNormal->GetDirectArray().GetAt(nId)[1];
				vertex.normal.z = pNormal->GetDirectArray().GetAt(nId)[2];
			}
			break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		}
	}

	bool HXFBXLoader::LoadMeshFromFile(std::string strFileName, HXMesh* pMesh)
	{
		if (strFileName == "Cube")
		{
			pMesh->CreateCubeForTest();
		}
		else if (strFileName == "Triangle")
		{
			pMesh->CreateTriangleForTest();
		}
		else if (strFileName == "Quad")
		{
			pMesh->CreateQuadForTest();
		}
		else
		{
			// 读取模型文本文档
			if (LoadScene(strFileName) == false)
			{
				return false;
			}
			// Convert mesh, NURBS and patch into triangle mesh
			FbxGeometryConverter lGeomConverter(m_pFbxManager);
			lGeomConverter.Triangulate(m_pScene, /*replace*/true);
			ProcessNode(m_pScene->GetRootNode(), pMesh);
		}
		return true;
	}
}