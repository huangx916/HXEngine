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
		mFrameCout = 0;
	}

	HXStatus::~HXStatus()
	{
	}

	void HXStatus::ShowStatusInfo()
	{
		std::string strFPS = "FPS: " + FloatToString(CalcLastFPS());
		HXGraphics::GetInstance()->DrawString(strFPS, SCREEN_WIDTH / 2, 0);
	}

	float HXStatus::CalcLastFPS()
	{
		mFrameCout++;
		double curTime = ::GetTickCount();
		if (curTime - mLastTime > 1000.0)
		{
			mLastFPS = (double)mFrameCout / (double)(curTime - mLastTime) * 1000.0;
			mLastTime = curTime;
			mFrameCout = 0;
		}
		return (float)mLastFPS;
	}
}
