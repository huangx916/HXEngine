#include "HXWindow.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
#include "HXGraphics.h"
#include "HXPaintListener.h"
#include "HXInputListener.h"
#include<ctime>
#include "HXStatus.h"

//using namespace std;

//int main(int argc, char* argv[])
//{
//	printf("%d\n", argc);
//	for (int i = 0; i < argc; i++)
//	{
//		printf("%s\n", argv[i]);
//	}
//	cout << "hello world" << endl;
//	printf("%s\n", "hello world");
//	system("pause");
//	return 0;
//}

namespace HX3D
{
	//--------------------------GLOBAL------------------------------------------
	HXWindow* HXWindow::pInstance;

	// 2、窗口过程函数
	LRESULT CALLBACK HXWindow::MyWindowProc(
		_In_ HWND   hwnd,
		_In_ UINT   uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	)
	{
		if (NULL == HXWindow::pInstance)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		//判断消息ID
		switch (uMsg)
		{
		case WM_MOVING:
		/*{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);
			HXWindow::pInstance->OnPaint(hdc);
			EndPaint(hwnd, &ps);
			break;
		}*/
		case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);
			HXWindow::pInstance->OnPaint(hdc);
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_TIMER:
		{
			// 加上，不然画面不会刷新
			HXWindow::pInstance->UpdateMyWnd(hwnd);
			break;
		}
		case WM_KEYDOWN:
		{
			HXWindow::GetInstance()->OnKeyDown(wParam);
			break;
		}
		case WM_KEYUP:
		{
			HXWindow::GetInstance()->OnKeyUp(wParam);
			break;
		}
		case WM_DESTROY:	// 窗口销毁消息
		{
			PostQuitMessage(0);	//  发送退出消息
			break;
		}
		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
			break;
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	// 其他的消息调用缺省的消息处理程序
		}
		return 0;
	}

	//------------------------------------------------------------------------------------------------------

	HXWindow::HXWindow()
	{
		HXGraphics::GetInstance()->InitGraphics();
	}

	HXWindow::~HXWindow()
	{

	}

	void HXWindow::StartWindow(LPCTSTR lpClassName, LPCTSTR lpWinName, HINSTANCE hInstance)
	{
		//HWND hWnd = NULL;
		RegisterMyWindow(lpClassName, hInstance);
		m_hWnd = CreateMyWindow(lpClassName, lpWinName, hInstance);
		DisplayMyWnd(m_hWnd);
	}

	void HXWindow::ShutDownWindow()
	{
		HXGraphics::GetInstance()->ShutDownGraphics();
	}

	// 3、注册窗口类型
	BOOL HXWindow::RegisterMyWindow(LPCSTR lpcWndName, HINSTANCE hInstance)
	{
		ATOM nAtom = 0;

		// 构造创建窗口参数
		WNDCLASS wndClass = { 0 };

		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = MyWindowProc;      // 指向窗口过程函数
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;
		//wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(100));// 100为在HelloWorld.rc文件中定义的ID号
		wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		/*wndClass.hCursor = NULL;*/	// 游戏启动后鼠标指针还转圈圈
		wndClass.hCursor = LoadCursor(0, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = lpcWndName;    // 注册的窗口名称，并非标题，以后创建窗口根据此注册的名称创建

		nAtom = RegisterClass(&wndClass);
		if (0 == nAtom)
		{
			MessageBox(NULL, "Register Failed",
				"Error", MB_OK | MB_ICONERROR);
			return FALSE;
		}
		else
		{
			/*MessageBox(NULL, "Register Successed",
				"Sucessed", MB_OK);*/
		}
		return TRUE;
	}

	// 4、创建窗口（lpClassName 一定是已经注册过的窗口类型）
	HWND HXWindow::CreateMyWindow(LPCTSTR lpClassName, LPCTSTR lpWinName, HINSTANCE hInstance)
	{
		HWND hWnd = NULL;
		// 创建窗口
		hWnd = CreateWindow(lpClassName, lpWinName,
			WS_OVERLAPPEDWINDOW & (~WS_MAXIMIZEBOX)& (~WS_THICKFRAME),
			0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
			NULL, NULL, hInstance, NULL);

		if (NULL == hWnd)
		{
			MessageBox(NULL, "Create Window Failed",
				"Error", MB_OK | MB_ICONERROR);
		}
		else
		{
			/*MessageBox(NULL, "Create Winodw Successed",
				"Successed", MB_OK);*/
		}

		::SetTimer(hWnd, WM_TIMER, 15, NULL);	// 每15毫秒传送一次WM_TIMER消息 
		// 手动播种
		srand((unsigned)time(NULL));

		return hWnd;
	}

	// 5、 显示窗口
	void HXWindow::DisplayMyWnd(HWND hWnd)
	{
		::ShowWindow(hWnd, SW_SHOW);
		::UpdateWindow(hWnd);
	}

	void HXWindow::UpdateMyWnd(HWND hWnd)
	{
		::InvalidateRect(hWnd, NULL, FALSE);	// 要求重新绘制
		::UpdateWindow(hWnd);
	}

	// 消息循环处理函数
	void HXWindow::StartLoop()
	{
		MSG msg = { 0 };
		// 获取消息
		//while (GetMessage(&msg, NULL, 0, 0))	// 当接收到WM_QIUT消息时，GetMessage函数返回0，结束循环
		//{
		//	DispatchMessage(&msg); // 派发消息，到WindowPro函数处理
		//}
		while (TRUE)
		{
			if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					// 一定要加上，不然关闭按钮按下后，游戏还在进程了
					break;
				}
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
			/*else
			{
				::Sleep(10);
			}*/
			/*HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(m_hWnd, &ps);
			HXWindow::pInstance->OnPaint(hdc);
			EndPaint(m_hWnd, &ps);*/
			// UpdateMyWnd(m_hWnd);
		}
	}

	void HXWindow::SetPaintListener(HXPaintListener* pHXPaintListener)
	{
		m_pPaintListener = pHXPaintListener;
	}

	void HXWindow::AddInputListener(HXInputListener* pHXInputListener)
	{
		m_vec_pInputListener.push_back(pHXInputListener);
	}

	void HXWindow::RemoveInputListener(HXInputListener* pHXInputListener)
	{
		for (InputItr itr = m_vec_pInputListener.begin(); itr != m_vec_pInputListener.end();)
		{
			if (*itr == pHXInputListener)
			{
				m_vec_pInputListener.erase(itr++);
				return;
			}
			else
			{
				itr++;
			}
		}
	}

	void HXWindow::OnPaint(HDC hdc)
	{
		if (m_pPaintListener)
		{
			HXGraphics::GetInstance()->ClearBuffer();

			HXStatus::GetInstance()->ShowStatusInfo();
			m_pPaintListener->OnPaint();

			// 双缓冲技术防止闪烁
			HXGraphics::GetInstance()->SwapBuffer(hdc);
		}
	}

	void HXWindow::OnKeyDown(int msg)
	{
		for (InputItr itr = m_vec_pInputListener.begin(); itr != m_vec_pInputListener.end(); ++itr)
		{
			(*itr)->OnKeyDown(msg);
		}
	}

	void HXWindow::OnKeyUp(int msg)
	{
		for (InputItr itr = m_vec_pInputListener.begin(); itr != m_vec_pInputListener.end(); ++itr)
		{
			(*itr)->OnKeyUp(msg);
		}
	}
}