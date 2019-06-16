#pragma once

#include <string>
#include <vector>
#include <list>
//#include <deque>
#include <iostream>
#include "HX3DHeader.h"
// #include "HXMath.h"	// 交叉包含
#include "HXColor.h"

namespace HX3D
{
	const std::string Version = "1.0.0";

	// 窗口大小
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	// 数学常量
	#define PI			3.141592654f
	#define PI2			(PI*2.0f)
	#define PI_DIV_2	(PI*0.5f)
	#define PI_DIV_4	(PI*0.25f)
	#define PI_INV		0.318309886f

	// 角度转弧度
	#define Degree_TO_Radian(deg)	(deg * PI / 180)
	// 弧度转角度
	#define Radian_TO_Degree(rad)	(rad * 180 * PI_INV)

	// 计算精度
	#define EPSILON_E6	((float)(1E-6))

	// shadow mapping
	#define FRUSTUM_DEPTH       80.0f
	#define DEPTH_TEXTURE_SIZE  1024
	#define ORTHO_HALF_SIZE		10
	#define ORTHO_DISTANCE		10

	#define HX_ARRAY_SIZE(_array_) (sizeof(_array_) / sizeof(_array_[0]))

	//#define HXColor_TO_24BIT(r,g,b)		(((r) & 0xff) << 16 | ((g) & 0xff) << 8 | ((b) & 0xff))

#define HX_SAFE_DELETE(_pointer_) \
    if (_pointer_ != nullptr) {\
        delete _pointer_; \
        _pointer_ = nullptr; \
    }

#define HX_SAFE_DELETE_ARRAY(_pointer_) \
    if (_pointer_ != nullptr) { \
        delete[] _pointer_; \
        _pointer_ = nullptr; \
    }

#define HX_SAFE_RELEASE(_pointer_) \
    if (_pointer_ != nullptr) { \
        _pointer_->Release(); \
        _pointer_ = nullptr; \
    }

	enum ERenderSystem
	{
		RenderSystem_GDI,
		RenderSystem_GL,
		RenderSystem_D3D
	};

	enum ERenderQueue
	{
		RQ_BACKGROUND = 1000,
		RQ_GEOMETRY = 2000,
		RQ_ALPHATEST = 2450,
		RQ_TRANSPARENT = 3000,
		RQ_OVERLAY = 4000
	};

	enum ELayer
	{
		L_DEFAULT,
		L_UI,
		L_EDITOR,
		L_WATER,
		L_ERMAP
	};

	enum ECullingMask
	{
		CM_NOTHING,
		CM_EVERYTHING,
		CM_DEFAULT,
		CM_UI,
		CM_EDITOR,
		CM_WATER,
		CM_ERMAP
	};

	inline bool IsCulled(ELayer layer, ECullingMask mask)
	{
		if (mask == CM_NOTHING)
		{
			return true;
		}
		else if (mask == CM_EVERYTHING)
		{
			return false;
		}
		else if (layer + 2 == mask)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	enum ECameraProjection
	{
		CP_ORTHOGRAPHIC,
		CP_PERSPECTIVE
	};

	enum EClearFlag
	{
		//CF_SKYBOX,
		CF_SOLIDCOLOR,
		CF_DEPTHONLY,
		CF_DONTCLEAR
	};

	enum class ETextureWrapMode
	{
		TWM_REPEAT,
		TWM_CLAMP
	};

	enum class ETextureFilterMode
	{
		TFM_POINT,
		TFM_BILINEAR,
		TFM_TRILINEAR
	};

	// TODO: 如何根据当前子网格顶点数动态生成顶点数组大小
	const int MAX_TRIANGLE_COUNT = 100000;	// 最大子网格面数
}
