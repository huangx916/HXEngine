#pragma once
#include "HXCommon.h"
#include <fbxsdk.h>
#include "HXISkeleton.h"

namespace HX3D
{
	class HXMeshFBX;

	class HXSkeletonFBX : public HXISkeleton
	{
	public:
		HXSkeletonFBX();
		~HXSkeletonFBX();

		void MatrixScale(FbxAMatrix& pMatrix, double pValue);
		void MatrixAddToDiagonal(FbxAMatrix& pMatrix, double pValue);
		void MatrixAdd(FbxAMatrix& pDstMatrix, FbxAMatrix& pSrcMatrix);

		FbxAMatrix GetPoseMatrix(FbxPose* pPose,
			int pNodeIndex);

		FbxAMatrix GetGlobalPosition(FbxNode* pNode,
			const FbxTime& pTime,
			FbxPose* pPose = NULL,
			FbxAMatrix* pParentGlobalPosition = NULL);

		FbxAMatrix GetGeometry(FbxNode* pNode);

		void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition,
			FbxMesh* pMesh,
			FbxCluster* pCluster,
			FbxAMatrix& pVertexTransformMatrix,
			FbxTime pTime,
			FbxPose* pPose);

		void ComputeLinearDeformation(FbxAMatrix& pGlobalPosition,
			FbxMesh* pMesh,
			FbxTime& pTime,
			FbxVector4* pVertexArray,
			FbxPose* pPose);

		void ComputeSkinDeformation(FbxAMatrix& pGlobalPosition,
			FbxMesh* pMesh,
			FbxTime& pTime,
			FbxVector4* pVertexArray,
			FbxPose* pPose);

		void DrawMesh(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
			FbxAMatrix& pGlobalPosition, FbxPose* pPose);

		void DrawNode(FbxNode* pNode,
			FbxTime& lTime,
			FbxAnimLayer * pAnimLayer,
			FbxAMatrix& pParentGlobalPosition,
			FbxAMatrix& pGlobalPosition,
			FbxPose* pPose);

		void DrawNodeRecursive(FbxNode* pNode, FbxTime& pTime, FbxAnimLayer* pAnimLayer,
			FbxAMatrix& pParentGlobalPosition,
			FbxPose* pPose);

		// The input index is corresponding to the array returned from GetAnimStackNameArray.
		bool SetCurrentAnimStack(int pIndex);

		virtual void Update();
		virtual HXISkeleton* Clone(HXMesh* pMesh);
		void Initial(HXMeshFBX* pMesh, FbxScene* pScene);

		FbxArray<FbxString*> mAnimStackNameArray;
		FbxAnimLayer * mCurrentAnimLayer;
		FbxTime mFrameTime, mStart, mStop, mCurrentTime;
		FbxTime mCache_Start, mCache_Stop;
		FbxScene * mScene;
		HXMeshFBX* mMesh;

		double mLastTime;
	};
}
