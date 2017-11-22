#pragma once
#include "HXCommon.h"
#include "HXRenderSystem.h"
#include <windows.h>

namespace HX3D
{
	class HXGDIRenderSystem : public HXRenderSystem
	{
	public:
		HXGDIRenderSystem();
		~HXGDIRenderSystem();

		virtual void CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen);
		virtual void MainLoop();
		static void Display(HDC hdc);
		static void Reshape(int nWidth, int nHeight);

		virtual HXRenderable* GenerateRenderable(HXSubMesh* pSubMesh);
		virtual void RenderSingle(HXRenderable* pRenderable);

		virtual HXICamera* CreateCamera(const HXVector3D& eye, const HXVector3D& at, const HXVector3D& up,
			float ffov, float nearZ, float farZ, float viewportWidth, float viewportHeigth,
			float left, float right, float bottom, float top);

		//virtual void BeginText();
		virtual void _DrawText(float x, float y, std::string text, const HXCOLOR& color = HXCOLOR(255,255,255,255));
		//virtual void EndText();

	private:
		// 2、窗口过程函数(必须要是全局函数)
		static LRESULT CALLBACK MyWindowProc(
			_In_ HWND   hwnd,
			_In_ UINT   uMsg,
			_In_ WPARAM wParam,
			_In_ LPARAM lParam
		);
		// 3、注册窗口类型
		BOOL RegisterMyWindow(LPCSTR lpcWndName, HINSTANCE hInstance);
		// 4、创建窗口（lpClassName 一定是已经注册过的窗口类型）
		HWND CreateMyWindow(LPCTSTR lpClassName, LPCTSTR lpWinName, HINSTANCE hInstance);
		// 5、 显示窗口
		void DisplayMyWnd(HWND hWnd);
		// 刷新窗口
		void UpdateMyWnd(HWND hWnd);

		HWND m_hWnd;
	};
}


