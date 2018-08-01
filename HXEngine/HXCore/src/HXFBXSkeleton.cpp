#include "..\include\HXFBXSkeleton.h"
#include <Windows.h>
#include "HXFBXMesh.h"
#include "HXMesh.h"

namespace HX3D
{
	HXFBXSkeleton::HXFBXSkeleton()
	{
		// nSpeed = 1;
		// bAnimationLoaded = false;
		mSkinSkeleton = new HXSkinSkeleton;
		srcControlPoints = NULL;
	}

	HXFBXSkeleton::~HXFBXSkeleton()
	{
		if (mSkinSkeleton)
		{
			delete mSkinSkeleton;
		}
		if (srcControlPoints)
		{
			delete[] srcControlPoints;
		}

		// TODO: delete
	}

	// Scale all the elements of a matrix.
	void HXFBXSkeleton::MatrixScale(FbxAMatrix& pMatrix, double pValue)
	{
		int i, j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				pMatrix[i][j] *= pValue;
			}
		}
	}

	// Add a value to all the elements in the diagonal of the matrix.
	void HXFBXSkeleton::MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue)
	{
		pMatrix[0][0] += pValue;
		pMatrix[1][1] += pValue;
		pMatrix[2][2] += pValue;
		pMatrix[3][3] += pValue;
	}

	// Sum two matrices element by element.
	void HXFBXSkeleton::MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix)
	{
		int i, j;

		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				pDstMatrix[i][j] += pSrcMatrix[i][j];
			}
		}
	}

	// Get the matrix of the given pose
	FbxAMatrix HXFBXSkeleton::GetPoseMatrix(FbxPose* pPose, int pNodeIndex)
	{
		FbxAMatrix lPoseMatrix;
		FbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

		memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

		return lPoseMatrix;
	}

	// Get the global position of the node for the current pose.
	// If the specified node is not part of the pose or no pose is specified, get its
	// global position at the current time.
	FbxAMatrix HXFBXSkeleton::GetGlobalPosition(FbxNode* pNode, const FbxTime& pTime, FbxPose* pPose, FbxAMatrix* pParentGlobalPosition)
	{
		FbxAMatrix lGlobalPosition;
		bool        lPositionFound = false;

		if (pPose)
		{
			int lNodeIndex = pPose->Find(pNode);

			if (lNodeIndex > -1)
			{
				// The bind pose is always a global matrix.
				// If we have a rest pose, we need to check if it is
				// stored in global or local space.
				if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
				{
					lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
				}
				else
				{
					// We have a local matrix, we need to convert it to
					// a global space matrix.
					FbxAMatrix lParentGlobalPosition;

					if (pParentGlobalPosition)
					{
						lParentGlobalPosition = *pParentGlobalPosition;
					}
					else
					{
						if (pNode->GetParent())
						{
							lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
						}
					}

					FbxAMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
					lGlobalPosition = lParentGlobalPosition * lLocalPosition;
				}

				lPositionFound = true;
			}
		}

		if (!lPositionFound)
		{
			// There is no pose entry for that node, get the current global position instead.

			// Ideally this would use parent global position and local position to compute the global position.
			// Unfortunately the equation 
			//    lGlobalPosition = pParentGlobalPosition * lLocalPosition
			// does not hold when inheritance type is other than "Parent" (RSrs).
			// To compute the parent rotation and scaling is tricky in the RrSs and Rrs cases.
			lGlobalPosition = pNode->EvaluateGlobalTransform(pTime);
		}

		return lGlobalPosition;
	}

	// Get the geometry offset to a node. It is never inherited by the children.
	FbxAMatrix HXFBXSkeleton::GetGeometry(FbxNode* pNode)
	{
		const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
		const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
		const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);

		return FbxAMatrix(lT, lR, lS);
	}

	//Compute the transform matrix that the cluster will transform the vertex.
	void HXFBXSkeleton::ComputeClusterDeformation(FbxAMatrix& pGlobalPosition,
		FbxMesh* pMesh,
		FbxCluster* pCluster,
		FbxAMatrix& pVertexTransformMatrix,
		FbxTime pTime,
		FbxPose* pPose)
	{
		FbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

		FbxAMatrix lReferenceGlobalInitPosition;
		FbxAMatrix lReferenceGlobalCurrentPosition;
		FbxAMatrix lAssociateGlobalInitPosition;
		FbxAMatrix lAssociateGlobalCurrentPosition;
		FbxAMatrix lClusterGlobalInitPosition;
		FbxAMatrix lClusterGlobalCurrentPosition;

		FbxAMatrix lReferenceGeometry;
		FbxAMatrix lAssociateGeometry;
		FbxAMatrix lClusterGeometry;

		FbxAMatrix lClusterRelativeInitPosition;
		FbxAMatrix lClusterRelativeCurrentPositionInverse;

		if (lClusterMode == FbxCluster::eAdditive && pCluster->GetAssociateModel())
		{
			pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
			// Geometric transform of the model
			lAssociateGeometry = GetGeometry(pCluster->GetAssociateModel());
			lAssociateGlobalInitPosition *= lAssociateGeometry;
			lAssociateGlobalCurrentPosition = GetGlobalPosition(pCluster->GetAssociateModel(), pTime, pPose);

			pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
			// Multiply lReferenceGlobalInitPosition by Geometric Transformation
			lReferenceGeometry = GetGeometry(pMesh->GetNode());
			lReferenceGlobalInitPosition *= lReferenceGeometry;
			lReferenceGlobalCurrentPosition = pGlobalPosition;

			// Get the link initial global position and the link current global position.
			pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
			// Multiply lClusterGlobalInitPosition by Geometric Transformation
			lClusterGeometry = GetGeometry(pCluster->GetLink());
			lClusterGlobalInitPosition *= lClusterGeometry;
			lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);

			// Compute the shift of the link relative to the reference.
			//ModelM-1 * AssoM * AssoGX-1 * LinkGX * LinkM-1*ModelM
			pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition * lAssociateGlobalCurrentPosition.Inverse() *
				lClusterGlobalCurrentPosition * lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
		}
		else
		{
			pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
			lReferenceGlobalCurrentPosition = pGlobalPosition;
			// Multiply lReferenceGlobalInitPosition by Geometric Transformation
			lReferenceGeometry = GetGeometry(pMesh->GetNode());
			lReferenceGlobalInitPosition *= lReferenceGeometry;

			// Get the link initial global position and the link current global position.
			pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
			lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);

			// Compute the initial position of the link relative to the reference.
			lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;

			// Compute the current position of the link relative to the reference.
			lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;

			// Compute the shift of the link relative to the reference.
			pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
		}
	}

	// Deform the vertex array in classic linear way.
	void HXFBXSkeleton::ComputeLinearDeformation(FbxAMatrix& pGlobalPosition,
		FbxMesh* pMesh,
		FbxTime& pTime,
		FbxVector4* pVertexArray,
		FbxPose* pPose)
	{
		//// All the links must have the same link mode.
		//FbxCluster::ELinkMode lClusterMode = ((FbxSkin*)pMesh->GetDeformer(0, FbxDeformer::eSkin))->GetCluster(0)->GetLinkMode();

		//int lVertexCount = pMesh->GetControlPointsCount();
		//FbxAMatrix* lClusterDeformation = new FbxAMatrix[lVertexCount];
		//memset(lClusterDeformation, 0, lVertexCount * sizeof(FbxAMatrix));

		//double* lClusterWeight = new double[lVertexCount];
		//memset(lClusterWeight, 0, lVertexCount * sizeof(double));

		//if (lClusterMode == FbxCluster::eAdditive)
		//{
		//	for (int i = 0; i < lVertexCount; ++i)
		//	{
		//		lClusterDeformation[i].SetIdentity();
		//	}
		//}

		// For all skins and all clusters, accumulate their deformation and weight
		// on each vertices and store them in lClusterDeformation and lClusterWeight.
		int lSkinCount = pMesh->GetDeformerCount(FbxDeformer::eSkin);
		for (int lSkinIndex = 0; lSkinIndex < lSkinCount; ++lSkinIndex)
		{
			FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin);

			int lClusterCount = lSkinDeformer->GetClusterCount();
			for (int lClusterIndex = 0; lClusterIndex < lClusterCount; ++lClusterIndex)
			{
				/*if (lClusterIndex + 1 > mSkinSkeleton->xSkeleton.nJointCount)
				{
					HXJoint* pJoint = new HXJoint();
					mSkinSkeleton->xSkeleton.vctJoint.push_back(pJoint);
					mSkinSkeleton->xSkeleton.nJointCount++;
				}*/

				FbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
				if (!lCluster->GetLink())
					continue;

				FbxAMatrix lVertexTransformMatrix;
				ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);

				HXJointPose* pJointPose = new HXJointPose;
				pJointPose->mtVertexTransformMatrix = lVertexTransformMatrix;
				
				
				if (mCurLoadAnimIndex + 1 > mSkinSkeleton->xSkeleton.vctJoint[lClusterIndex]->vctJointAnim.size())
				{
					HXJointAnim* pJointAnim = new HXJointAnim;
					mSkinSkeleton->xSkeleton.vctJoint[lClusterIndex]->vctJointAnim.push_back(pJointAnim);
					
				}
				HXJointAnim* pJointAnim = mSkinSkeleton->xSkeleton.vctJoint[lClusterIndex]->vctJointAnim[mCurLoadAnimIndex];
				pJointAnim->strAnimName = mCurLoadAnimName;
				pJointAnim->nKeyNums++;
				pJointAnim->vctJointPose.push_back(pJointPose);

				//int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
				//for (int k = 0; k < lVertexIndexCount; ++k)
				//{
				//	int lIndex = lCluster->GetControlPointIndices()[k];

				//	// Sometimes, the mesh can have less points than at the time of the skinning
				//	// because a smooth operator was active when skinning but has been deactivated during export.
				//	if (lIndex >= lVertexCount)
				//		continue;

				//	double lWeight = lCluster->GetControlPointWeights()[k];

				//	if (lWeight == 0.0)
				//	{
				//		continue;
				//	}

				//	// Compute the influence of the link on the vertex.
				//	FbxAMatrix lInfluence = lVertexTransformMatrix;
				//	MatrixScale(lInfluence, lWeight);

				//	if (lClusterMode == FbxCluster::eAdditive)
				//	{
				//		// Multiply with the product of the deformations on the vertex.
				//		MatrixAddToDiagonal(lInfluence, 1.0 - lWeight);
				//		lClusterDeformation[lIndex] = lInfluence * lClusterDeformation[lIndex];

				//		// Set the link to 1.0 just to know this vertex is influenced by a link.
				//		lClusterWeight[lIndex] = 1.0;
				//	}
				//	else // lLinkMode == FbxCluster::eNormalize || lLinkMode == FbxCluster::eTotalOne
				//	{
				//		// Add to the sum of the deformations on the vertex.
				//		MatrixAdd(lClusterDeformation[lIndex], lInfluence);

				//		// Add to the sum of weights to either normalize or complete the vertex.
				//		lClusterWeight[lIndex] += lWeight;
				//	}
				//	// 只在第一帧读取，不要每帧重复读取
				//	if (mSkinSkeleton->nKeyNums == 1)
				//	{
				//		HXVertJointWeights xVertJointWeight;
				//		xVertJointWeight.nAttachJointIndex = lClusterIndex;
				//		xVertJointWeight.fWeightBias = (float)lWeight;
				//		std::map<int, std::vector<HXVertJointWeights>>::iterator pFind = mSkinSkeleton->mapVertJointInfo.find(lIndex);
				//		if (pFind != mSkinSkeleton->mapVertJointInfo.end())
				//		{
				//			pFind->second.push_back(xVertJointWeight);
				//		}
				//		else
				//		{
				//			mSkinSkeleton->mapVertJointInfo.insert(std::make_pair(lIndex, std::vector<HXVertJointWeights>())).first->second.push_back(xVertJointWeight);
				//		}
				//	}
				//}//For each vertex			
			}//lClusterCount
		}

		//Actually deform each vertices here by information stored in lClusterDeformation and lClusterWeight
		//for (int i = 0; i < lVertexCount; i++)
		//{
		//	FbxVector4 lSrcVertex = pVertexArray[i];
		//	FbxVector4& lDstVertex = pVertexArray[i];
		//	double lWeight = lClusterWeight[i];

		//	// Deform the vertex if there was at least a link with an influence on the vertex,
		//	if (lWeight != 0.0)
		//	{
		//		lDstVertex = lClusterDeformation[i].MultT(lSrcVertex);
		//		if (lClusterMode == FbxCluster::eNormalize)
		//		{
		//			// In the normalized link mode, a vertex is always totally influenced by the links. 
		//			lDstVertex /= lWeight;
		//		}
		//		else if (lClusterMode == FbxCluster::eTotalOne)
		//		{
		//			// In the total 1 link mode, a vertex can be partially influenced by the links. 
		//			lSrcVertex *= (1.0 - lWeight);
		//			lDstVertex += lSrcVertex;
		//		}
		//	}
		//}

		/*delete[] lClusterDeformation;
		delete[] lClusterWeight;*/
	}

	// Deform the vertex array according to the links contained in the mesh and the skinning type.
	void HXFBXSkeleton::ComputeSkinDeformation(FbxAMatrix& pGlobalPosition,
		FbxMesh* pMesh,
		FbxTime& pTime,
		FbxVector4* pVertexArray,
		FbxPose* pPose)
	{
		FbxSkin * lSkinDeformer = (FbxSkin *)pMesh->GetDeformer(0, FbxDeformer::eSkin);
		FbxSkin::EType lSkinningType = lSkinDeformer->GetSkinningType();

		if (lSkinningType == FbxSkin::eLinear || lSkinningType == FbxSkin::eRigid)
		{
			ComputeLinearDeformation(pGlobalPosition, pMesh, pTime, pVertexArray, pPose);
		}
		//else if (lSkinningType == FbxSkin::eDualQuaternion)
		//{
		//	ComputeDualQuaternionDeformation(pGlobalPosition, pMesh, pTime, pVertexArray, pPose);
		//}
		//else if (lSkinningType == FbxSkin::eBlend)
		//{
		//	int lVertexCount = pMesh->GetControlPointsCount();

		//	FbxVector4* lVertexArrayLinear = new FbxVector4[lVertexCount];
		//	memcpy(lVertexArrayLinear, pMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));

		//	FbxVector4* lVertexArrayDQ = new FbxVector4[lVertexCount];
		//	memcpy(lVertexArrayDQ, pMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));

		//	ComputeLinearDeformation(pGlobalPosition, pMesh, pTime, lVertexArrayLinear, pPose);
		//	ComputeDualQuaternionDeformation(pGlobalPosition, pMesh, pTime, lVertexArrayDQ, pPose);

		//	// To blend the skinning according to the blend weights
		//	// Final vertex = DQSVertex * blend weight + LinearVertex * (1- blend weight)
		//	// DQSVertex: vertex that is deformed by dual quaternion skinning method;
		//	// LinearVertex: vertex that is deformed by classic linear skinning method;
		//	int lBlendWeightsCount = lSkinDeformer->GetControlPointIndicesCount();
		//	for (int lBWIndex = 0; lBWIndex < lBlendWeightsCount; ++lBWIndex)
		//	{
		//		double lBlendWeight = lSkinDeformer->GetControlPointBlendWeights()[lBWIndex];
		//		pVertexArray[lBWIndex] = lVertexArrayDQ[lBWIndex] * lBlendWeight + lVertexArrayLinear[lBWIndex] * (1 - lBlendWeight);
		//	}
		//}
	}

	// Draw the vertices of a mesh.
	void HXFBXSkeleton::DrawMesh(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pGlobalPosition, FbxPose* pPose)
	{
		FbxMesh* lMesh = pNode->GetMesh();
		const int lVertexCount = lMesh->GetControlPointsCount();

		// No vertex to draw.
		if (lVertexCount == 0)
		{
			return;
		}

		//const VBOMesh * lMeshCache = static_cast<const VBOMesh *>(lMesh->GetUserDataPtr());

		// If it has some defomer connection, update the vertices position
		const bool lHasVertexCache = lMesh->GetDeformerCount(FbxDeformer::eVertexCache) &&
			(static_cast<FbxVertexCacheDeformer*>(lMesh->GetDeformer(0, FbxDeformer::eVertexCache)))->Active.Get();
		const bool lHasShape = lMesh->GetShapeCount() > 0;
		const bool lHasSkin = lMesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
		const bool lHasDeformation = lHasVertexCache || lHasShape || lHasSkin;

		FbxVector4* lVertexArray = NULL;
		//if (!lMeshCache || lHasDeformation)
		//{
		lVertexArray = new FbxVector4[lVertexCount];
		memcpy(lVertexArray, lMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));
		//}

		srcControlPoints = new FbxVector4[lVertexCount];
		memcpy(srcControlPoints, lMesh->GetControlPoints(), lVertexCount * sizeof(FbxVector4));
		nControlPointCount = lVertexCount;

		if (lHasDeformation)
		{
			// Active vertex cache deformer will overwrite any other deformer
			if (lHasVertexCache)
			{
				//ReadVertexCacheData(lMesh, pTime, lVertexArray);
			}
			else
			{
				if (lHasShape)
				{
					// Deform the vertex array with the shapes.
					//ComputeShapeDeformation(lMesh, pTime, pAnimLayer, lVertexArray);
				}

				//we need to get the number of clusters
				const int lSkinCount = lMesh->GetDeformerCount(FbxDeformer::eSkin);
				int lClusterCount = 0;
				for (int lSkinIndex = 0; lSkinIndex < lSkinCount; ++lSkinIndex)
				{
					lClusterCount += ((FbxSkin *)(lMesh->GetDeformer(lSkinIndex, FbxDeformer::eSkin)))->GetClusterCount();
				}
				if (lClusterCount)
				{
					// Deform the vertex array with the skin deformer.
					ComputeSkinDeformation(pGlobalPosition, lMesh, pTime, lVertexArray, pPose);
				}
			}

			//if (lMeshCache)
			//	lMeshCache->UpdateVertexPosition(lMesh, lVertexArray);
			/*if (mMesh)
			{
				mMesh->UpdateVertexPosition(lVertexArray);
			}*/
		}

		//glPushMatrix();
		//glMultMatrixd((const double*)pGlobalPosition);

		//if (lMeshCache)
		//{
		//	lMeshCache->BeginDraw(pShadingMode);
		//	const int lSubMeshCount = lMeshCache->GetSubMeshCount();
		//	for (int lIndex = 0; lIndex < lSubMeshCount; ++lIndex)
		//	{
		//		if (pShadingMode == SHADING_MODE_SHADED)
		//		{
		//			const FbxSurfaceMaterial * lMaterial = pNode->GetMaterial(lIndex);
		//			if (lMaterial)
		//			{
		//				const MaterialCache * lMaterialCache = static_cast<const MaterialCache *>(lMaterial->GetUserDataPtr());
		//				if (lMaterialCache)
		//				{
		//					lMaterialCache->SetCurrentMaterial();
		//				}
		//			}
		//			else
		//			{
		//				// Draw green for faces without material
		//				MaterialCache::SetDefaultMaterial();
		//			}
		//		}

		//		lMeshCache->Draw(lIndex, pShadingMode);
		//	}
		//	lMeshCache->EndDraw();
		//}
		//else
		//{
		//	// OpenGL driver is too lower and use Immediate Mode
		//	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
		//	const int lPolygonCount = lMesh->GetPolygonCount();
		//	for (int lPolygonIndex = 0; lPolygonIndex < lPolygonCount; lPolygonIndex++)
		//	{
		//		const int lVerticeCount = lMesh->GetPolygonSize(lPolygonIndex);
		//		glBegin(GL_LINE_LOOP);
		//		for (int lVerticeIndex = 0; lVerticeIndex < lVerticeCount; lVerticeIndex++)
		//		{
		//			glVertex3dv((GLdouble *)lVertexArray[lMesh->GetPolygonVertex(lPolygonIndex, lVerticeIndex)]);
		//		}
		//		glEnd();
		//	}
		//}

		//glPopMatrix();

		delete[] lVertexArray;
	}

	// Draw the node following the content of it's node attribute.
	void HXFBXSkeleton::DrawNode(FbxNode* pNode,
		FbxTime& pTime,
		FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pParentGlobalPosition,
		FbxAMatrix& pGlobalPosition,
		FbxPose* pPose)
	{
		FbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

		if (lNodeAttribute)
		{
			// All lights has been processed before the whole scene because they influence every geometry.
			
			/*if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			{
				DrawSkeleton(pNode, pParentGlobalPosition, pGlobalPosition);
			}*/
			// NURBS and patch have been converted into triangluation meshes.
			if (lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				DrawMesh(pNode, pTime, pAnimLayer, pGlobalPosition, pPose);
			}
			
		}
		
	}

	// Draw recursively each node of the scene. To avoid recomputing 
	// uselessly the global positions, the global position of each 
	// node is passed to it's children while browsing the node tree.
	// If the node is part of the given pose for the current scene,
	// it will be drawn at the position specified in the pose, Otherwise
	// it will be drawn at the given time.
	void HXFBXSkeleton::DrawNodeRecursive(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
		FbxAMatrix& pParentGlobalPosition, FbxPose* pPose)
	{
		FbxAMatrix lGlobalPosition = GetGlobalPosition(pNode, pTime, pPose, &pParentGlobalPosition);

		if (pNode->GetNodeAttribute())
		{
			// Geometry offset.
			// it is not inherited by the children.
			FbxAMatrix lGeometryOffset = GetGeometry(pNode);
			FbxAMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

			DrawNode(pNode, pTime, pAnimLayer, pParentGlobalPosition, lGlobalOffPosition, pPose);
		}

		const int lChildCount = pNode->GetChildCount();
		for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
		{
			DrawNodeRecursive(pNode->GetChild(lChildIndex), pTime, pAnimLayer, lGlobalPosition, pPose);
		}
	}

	bool HXFBXSkeleton::SetCurrentAnimStack(int pIndex)
	{
		// Get the list of all the animation stack.
		mScene->FillAnimStackNameArray(mAnimStackNameArray);

		const int lAnimStackCount = mAnimStackNameArray.GetCount();
		if (!lAnimStackCount || pIndex >= lAnimStackCount)
		{
			return false;
		}

		// select the base layer from the animation stack
		FbxAnimStack * lCurrentAnimationStack = mScene->FindMember<FbxAnimStack>(mAnimStackNameArray[pIndex]->Buffer());
		if (lCurrentAnimationStack == NULL)
		{
			// this is a problem. The anim stack should be found in the scene!
			return false;
		}

		// we assume that the first animation layer connected to the animation stack is the base layer
		// (this is the assumption made in the FBXSDK)
		mCurrentAnimLayer = lCurrentAnimationStack->GetMember<FbxAnimLayer>();
		mScene->SetCurrentAnimationStack(lCurrentAnimationStack);

		FbxTakeInfo* lCurrentTakeInfo = mScene->GetTakeInfo(*(mAnimStackNameArray[pIndex]));
		if (lCurrentTakeInfo)
		{
			mStart = lCurrentTakeInfo->mLocalTimeSpan.GetStart();
			mStop = lCurrentTakeInfo->mLocalTimeSpan.GetStop();
		}
		else
		{
			// Take the time line value
			FbxTimeSpan lTimeLineTimeSpan;
			mScene->GetGlobalSettings().GetTimelineDefaultTimeSpan(lTimeLineTimeSpan);

			mStart = lTimeLineTimeSpan.GetStart();
			mStop = lTimeLineTimeSpan.GetStop();
		}

		// check for smallest start with cache start
		if (mCache_Start < mStart)
			mStart = mCache_Start;

		// check for biggest stop with cache stop
		if (mCache_Stop > mStop)
			mStop = mCache_Stop;

		// move to beginning
		mCurrentTime = mStart;

		return true;
	}

	//void HXFBXSkeleton::Update()
	//{
	//	double curTime = ::GetTickCount();
	//	//mFrameTime.SetMilliSeconds(curTime - mLastTime);
	//	mFrameTime.SetTime(0, 0, 0, 1, 0, mScene->GetGlobalSettings().GetTimeMode());
	//	mLastTime = curTime;
	//	mCurrentTime += mFrameTime;
	//	if (mCurrentTime > mStop)
	//	{
	//		mCurrentTime = mStart;
	//	}

	//	// If one node is selected, draw it and its children.
	//	FbxAMatrix lDummyGlobalPosition;
	//	DrawNodeRecursive(mScene->GetRootNode(), mCurrentTime, mCurrentAnimLayer, lDummyGlobalPosition, NULL);
	//}

	//HXISkeleton* HXFBXSkeleton::Clone(HXMesh* pMesh)
	//{
	//	HXFBXSkeleton* pSkeletonFBX = new HXFBXSkeleton();
	//	
	//	pSkeletonFBX->Initial(NULL, mScene);

	//	// 具体mesh实例
	//	pSkeletonFBX->mMesh = (HXFBXMesh*)pMesh;

	//	/*pSkeletonFBX->mAnimStackNameArray = mAnimStackNameArray;
	//	pSkeletonFBX->mCurrentAnimLayer = mCurrentAnimLayer;
	//	pSkeletonFBX->mFrameTime = mFrameTime;
	//	pSkeletonFBX->mStart = mStart;
	//	pSkeletonFBX->mStop = mStop;
	//	pSkeletonFBX->mCurrentTime = mCurrentTime;
	//	pSkeletonFBX->mCache_Start = mCache_Start;
	//	pSkeletonFBX->mCache_Stop = mCache_Stop;
	//	pSkeletonFBX->mScene = mScene;
	//	pSkeletonFBX->mLastTime = mLastTime;*/

	//	return pSkeletonFBX;
	//}

	void HXFBXSkeleton::Initial(FbxScene* pScene)
	{
		
		// mMesh = pMesh;  Clone时赋值具体实例Mesh
		// mMesh = NULL;
		//mScene = pScene;
		
		LoadSkeleton(pScene);
		//LoadAnimationCurve();
	}

	void HXFBXSkeleton::UpdateAnimation(HXAnimationInstance* pAnimInst)
	{
		/*if (!bAnimationLoaded)
		{
			return;
		}*/

		// 首先判断是否有该动作
		if (!mSkinSkeleton->xSkeleton.vctJoint[0])
		{
			return;
		}

		if (pAnimInst->nCurPlayAnimIndex + 1 > mSkinSkeleton->xSkeleton.vctJoint[0]->vctJointAnim.size())
		{
			return;
		}


		pAnimInst->nCurKeyframe += pAnimInst->nSpeed;
		if (pAnimInst->nCurKeyframe > mSkinSkeleton->xSkeleton.vctJoint[0]->vctJointAnim[pAnimInst->nCurPlayAnimIndex]->nKeyNums - 1)
		{
			pAnimInst->nCurKeyframe = 0;
		}

		int lVertexCount = nControlPointCount;
		FbxAMatrix* lClusterDeformation = new FbxAMatrix[lVertexCount];
		memset(lClusterDeformation, 0, lVertexCount * sizeof(FbxAMatrix));

		double* lClusterWeight = new double[lVertexCount];
		memset(lClusterWeight, 0, lVertexCount * sizeof(double));

		FbxVector4* destVertexArray = new FbxVector4[lVertexCount];
		//memset(destVertexArray, 0, lVertexCount * sizeof(FbxVector4));

		//HXJoint* pJoint = mSkinSkeleton->xSkeleton.vctJoint[0];
		//HXJointAnim* pJointAnim = pJoint->vctJointAnim[pAnimInst->nCurPlayAnimIndex];
		//HXJointPose* pJointPose = pJointAnim->vctJointPose[pAnimInst->nCurKeyframe];

		for (int i = 0; i < lVertexCount; i++)
		{
			FbxVector4 lSrcVertex = srcControlPoints[i];
			FbxVector4& lDstVertex = destVertexArray[i];

			//std::map<int, std::vector<HXVertJointWeights>>::iterator pFind = mSkinSkeleton->mapVertJointInfo.find(i);
			//if (pFind != mSkinSkeleton->mapVertJointInfo.end())
			//{
			//	for (std::vector<HXVertJointWeights>::iterator itr = pFind->second.begin(); itr != pFind->second.end(); ++itr)
			//	{
			//		HXJoint* pJoint = mSkinSkeleton->xSkeleton.vctJoint[itr->nAttachJointIndex];
			//		HXJointAnim* pJointAnim = pJoint->vctJointAnim[pAnimInst->nCurPlayAnimIndex];
			//		HXJointPose* pJointPose = pJointAnim->vctJointPose[pAnimInst->nCurKeyframe];

			//		// Compute the influence of the link on the vertex.
			//		FbxAMatrix lInfluence = pJointPose->mtVertexTransformMatrix;
			//		MatrixScale(lInfluence, itr->fWeightBias);
			//		MatrixAdd(lClusterDeformation[i], lInfluence);
			//		lClusterWeight[i] += itr->fWeightBias;
			//	}
			//}

			// 使用vector提高性能，使用引用防止值拷贝影响性能
			std::vector<HXVertJointWeights>& vct = mSkinSkeleton->vctVertJointInfo[i];
			for (std::vector<HXVertJointWeights>::iterator itr = vct.begin(); itr != vct.end(); ++itr)
			{
				HXJoint* pJoint = mSkinSkeleton->xSkeleton.vctJoint[itr->nAttachJointIndex];
				HXJointAnim* pJointAnim = pJoint->vctJointAnim[pAnimInst->nCurPlayAnimIndex];
				HXJointPose* pJointPose = pJointAnim->vctJointPose[pAnimInst->nCurKeyframe];

				// Compute the influence of the link on the vertex.
				FbxAMatrix lInfluence = pJointPose->mtVertexTransformMatrix;
				MatrixScale(lInfluence, itr->fWeightBias);
				MatrixAdd(lClusterDeformation[i], lInfluence);
				lClusterWeight[i] += itr->fWeightBias;
			}

			double lWeight = lClusterWeight[i];

			// Deform the vertex if there was at least a link with an influence on the vertex,
			if (lWeight != 0.0)
			{
				lDstVertex = lClusterDeformation[i].MultT(lSrcVertex);
				//if (lClusterMode == FbxCluster::eNormalize)
				//{
					// In the normalized link mode, a vertex is always totally influenced by the links. 
					lDstVertex /= lWeight;
				//}
				//else if (lClusterMode == FbxCluster::eTotalOne)
				//{
				//	// In the total 1 link mode, a vertex can be partially influenced by the links. 
				//	lSrcVertex *= (1.0 - lWeight);
				//	lDstVertex += lSrcVertex;
				//}
			}
		}
		
		if (pAnimInst->mMesh)
		{
			((HXFBXMesh*)(pAnimInst->mMesh))->UpdateVertexPosition(destVertexArray);
		}

		delete[] lClusterDeformation;
		delete[] lClusterWeight;
		delete[] destVertexArray;
	}

	void HXFBXSkeleton::LoadSkeleton(FbxScene* pScene)
	{
		mScene = pScene;

		FbxMesh* pFbxMesh = GetMeshNodeRecursive(mScene->GetRootNode());
		if (NULL == pFbxMesh)
		{
			return;
		}

		// 提前按顶点顺序填充，保证与vctVertJointInfo对应
		const int lVertexCount = pFbxMesh->GetControlPointsCount();
		for (int i = 0; i < lVertexCount; ++i)
		{
			mSkinSkeleton->mapVertJointInfo.insert(std::make_pair(i, std::vector<HXVertJointWeights>()));
		}

		FbxSkin* lSkinDeformer = (FbxSkin*)pFbxMesh->GetDeformer(0, FbxDeformer::eSkin);
		int lClusterCount = lSkinDeformer->GetClusterCount();
		for (int lClusterIndex = 0; lClusterIndex < lClusterCount; ++lClusterIndex)
		{
			if (lClusterIndex + 1 > mSkinSkeleton->xSkeleton.nJointCount)
			{
				HXJoint* pJoint = new HXJoint();
				mSkinSkeleton->xSkeleton.vctJoint.push_back(pJoint);
				mSkinSkeleton->xSkeleton.nJointCount++;
			}

			FbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
			if (!lCluster->GetLink())
				continue;

			int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
			for (int k = 0; k < lVertexIndexCount; ++k)
			{
				int lIndex = lCluster->GetControlPointIndices()[k];
				double lWeight = lCluster->GetControlPointWeights()[k];
				
				HXVertJointWeights xVertJointWeight;
				xVertJointWeight.nAttachJointIndex = lClusterIndex;
				xVertJointWeight.fWeightBias = (float)lWeight;
				
				std::map<int, std::vector<HXVertJointWeights>>::iterator pFind = mSkinSkeleton->mapVertJointInfo.find(lIndex);
				if (pFind != mSkinSkeleton->mapVertJointInfo.end())
				{
					pFind->second.push_back(xVertJointWeight);
				}
				else
				{
					mSkinSkeleton->mapVertJointInfo.insert(std::make_pair(lIndex, std::vector<HXVertJointWeights>())).first->second.push_back(xVertJointWeight);
				}
				
			}//For each vertex			
		}//lClusterCount

		for (std::map<int, std::vector<HXVertJointWeights>>::iterator itr = mSkinSkeleton->mapVertJointInfo.begin(); itr != mSkinSkeleton->mapVertJointInfo.end(); ++itr)
		{
			mSkinSkeleton->vctVertJointInfo.push_back(itr->second);
		}
	}

	void HXFBXSkeleton::LoadAnimationCurve(int nAnimIndex, std::string strAnimName, FbxScene* pScene)
	{
		mScene = pScene;
		mCurLoadAnimIndex = nAnimIndex;
		mCurLoadAnimName = strAnimName;

		// initialize cache start and stop time
		mCache_Start = FBXSDK_TIME_INFINITE;
		mCache_Stop = FBXSDK_TIME_MINUS_INFINITE;
		// mLastTime = 0.0;
		SetCurrentAnimStack(0);

		mFrameTime.SetTime(0, 0, 0, 1, 0, mScene->GetGlobalSettings().GetTimeMode());

		bool bFinish = false;
		while (!bFinish)
		{
			mCurrentTime += mFrameTime;
			if (mCurrentTime > mStop)
			{
				mCurrentTime = mStart;
				bFinish = true;
			}
			// mSkinSkeleton->nKeyNums++;
		
			// 加载关键帧
			// If one node is selected, draw it and its children.
			FbxAMatrix lDummyGlobalPosition;
			DrawNodeRecursive(mScene->GetRootNode(), mCurrentTime, mCurrentAnimLayer, lDummyGlobalPosition, NULL);

		}

		// bAnimationLoaded = true;
	}

	std::vector<std::string> HXFBXSkeleton::GetAnimNameList()
	{
		std::vector<std::string> lt;
		for (std::vector<HXJointAnim*>::iterator itr = mSkinSkeleton->xSkeleton.vctJoint[0]->vctJointAnim.begin(); itr != mSkinSkeleton->xSkeleton.vctJoint[0]->vctJointAnim.end(); ++itr)
		{
			lt.push_back((*itr)->strAnimName);
		}
		return lt;
	}

	FbxMesh* HXFBXSkeleton::GetMeshNodeRecursive(FbxNode* pNode)
	{
		if (pNode->GetNodeAttribute())
		{
			if (pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				return pNode->GetMesh();
			}
		}
		const int lChildCount = pNode->GetChildCount();
		for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
		{
			return GetMeshNodeRecursive(pNode->GetChild(lChildIndex));
		}
	}

	bool HXFBXSkeleton::IsHaveSkeleton(FbxScene* pScene)
	{
		FbxMesh* pFbxMesh = GetMeshNodeRecursive(pScene->GetRootNode());
		if (pFbxMesh)
		{
			const bool lHasSkin = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
			if (lHasSkin)
			{
				return true;
			}
		}
		return false;
	}

	bool HXFBXSkeleton::IsHaveSkeletonAnimation(FbxScene* pScene)
	{
		FbxArray<FbxString*> animStackNameArray;
		// Get the list of all the animation stack.
		pScene->FillAnimStackNameArray(animStackNameArray);

		const int lAnimStackCount = animStackNameArray.GetCount();
		if (lAnimStackCount <= 0)
		{
			return false;
		}

		// select the base layer from the animation stack
		FbxAnimStack * lCurrentAnimationStack = pScene->FindMember<FbxAnimStack>(animStackNameArray[0]->Buffer());
		if (lCurrentAnimationStack == NULL)
		{
			// this is a problem. The anim stack should be found in the scene!
			return false;
		}

		return true;

	}
}