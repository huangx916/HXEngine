//#pragma once
//#include "HXCommon.h"
//#include <Windows.h>
////#include "HXPaintListener.h"	//防止HXPaintListener.h改动后，包含Windows.h的其它文件(例如HXWinMain.cpp)重复编译
////#include "HXInputListener.h"
//namespace HX3D
//{
//class HXPaintListener;
//class HXInputListener;
//
//	class HXWindow
//	{
//	private:
//		// 单例模式
//		static HXWindow* pInstance;
//		HXWindow();	//单例模式构造函数是私有的,防止外部直接new
//	public:
//		static HXWindow* GetInstance()
//		{
//			if (NULL == pInstance)
//			{
//				pInstance = new HXWindow;
//			}
//			return pInstance;
//		}
//		~HXWindow();
//
//		void StartWindow(LPCTSTR lpClassName, LPCTSTR lpWinName, HINSTANCE hInstance);
//		void StartLoop();
//		void ShutDownWindow();
//		void SetPaintListener(HXPaintListener* pHXPaintListener);
//		void AddInputListener(HXInputListener* pHXInputListener);
//		void RemoveInputListener(HXInputListener* pHXInputListener);
//
//		void TestCreateGLWindow(int argc, char* argv[]);
//	private:
//		// 2、窗口过程函数(必须要是全局函数)
//		static LRESULT CALLBACK MyWindowProc(
//			_In_ HWND   hwnd,
//			_In_ UINT   uMsg,
//			_In_ WPARAM wParam,
//			_In_ LPARAM lParam
//		);
//		// 3、注册窗口类型
//		BOOL RegisterMyWindow(LPCSTR lpcWndName, HINSTANCE hInstance);
//		// 4、创建窗口（lpClassName 一定是已经注册过的窗口类型）
//		HWND CreateMyWindow(LPCTSTR lpClassName, LPCTSTR lpWinName, HINSTANCE hInstance);
//		// 5、 显示窗口
//		void DisplayMyWnd(HWND hWnd);
//		// 刷新窗口
//		void UpdateMyWnd(HWND hWnd);
//		// 绘画回调
//		void OnPaint(HDC hdc);
//		// 按键回调
//		void OnKeyDown(int msg);
//		void OnKeyUp(int msg);
//
//	private:
//		HXPaintListener* m_pPaintListener;
//		std::vector<HXInputListener*> m_vec_pInputListener;
//		typedef std::vector<HXInputListener*>::iterator InputItr;
//
//		HWND m_hWnd;
//	};
//}