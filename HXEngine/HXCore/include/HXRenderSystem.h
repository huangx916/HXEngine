#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXDisplayListener;
	class HXRenderable;
	class HXSubMesh;
	class HXICamera;
	class HXRenderSystem
	{
	public:
		HXRenderSystem();
		virtual ~HXRenderSystem();

		virtual void CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen);
		void SetDisplayListener(HXDisplayListener* pDisplayListener);
		virtual void MainLoop() = 0;

		virtual HXRenderable* GenerateRenderable(HXSubMesh* pSubMesh) = 0;
		virtual void RenderSingle(HXRenderable* pRenderable) = 0;

		virtual HXICamera* CreateCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
			float left, float right, float bottom, float top) = 0;

		// virtual void DrawString() = 0;

		static HXDisplayListener* m_pDisplayListener;
		//static int gCurScreenWidth;
		//static int gCurScreenHeight;
		//static float gAspect;	// ×Ýºá±È
	};
}