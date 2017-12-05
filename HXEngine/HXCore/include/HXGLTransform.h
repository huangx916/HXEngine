#pragma once
#include "HXCommon.h"
#include "HXITransform.h"
#include "vmath.h"

namespace HX3D
{
	// ÓÒÊÖ×ø±êÏµ
	class HXGLTransform : public HXITransform
	{
	public:
		HXGLTransform();
		~HXGLTransform();

		static vmath::mat4 ConvertMatrix(HXMatrix44& mat);
		static HXMatrix44 UnConvertMatrix(vmath::mat4& mat);

		virtual void CaculateModelMatrix(HXMatrix44& fatherModelMatrix);
		virtual void CaculateModelMatrix();
	};
}


