#pragma once
#include "HXCommon.h"
#include "HXITransform.h"
#include "vmath.h"

namespace HX3D
{
	// TODO: 与HXGDITransform合并
	// 中间过程不需要转，最后转成GLSL所需类型就行
	// 右手坐标系
	class HXGLTransform : public HXITransform
	{
	public:
		HXGLTransform();
		~HXGLTransform();

		static vmath::mat4 ConvertMatrix(HXMatrix44& mat);
		static HXMatrix44 UnConvertMatrix(vmath::mat4& mat);

		virtual HXVector3D GetGlobalPosition();
		virtual HXVector3D GetGlobalRotation();
		virtual HXVector3D GetGlobalScale();

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix);
		virtual void CaculateModelMatrix();
	};
}


