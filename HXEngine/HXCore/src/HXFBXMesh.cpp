#include "..\include\HXFBXMesh.h"
#include "HXFBXLoader.h"
#include "HXMatrix.h"
#include "HXISkeleton.h"

namespace HX3D
{
	HXFBXMesh::HXFBXMesh()
	{
	}


	HXFBXMesh::~HXFBXMesh()
	{
	}

	bool HXFBXMesh::Initialize(FbxMesh* pFbxMesh)
	{
		/*FbxVector4 fbxScale = pFbxMesh->GetNode()->GetGeometricScaling(FbxNode::eSourcePivot);
		HXVector3D scale = HXVector3D(fbxScale.mData[0], fbxScale.mData[1], fbxScale.mData[2]);*/

		//FbxSystemUnit sceneSystemUnit = m_pScene->GetGlobalSettings().GetSystemUnit();
		/*if (sceneSystemUnit.GetScaleFactor() != 1.0)
		{
		FbxSystemUnit::cm.ConvertScene(m_pScene);
		}*/
		//double scale = sceneSystemUnit.GetScaleFactor();


		matrixMeshGlobalPositionIn3DMax = pFbxMesh->GetNode()->EvaluateGlobalTransform();
		// 缩放已经包含在matrixMeshGlobalPositionIn3DMax矩阵里了
		//FbxVector4 LclScaling = pFbxMesh->GetNode()->LclScaling;

		int nTriangleCount = pFbxMesh->GetPolygonCount();
		int nVertexCounter = 0;

		FbxLayerElementArrayTemplate<int>* lMaterialIndice = NULL;
		FbxGeometryElement::EMappingMode lMaterialMappingMode = FbxGeometryElement::eNone;
		if (pFbxMesh->GetElementMaterial() != NULL)
		{
			lMaterialIndice = &pFbxMesh->GetElementMaterial()->GetIndexArray();
			lMaterialMappingMode = pFbxMesh->GetElementMaterial()->GetMappingMode();
		}
		
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
					}
					subMeshList[lMaterialIndex]->triangleCount += 1;
					// 关联材质
					/*FbxSurfaceMaterial* lMaterial = pFbxMesh->GetNode()->GetMaterial(lMaterialIndex);
					std::string strMaterialName = HXFBXLoader::gCurPathFileName + "|" + lMaterial->GetName();
					subMeshList[lMaterialIndex]->materialName = strMaterialName;*/
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
			// 只有一个子网格或者无材质信息
			subMeshList.resize(1);
			subMeshList[0] = new HXSubMesh();
			subMeshList[0]->triangleCount = nTriangleCount;
			// 关联材质
			FbxSurfaceMaterial* lMaterial = pFbxMesh->GetNode()->GetMaterial(0);
			if (lMaterial)
			{
				subMeshList[0]->materialName = HXFBXLoader::gCurPathFileName + "|" + lMaterial->GetName();
			}
			
			for (int i = 0; i < nTriangleCount; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					HXVertex vertex;

					// 控点和UV不同的顶点可能共享，和顶点不是一一对应关系
					int nCtrlPointIndex = pFbxMesh->GetPolygonVertex(i, j);
					int nTextureUVIndex = pFbxMesh->GetTextureUVIndex(i, j);
					// 读取比例因子矩阵乘以顶点坐标（3DMAX系统单位设置不同，顶点坐标会不同，需要乘以比例因子LclScaling）
					// 顶点坐标会转化为系统设置单位，乘以比例因子后是导出时选择的单位
					// 3DMAX中调整单位及轴等，导出时需要重置变换
					// 以上所有都包含在matrixMeshGlobalPositionIn3DMax矩阵中了
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
		triangleCount = nTriangleCount;
		vertexCount = nVertexCounter;
		return true;
	}

	void HXFBXMesh::UpdateVertexPosition(const FbxVector4* pVertices)
	{
		for (std::vector<HXSubMesh*>::iterator itr = subMeshList.begin(); itr != subMeshList.end(); ++itr)
		{
			for (std::vector<HXVertex>::iterator itr1 = (*itr)->vertexList.begin(); itr1 != (*itr)->vertexList.end(); ++itr1)
			{
				FbxVector4 curPoint = pVertices[(*itr1).ctrlPointIndex];
				curPoint = matrixMeshGlobalPositionIn3DMax.MultT(curPoint);

				/*(*itr1).pos.x = pVertices[(*itr1).ctrlPointIndex][0];
				(*itr1).pos.y = pVertices[(*itr1).ctrlPointIndex][1];
				(*itr1).pos.z = pVertices[(*itr1).ctrlPointIndex][2];*/
				(*itr1).pos.x = curPoint[0];
				(*itr1).pos.y = curPoint[1];
				(*itr1).pos.z = curPoint[2];
			}
		}
	}

	HXMesh* HXFBXMesh::Clone(HXRenderSystem* pRenderSystem)
	{
		HXFBXMesh* pMesh = new HXFBXMesh();
		for (std::vector<HXSubMesh*>::iterator itr = subMeshList.begin(); itr != subMeshList.end(); ++itr)
		{
			HXSubMesh* pHXSubMesh = (*itr)->Clone(pRenderSystem);
			pMesh->subMeshList.push_back(pHXSubMesh);
		}
		pMesh->triangleCount = triangleCount;
		pMesh->vertexCount = vertexCount;

		// 骨骼用同一套，具体参数(如当前动画片段，时间等)自己控制
		if (NULL != skeleton)
		{
			pMesh->skeleton = skeleton;
			HXAnimationInstance* pAnimInst = new HXAnimationInstance();
			pMesh->animInst = pAnimInst;
			pMesh->animInst->mMesh = pMesh;
		}

		pMesh->matrixMeshGlobalPositionIn3DMax = matrixMeshGlobalPositionIn3DMax;

		return pMesh;
	}

	void HXFBXMesh::ReadVertex(FbxMesh* pFbxMesh, int nCtrlPointIndex, HXVertex& vertex)
	{
		FbxVector4* pCtrlPoint = pFbxMesh->GetControlPoints();

		FbxVector4 curPoint = pCtrlPoint[nCtrlPointIndex];
		curPoint = matrixMeshGlobalPositionIn3DMax.MultT(curPoint);

		/*vertex.pos.x = pCtrlPoint[nCtrlPointIndex][0];
		vertex.pos.y = pCtrlPoint[nCtrlPointIndex][1];
		vertex.pos.z = pCtrlPoint[nCtrlPointIndex][2];*/
		vertex.pos.x = curPoint[0];
		vertex.pos.y = curPoint[1];
		vertex.pos.z = curPoint[2];
		vertex.ctrlPointIndex = nCtrlPointIndex;
	}

	void HXFBXMesh::ReadColor(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex)
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

	void HXFBXMesh::ReadUV(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nTextureUVIndex, HXVertex& vertex)
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

	void HXFBXMesh::ReadNormal(FbxMesh* pFbxMesh, int nCtrlPointIndex, int nVertexCounter, HXVertex& vertex)
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