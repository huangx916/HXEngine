#pragma once
#include "HXCommon.h"
#include "HXVector.h"
#include "HXMatrix.h"
#include "HXITransform.h"

namespace HX3D
{
	class HXMesh;
	struct HXRenderList;
	class HXRenderSystem;
	class HXGameObject
	{
	public:
		HXGameObject(std::string strName, HXMesh* pMesh, HXRenderSystem* pRenderSystem);
		~HXGameObject();
	
		void Update();

		//void Insert_To_RenderList(HXRenderList* pRenderList);
		void SetPostion(const HXVector3D& pos);
		HXVector3D GetPosition();
		void Move(const HXVector3D& mov);

		void SetRotation(const HXVector3D& rotation);
		HXVector3D GetRotation();
		void Pitch(float fDegree);	// 绕X轴旋转
		void Yaw(float fDegree);	// 绕Y轴旋转
		void Roll(float fDegree);	// 绕Z轴旋转
		
		void SetScale(const HXVector3D& scale);
		HXVector3D GetScale();

		HXMesh* GetMesh();
		HXGameObject* GetFather();
		void SetFather(HXGameObject* father);
		HXITransform* GetTransform();

		// 渲染优先级
		int m_nPriority;
		bool m_bCastShadow;
		
	private:
		std::string m_strName;
		// Local Coordinate
		/*HXVector3D mPostion;
		HXVector3D mEulerDegree;
		HXVector3D mScale;*/
		HXITransform* m_pTransform;

		HXMesh* m_pMesh;
		// TODO: config中暂时只支持两层 prefabgameobj--->modelgameobj
		HXGameObject* m_pFather;	// 用作计算World Coordinate
	};
}


