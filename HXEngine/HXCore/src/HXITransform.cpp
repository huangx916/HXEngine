#include "..\include\HXITransform.h"

namespace HX3D
{
	HXITransform::HXITransform()
	{
		mPostion = HXVector3D(0,0,0);
		mEulerDegree = HXVector3D(0,0,0);
		mScale = HXVector3D(1,1,1);
	}

	HXITransform::~HXITransform()
	{
	}

	void HXITransform::SetPosition(const HXVector3D& pos)
	{
		mPostion = pos;
	}

	HXVector3D HXITransform::GetPosition()
	{
		return mPostion;
	}

	void HXITransform::Move(const HXVector3D& mov)
	{
		mPostion += mov;
	}

	void HXITransform::SetRotation(const HXVector3D& rotation)
	{
		mEulerDegree = rotation;
	}

	HXVector3D HXITransform::GetRotation()
	{
		return mEulerDegree;
	}

	void HXITransform::Pitch(float fDegree)
	{
		mEulerDegree.x = fDegree;
	}

	void HXITransform::Yaw(float fDegree)
	{
		mEulerDegree.y = fDegree;
	}

	void HXITransform::Roll(float fDegree)
	{
		mEulerDegree.z = fDegree;
	}

	void HXITransform::SetScale(const HXVector3D& scale)
	{
		mScale = scale;
	}
	HXVector3D HXITransform::GetScale()
	{
		return mScale;
	}
}