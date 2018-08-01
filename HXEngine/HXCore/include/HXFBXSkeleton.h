#pragma once
#include "HXCommon.h"
#include <fbxsdk.h>
#include "HXISkeleton.h"
#include <map>

namespace HX3D
{
	struct HXJointPose 
	{
		FbxAMatrix mtVertexTransformMatrix;
	};

	struct HXJointAnim 
	{
		HXJointAnim()
		{
			nKeyNums = 0;
		}
		std::string strAnimName;
		int nKeyNums;
		std::vector<HXJointPose*> vctJointPose;
	};

	struct HXJoint 
	{
		std::vector<HXJointAnim*> vctJointAnim;
	};

	struct HXSkeleton
	{
		HXSkeleton()
		{
			nJointCount = 0;
		}
		int nJointCount;
		std::vector<HXJoint*> vctJoint;
	};

	/*struct HXJointPose
	{
		FbxAMatrix mtVertexTransformMatrix;
	};

	struct HXJointAnim
	{
		HXJointAnim()
		{
			nKeyNums = 0;
		}
		int nKeyNums;
		std::vector<HXJointPose*> vctJointPose;
	};

	struct HXSkeletonAnim
	{
		HXSkeletonAnim()
		{
			nJointCount = 0;
		}
		int nJointCount;
		std::string strAnimName;
		std::vector<HXJointAnim*> vctJoint;
	};

	struct HXSkeleton
	{
		std::map<std::string, HXSkeletonAnim*> mapSkeletonAnim;
	};*/

	struct HXVertJointWeights 
	{
		HXVertJointWeights()
		{
			nAttachJointIndex = -1;
			fWeightBias = 0;
		}
		int nAttachJointIndex;
		float fWeightBias;
	};

	struct HXSkinSkeleton 
	{
		HXSkeleton xSkeleton;
		std::map<int, std::vector<HXVertJointWeights>> mapVertJointInfo;	//#include <map>
		// update时使用vector以提高性能
		std::vector<std::vector<HXVertJointWeights>> vctVertJointInfo;
	};

	class HXFBXMesh;
	class HXFBXSkeleton : public HXISkeleton
	{
	public:
		HXFBXSkeleton();
		~HXFBXSkeleton();

		virtual void UpdateAnimation(HXAnimationInstance* pAnimInst);

		static bool IsHaveSkeleton(FbxScene* pScene);
		// 加载骨骼
		void LoadSkeleton(FbxScene* pScene);
		// 加载骨骼动画
		void LoadAnimationCurve(int nAnimIndex, std::string strAnimName, FbxScene* pScene);

		virtual std::vector<std::string> GetAnimNameList();

	private:

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

		//// virtual void Update();
		// virtual HXISkeleton* Clone(HXMesh* pMesh);
		void Initial(FbxScene* pScene);

		static FbxMesh* GetMeshNodeRecursive(FbxNode* pNode);
		
		static bool IsHaveSkeletonAnimation(FbxScene* pScene);

		FbxArray<FbxString*> mAnimStackNameArray;
		FbxAnimLayer * mCurrentAnimLayer;
		FbxTime mFrameTime, mStart, mStop, mCurrentTime;
		FbxTime mCache_Start, mCache_Stop;
		FbxScene * mScene;
		double mLastTime;
		std::string mCurLoadAnimName;
		int mCurLoadAnimIndex;

		HXSkinSkeleton* mSkinSkeleton;
		FbxVector4* srcControlPoints;
		int nControlPointCount;
		// bool bAnimationLoaded;

		/*int nCurKeyframe;
		int nSpeed;
		HXFBXMesh* mMesh;*/
	};
}
