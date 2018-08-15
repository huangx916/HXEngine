#include "..\include\HXITransform.h"
#include "HXGameObject.h"

namespace HX3D
{
	HXITransform::HXITransform()
	{
		mLocalPostion = HXVector3D(0,0,0);
		mLocalEulerDegree = HXVector3D(0,0,0);
		mLocalScale = HXVector3D(1,1,1);
	}

	HXITransform::~HXITransform()
	{
	}

	void HXITransform::SetLocalPosition(const HXVector3D& pos)
	{
		mLocalPostion = pos;
	}

	const HXVector3D& HXITransform::GetLocalPosition()
	{
		return mLocalPostion;
	}

	/*const HXVector3D& HXITransform::GetGlobalPosition()
	{

	}*/

	void HXITransform::Move(const HXVector3D& mov)
	{
		mLocalPostion += mov;
	}

	void HXITransform::SetLocalRotation(const HXVector3D& rotation)
	{
		mLocalEulerDegree = rotation;
	}

	const HXVector3D& HXITransform::GetLocalRotation()
	{
		return mLocalEulerDegree;
	}

	void HXITransform::Pitch(float fDegree)
	{
		mLocalEulerDegree.x = fDegree;
	}

	void HXITransform::Yaw(float fDegree)
	{
		mLocalEulerDegree.y = fDegree;
	}

	void HXITransform::Roll(float fDegree)
	{
		mLocalEulerDegree.z = fDegree;
	}

	void HXITransform::SetLocalScale(const HXVector3D& scale)
	{
		mLocalScale = scale;
	}

	const HXVector3D& HXITransform::GetLocalScale()
	{
		return mLocalScale;
	}

	void HXITransform::AddChild(HXITransform* child)
	{
		vctChildren.push_back(child);
	}

	std::vector<HXITransform*>& HXITransform::GetChildren()
	{
		return vctChildren;
	}
}