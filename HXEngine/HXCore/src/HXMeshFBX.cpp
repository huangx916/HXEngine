#include "..\include\HXMeshFBX.h"
#include "HXFBXLoader.h"

namespace HX3D
{
	HXMeshFBX::HXMeshFBX()
	{
	}


	HXMeshFBX::~HXMeshFBX()
	{
	}

	bool HXMeshFBX::Initialize(FbxMesh* pFbxMesh)
	{
		/*FbxVector4 fbxScale = pFbxMesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
		HXVector3D scale = HXVector3D(fbxScale.mData[0], fbxScale.mData[1], fbxScale.mData[2]);*/

		//FbxSystemUnit sceneSystemUnit = m_pScene->GetGlobalSettings().GetSystemUnit();
		/*if (sceneSystemUnit.GetScaleFactor() != 1.0)
		{
		FbxSystemUnit::cm.ConvertScene(m_pScene);
		}*/
		//double scale = sceneSystemUnit.GetScaleFactor();

		FbxVector4 LclScaling = pFbxMesh->GetNode()->LclScaling;

		int nTriangleCount = pFbxMesh->GetPolygonCount();
		int nVertexCounter = 0;


		FbxLayerElementArrayTemplate<int>* lMaterialIndice = &pFbxMesh->GetElementMaterial()->GetIndexArray();
		FbxGeometryElement::EMappingMode lMaterialMappingMode = pFbxMesh->GetElementMaterial()->GetMappingMode();
		if (lMaterialIndice && lMaterialMappingMode == FbxGeometryElement::eByPolygon)
		{
			// 多个子网格
			FBX_ASSERT(lMaterialIndice->GetCount() == nTriangleCount);
			if (lMaterialIndice->GetCount() == nTriangleCount)
			{
				for (int i = 0; i < nTriangleCount; ++i)
				{
					const int lMaterialIndex = lMaterialIndice->GetAt(i);
					if (subMeshList.size() < lMaterialIndex + 1)
					{
						subMeshList.resize(lMaterialIndex + 1);
					}
					if (subMeshList[lMaterialIndex] == NULL)
					{
						subMeshList[lMaterialIndex] = new HXSubMesh();
						subMeshList[lMaterialIndex]->triangleCount += 1;
					}
					// 关联材质
					FbxSurfaceMaterial* lMaterial = pFbxMesh->GetNode()->GetMaterial(lMaterialIndex);
					std::string strMaterialName = HXFBXLoader::gCurPathFileName + "|" + lMaterial->GetName();
					subMeshList[lMaterialIndex]->materialName = strMaterialName;
					// 读取顶点坐标、颜色、UV、法线等
					for (int j = 0; j < 3; j++)
					{
						HXVertex vertex;

						// 控点和UV不同的顶点可能共享，和顶点不是一一对应关系
						int nCtrlPointIndex = pFbxMesh->GetPolygonVertex(i, j);
						int nTextureUVIndex = pFbxMesh->GetTextureUVIndex(i, j);
						// TODO: 读取比例因子矩阵乘以顶点坐标（3DMAX系统单位设置不同，顶点坐标会不同，需要乘以比例因子LclScaling）
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

						subMeshList[lMaterialIndex]->vertexList.push_back(vertex);
						nVertexCounter++;
					}
				}
				//// Make sure we have no "holes" (NULL) in the mSubMeshes table. This can happen
				//// if, in the loop above, we resized the mSubMeshes by more than one slot.
				//for (int i = 0; i < subMeshList.size(); i++)
				//{
				//	if (subMeshList[i] == NULL)
				//		subMeshList[i] = new HXSubMesh();
				//}
			}
		}
		else
		{
			// 只有一个子网格
			subMeshList.resize(1);
			subMeshList[0] = new HXSubMesh();
			subMeshList[0]->triangleCount = nTriangleCount;
			// 关联材质
			FbxSurfaceMaterial* lMaterial = pFbxMesh->GetNode()->GetMaterial(0);
			std::string strMaterialName = HXFBXLoader::gCurPathFileName + "|" + lMaterial->GetName();
			subMeshList[0]->materialName = strMaterialName;
			for (int i = 0; i < nTriangleCount; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					HXVertex vertex;

					// 控点和UV不同的顶点可能共享，和顶点不是一一对应关系
					int nCtrlPointIndex = pFbxMesh->GetPolygonVertex(i, j);
					int nTextureUVIndex = pFbxMesh->GetTextureUVIndex(i, j);
					// TODO: 读取比例因子矩阵乘以顶点坐标（3DMAX系统单位设置不同，顶点坐标会不同，需要乘以比例因子LclScaling）
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

					subMeshList[0]->vertexList.push_back(vertex);
					nVertexCounter++;
				}
			}
		}

		return true;
	}

	void HXMeshFBX::ReadVertex(FbxMesh* pFbxMesh, int nCtrlPointIndex, HXVertex& vertex)
	{
		FbxVector4* pCtrlPoint = pFbxMesh->GetControlPoints();
		vertex.pos.x = pCtrlPoint[nCtrlPointIndex][0];
		vertex.pos.y = pCtrlPoint[nCtrlPointIndex][1];
		vertex.pos.z = pCtrlPoint[nCtrlPointIndex][2];
	}

	void HXMeshFBX::ReadColor(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex)
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

	void HXMeshFBX::ReadUV(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nTextureUVIndex, HXVertex& vertex)
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

	void HXMeshFBX::ReadNormal(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex)
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
}