#pragma once
#include "HXCommon.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	class HXGLRenderSystem : public HXRenderSystem
	{
	public:
		HXGLRenderSystem();
		~HXGLRenderSystem();

		virtual void CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen);
		virtual void MainLoop();
		static void Display();
		static void Reshape(int nWidth, int nHeight);

		virtual HXRenderable* GenerateRenderable(HXSubMesh* pSubMesh);
		virtual void RenderSingle(HXRenderable* pRenderable);

		virtual HXICamera* CreateCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
			float left, float right, float bottom, float top);
	};
}