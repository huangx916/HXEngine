#include "..\include\HXFrustum.h"
#include "HXMath.h"
#include "HXQuaternion.h"

namespace HX3D
{
	HXFrustum::HXFrustum(const HXVector4D& pos, const HXVector4D& target
		, float ffov, float nearZ, float farZ
		, float viewportWidth, float viewportHeigth):mYaw(0), mPitch(0), mRoll(0)
	{
		camPosition = pos;
		lookTarget = target;
		fov = ffov;
		clip_z_near = nearZ;
		clip_z_far = farZ;
		viewport_width = viewportWidth;
		viewport_heigth = viewportHeigth;

		aspect_ratio = viewport_width / viewport_heigth;

		viewplane_width = 2.0f;
		viewplane_height = viewplane_width / aspect_ratio;

		float tan_fov_div2 = tan(Degree_TO_Radian(fov * 0.5f));
		view_dist = viewplane_width * 0.5f / tan_fov_div2;

		viewport_center_X = (viewport_width - 1) * 0.5f;
		viewport_center_Y = (viewport_heigth - 1) * 0.5f;

		// 裁截在相机坐标系下
		HXVector4D point = HXVector4D::ZERO;
		// 右裁截面
		HXVector4D normalR = HXVector4D(-view_dist, 0, viewplane_width * 0.5f);
		clip_plane_R = HXPlane3D(point, normalR);
		// 左裁截面
		HXVector4D normalL = HXVector4D(view_dist, 0, viewplane_width * 0.5f);
		clip_plane_L = HXPlane3D(point, normalL);
		// 上裁截面
		HXVector4D normalT = HXVector4D(0, -view_dist, viewplane_height * 0.5f);
		clip_plane_T = HXPlane3D(point, normalT);
		// 下裁截面
		HXVector4D normalB = HXVector4D(0, view_dist, viewplane_height * 0.5f);
		clip_plane_B = HXPlane3D(point, normalB);
	}

	void HXFrustum::update()
	{
		HXQuaternion q;
		q.FromEulerDegree(mPitch, mYaw, mRoll);
		HXVector3D vec = camPosition.xyz() - lookTarget.xyz();
		vec = q.Transform(vec);
		HXVector4D camPositionNew = lookTarget + HXVector4D(vec, 0);


		//HXMatrix44 matTransInv = GetTranslateMatrix44(-camPosition.x, -camPosition.y, -camPosition.z);
		HXMatrix44 matTransInv = GetTranslateMatrix44(-camPositionNew.x, -camPositionNew.y, -camPositionNew.z);

		//camN = lookTarget - camPosition;	// 此处N为相机前方，所以用左手坐标系
		camN = lookTarget - camPositionNew;	// 此处N为相机前方，所以用左手坐标系
		//camN = camPosition - lookTarget;	// 此处N为相机后方，所以用右手坐标系
		camU = HXVector4D::UNIT_Y.crossProduct(camN);
		camV = camN.crossProduct(camU);

		camN.normalize();
		camU.normalize();
		camV.normalize();
		HXMatrix44 matUVNInv = HXMatrix44(	camU.x, camV.x, camN.x, 0,
											camU.y, camV.y, camN.y, 0,
											camU.z, camV.z, camN.z, 0,
											0,		0,		0,		1);

		matWorldToCamera = matTransInv * matUVNInv;
	}
}

