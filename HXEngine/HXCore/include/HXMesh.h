#pragma once
#include "HXCommon.h"
#include "HXVector.h"

namespace HX3D
{
	class HXRenderList;
	class HXISkeleton;
	class HXAnimationInstance;

	struct HXVertex
	{
		//HXVertex() {}
		//HXVertex(const HXVector3D& pos_, const HXCOLOR& color_): pos(pos_),color(color_) {}
		HXVector3D pos;
		int ctrlPointIndex;	// 骨骼动画更新时控制点映射到顶点用
		HXVector3D normal;
		HXCOLOR	color;
		float u;
		float v;

		HXVertex interp(const HXVertex& rhs, float factor)
		{
			HXVertex vertex;
			//vertex.pos.x = pos.x * (1 - factor) + rhs.pos.x * factor;
			vertex.pos.x = pos.x + (rhs.pos.x - pos.x)*factor;
			vertex.pos.y = pos.y + (rhs.pos.y - pos.y)*factor;
			vertex.pos.z = pos.z + (rhs.pos.z - pos.z)*factor;

			vertex.color.r = color.r + (rhs.color.r - color.r)*factor;
			vertex.color.g = color.g + (rhs.color.g - color.g)*factor;
			vertex.color.b = color.b + (rhs.color.b - color.b)*factor;
			vertex.color.a = color.a + (rhs.color.a - color.a)*factor;

			vertex.u = u + (rhs.u - u)*factor;
			vertex.v = v + (rhs.v - v)*factor;

			return vertex;
		}

		inline HXVertex& operator+=(const HXVertex& rhs)
		{
			pos += rhs.pos;
			color += rhs.color;
			u += rhs.u;
			v += rhs.v;
			return *this;
		}

		inline HXVertex operator-(const HXVertex& rhs) const
		{
			HXVertex vertex;
			vertex.pos = pos - rhs.pos;
			vertex.color = color - rhs.color;
			vertex.u = u - rhs.u;
			vertex.v = v - rhs.v;
			return vertex;
		}

		inline HXVertex operator/(float rhs) const
		{
			HXVertex vertex;
			vertex.pos = pos / rhs;
			vertex.color = color / rhs;
			vertex.u = u / rhs;
			vertex.v = v / rhs;
			return vertex;
		}
	};

	struct HXScanline 
	{
		HXScanline(HXVertex v_, const HXVertex& step_, int x_, int y_, float width_)
			:v(v_), step(step_), x(x_), y(y_), width(width_){}
		HXVertex v;		// 当前点
		HXVertex step;	// 点之间的步进
		int x;	// 起始X
		int y;	// 扫描线Y
		float width;	// 扫描线宽度
	};

	class HXSubMesh
	{
	public:
		HXSubMesh();
		~HXSubMesh();

		HXSubMesh* Clone();

		void Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList);

		bool useIndex;
		std::vector<HXVertex>	vertexList;
		std::vector<int>	indexList;

		std::string materialName;

		int triangleCount;

	private:
		void Insert_To_RenderList_Without_Index(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList);
		void Insert_To_RenderList_With_Index(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList);
	};

	class HXMesh
	{
	public:
		HXMesh();
		virtual ~HXMesh();

		void PlayAnimation(std::string strAnimName, int nSpeed = 1);
		void UpdateAnimation();

		HXMesh* Clone();

		// For Test
		void CreateCubeForTest();
		void CreateTriangleForTest();
		void CreateQuadForTest();

		void Insert_To_RenderList(const HXVector3D& pos, const HXVector3D& eulerDegree, const HXVector3D& scale, HXRenderList* pRenderList);

		std::vector<HXSubMesh*> subMeshList;

		int triangleCount;
		int vertexCount;
		HXISkeleton* skeleton;
		HXAnimationInstance* animInst;	// 只有实例化到场景的MESH才会new
	};
}


