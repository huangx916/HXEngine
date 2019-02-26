#pragma once
#include "HXCommon.h"
#include "HXRenderSystem.h"

namespace HX3D
{
	class HXITransform;
	class HXIFreeTypeFont;
	class HXGLShadowMap;
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
		virtual void RenderSingle(HXRenderable* pRenderable, bool shadow);

		virtual HXICamera* CreateCamera(const HXCameraInfo* cameraInfo);

		virtual void BeginText();
		virtual void _DrawText(float x, float y, std::string text, const HXColor& color = HXColor(255, 255, 255, 255));
		virtual void EndText();

		virtual HXITransform* CreateTransform();
		virtual HXMaterial* CreateMaterial(HXMaterialInfo* info);
		virtual void InitDefaultRenderTarget();
		virtual HXRenderTarget* GetDefaultRenderTarget();
		virtual HXRenderTarget* CreateRenderTarget(int width, int height);

		static void RenderScene();
		void Initialize();
		virtual void InitForEditor();

		HXIFreeTypeFont* mFont;
		static HXGLShadowMap* mShadowMap;
		HXRenderTarget* mDefaultRenderTarget;
	};
}