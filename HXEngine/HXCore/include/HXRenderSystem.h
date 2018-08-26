#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXIDisplayListener;
	class HXRenderable;
	class HXSubMesh;
	class HXICamera;
	class HXITransform;
	class HXMaterial;
	struct HXMaterialInfo;
	struct HXCameraInfo;
	class HXRenderTarget;
	class HXRenderSystem
	{
	public:
		HXRenderSystem();
		virtual ~HXRenderSystem();

		virtual void CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen) = 0;
		void SetDisplayListener(HXIDisplayListener* pDisplayListener);
		virtual void MainLoop() = 0;

		virtual HXRenderable* GenerateRenderable(HXSubMesh* pSubMesh) = 0;
		virtual void RenderSingle(HXRenderable* pRenderable, bool shadow) = 0;

		virtual HXICamera* CreateCamera(const HXCameraInfo* cameraInfo) = 0;

		virtual HXITransform* CreateTransform() = 0;

		virtual HXMaterial* CreateMaterial(HXMaterialInfo* info) = 0;

		virtual void InitDefaultRenderTarget() {};
		virtual HXRenderTarget* GetDefaultRenderTarget() { return NULL; };
		virtual HXRenderTarget* CreateRenderTarget() { return NULL; };

		ERenderSystem GetRenderSystemType();
		void SetRenderSystemType(ERenderSystem rs);

		virtual void InitForEditor() {};

		virtual void BeginText() {};
		virtual void _DrawText(float x, float y, std::string text, const HXCOLOR& color = HXCOLOR(255, 255, 255, 255)) = 0;
		virtual void EndText() {};

		static void Reshape(int nWidth, int nHeight);
		static void Keyboard(unsigned char key, int x, int y);
		static void Mouse(int button, int state, int x, int y);
		static void MouseMotion(int x, int y);
		static int mLastX;
		static int mLastY;
		static int mButtonDown;

		static HXIDisplayListener* m_pDisplayListener;
		static int gCurScreenWidth;
		static int gCurScreenHeight;
		//static float gAspect;	// ×Ýºá±È
	private:
		ERenderSystem m_eRenderSystemType;
	};
}