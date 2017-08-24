#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXPlane.h"
#include "HXMatrix.h"

namespace HX3D
{
	// UVN相机
	struct HXFrustum
	{
		HXFrustum(const HXVector4D& pos, const HXVector4D& target
			, float ffov, float nearZ, float farZ
			, float viewportWidth, float viewportHeigth);

		void update();

		HXVector4D	camPosition;	// 相机世界坐标
		HXVector4D	lookTarget;	// 相机注视点

		HXVector4D	camU;	// 右基向量
		HXVector4D	camV;	// 上基向量
		HXVector4D	camN;	// 右手坐标系（OpenGl），N是后方；左手坐标系（D3D），N是前方      (Z轴方向).

		float	view_dist;	// 视点到投影平面的距离（由 fov 和 viewplane_width 计算而来）
		float	fov;	// 水平方向视野角度
		float	clip_z_near;	// 近裁截面
		float	clip_z_far;		// 远裁截面
		HXPlane3D	clip_plane_R;	// 右裁截面
		HXPlane3D	clip_plane_L;	// 左裁截面
		HXPlane3D	clip_plane_T;	// 上裁截面
		HXPlane3D	clip_plane_B;	// 下裁截面

		float	viewplane_width;	// 投影平面宽	// 固定为2
		float	viewplane_height;	// 投影平面高	// 对于归一化投影, 为2X2， 否则宽高比与屏幕窗口宽高比相同

		float	viewport_width;		// 游戏屏幕宽
		float	viewport_heigth;	// 游戏屏幕高
		float	viewport_center_X;	// 游戏屏幕中心坐标
		float	viewport_center_Y;	// 游戏屏幕中心坐标
		float	aspect_ratio;		// 游戏屏幕宽高比

		HXMatrix44	matWorldToCamera;	// 世界坐标系到相机坐标系转化矩阵
	};
}


