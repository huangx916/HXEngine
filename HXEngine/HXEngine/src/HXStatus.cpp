#include "..\include\HXStatus.h"
#include <Windows.h>
#include "HXUtil.h"
#include "HXRenderSystem.h"
#include "HXRoot.h"

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
		/*std::string strFPS = "FPS: " + FloatToString(CalcLastFPS());
		HXGraphics::GetInstance()->DrawString(strFPS, SCREEN_WIDTH / 2, 0);

		std::string strTriangleCount = "TriangleCount: " + FloatToString(nTriangleCount);
		HXGraphics::GetInstance()->DrawString(strTriangleCount, SCREEN_WIDTH / 2, 18);

		std::string strVertexCount = "VertexCount: " + FloatToString(nVertexCount);
		HXGraphics::GetInstance()->DrawString(strVertexCount, SCREEN_WIDTH / 2, 36);*/

		HXRenderSystem* rs = HXRoot::GetInstance()->GetRenderSystem();
		if (NULL == rs)
		{
			return;
		}
		rs->BeginText();

		std::string strFPS = "FPS: " + FloatToString(CalcLastFPS());
		rs->_DrawText(SCREEN_WIDTH / 2, 0, strFPS.c_str(), HXCOLOR(255,0,0,255));

		std::string strTriangleCount = "TriangleCount: " + FloatToString(nTriangleCount);
		rs->_DrawText(SCREEN_WIDTH / 2, 18, strTriangleCount.c_str(), HXCOLOR(255, 0, 0, 255));

		std::string strVertexCount = "VertexCount: " + FloatToString(nVertexCount);
		rs->_DrawText(SCREEN_WIDTH / 2, 36, strVertexCount.c_str(), HXCOLOR(255, 0, 0, 255));

		rs->EndText();
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
