#pragma once
#include "HXCommon.h"

namespace HX3D
{
	struct HXFrustum;

	enum RenderMode
	{
		RENDER_WIRE,	// 线框渲染
		RENDER_SOILD,	// 实体渲染
	};
	// 废弃的，请使用HXICamera类
	class HXCamera
	{
	public:
		~HXCamera();

		void setNearZ(float fNearZ);
		void setFarZ(float fFarZ);

		void update();
		// 相机世界坐标
		void setPosition(const HXVector4D& pos);
		// 目标点世界坐标
		void setTargetPos(const HXVector4D& pos);
		// 相机移动
		void move(const HXVector4D& mov);
		// 绕Y轴旋转
		void yaw(float fDegree);
		// 绕X轴旋转
		void pitch(float fDegree);

	//protected:
		// TODO: 只允许友元类 场景管理器创建相机
		HXCamera();

	//private:
		HXFrustum* mFrustum;
		bool mNeedUpdate;
	};
}
