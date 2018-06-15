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

		inline void AddReference(HXMesh* pMesh)
		{
			vctBeReferenced.push_back(pMesh);
		};

		inline bool ReduceReference(HXMesh* pMesh)
		{
			for (std::vector<HXMesh*>::iterator itr = vctBeReferenced.begin(); itr != vctBeReferenced.end(); ++itr)
			{
				if (*itr == pMesh)
				{
					vctBeReferenced.erase(itr);
					break;
				}
			}
			if (vctBeReferenced.size() == 0)
			{
				return true;
			}
			return false;
		};
	private:
		std::vector<HXMesh*> vctBeReferenced;
	};
}