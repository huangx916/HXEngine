#include "..\include\HXStatus.h"
#include <Windows.h>
#include "HXUtil.h"
#include "HXGraphics.h"
namespace HX3D
{
	HXStatus* HXStatus::pInstance = NULL;

	HXStatus::HXStatus()
	{
		mLastFPS = 0.0;
		mLastTime = 0.0;
		mFrameCount = 0;
	}

	HXStatus::~HXStatus()
	{
	}

	void HXStatus::ResetStatus()
	{
		nVertexCount = 0;
		nTriangleCount = 0;
	}

	void HXStatus::ShowStatusInfo()
	{
		std::string strFPS = "FPS: " + FloatToString(CalcLastFPS());
		HXGraphics::GetInstance()->DrawString(strFPS, SCREEN_WIDTH / 2, 0);

		std::string strTriangleCount = "TriangleCount: " + FloatToString(nTriangleCount);
		HXGraphics::GetInstance()->DrawString(strTriangleCount, SCREEN_WIDTH / 2, 18);

		std::string strVertexCount = "VertexCount: " + FloatToString(nVertexCount);
		HXGraphics::GetInstance()->DrawString(strVertexCount, SCREEN_WIDTH / 2, 36);
	}

	float HXStatus::CalcLastFPS()
	{
		mFrameCount++;
		double curTime = ::GetTickCount();
		if (curTime - mLastTime > 1000.0)
		{
			mLastFPS = (double)mFrameCount / (double)(curTime - mLastTime) * 1000.0;
			mLastTime = curTime;
			mFrameCount = 0;
		}
		return (float)mLastFPS;
	}
}
