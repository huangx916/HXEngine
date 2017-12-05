#pragma once
#include "HXMesh.h"

namespace HX3D
{
	struct HXAnimationInstance
	{
		std::string strCurPlayAnim;
		int nCurKeyframe;
		int nSpeed;
		HXMesh* mMesh;
	};
	class HXISkeleton
	{
	public:
		HXISkeleton() {};
		virtual ~HXISkeleton() {};

		//// virtual void Update() = 0;
		virtual void UpdateAnimation(HXAnimationInstance* pAnimInst) = 0;
		//virtual HXISkeleton* Clone(HXMesh* pMesh) = 0;
		virtual std::vector<std::string> GetAnimNameList() = 0;
	};
}