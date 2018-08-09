#include "..\include\HXGDIRenderSystem.h"
#include<ctime>
#include "HXIDisplayListener.h"
#include "HXGraphics.h"
#include "HXGDIRenderable.h"
#include "HXGDICamera.h"
#include "HXGDITransform.h"
#include "HXGDIMaterial.h"
#include "HXLoadConfigScene.h"

namespace HX3D
{
	// 2、窗口过程函数
	LRESULT CALLBACK HXGDIRenderSystem::MyWindowProc(
		_In_ HWND   hwnd,
		_In_ UINT   uMsg,
		_In_ WPARAM wParam,
		_In_ LPARAM lParam
	)
	{
		if (NULL == m_pDisplayListener)
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		//判断消息ID
		switch (uMsg)
		{
		case WM_MOVING:
		case WM_PAINT:
		{
			/*HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd, &ps);
			HXWindow::pInstance->OnPaint(hdc);
			EndPaint(hwnd, &ps);*/
			break;
		}
		case WM_TIMER:
		{
			// 加上，不然画面不会刷新
			// HXWindow::pInstance->UpdateMyWnd(hwnd);
			break;
		}
		case WM_KEYDOWN:
		{
			// HXWindow::GetInstance()->OnKeyDown(wParam);
			/*if (m_pDisplayListener)
			{
				m_pDisplayListener->OnKeyboard(wParam, 0, 0);
			}*/
			Keyboard(wParam, 0, 0);
			break;
		}
		case WM_KEYUP:
		{
			// HXWindow::GetInstance()->OnKeyUp(wParam);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			/*if (m_pDisplayListener)
			{
				int x = (int)LOWORD(lParam);
				int y = (int)HIWORD(lParam);
				m_pDisplayListener->OnMouseMove(x, y);
			}*/
			mouseLDown = true;
			mLastX = (int)LOWORD(lParam);
			mLastY = (int)HIWORD(lParam);
			Mouse(0, 0, mLastX, mLastY);
			break;
		}
		case WM_LBUTTONUP:
		{
			mouseLDown = false;
			mLastX = (int)LOWORD(lParam);
			mLastY = (int)HIWORD(lParam);
			Mouse(0, 1, mLastX, mLastY);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			/*if (m_pDisplayListener)
			{
			int x = (int)LOWORD(lParam);
			int y = (int)HIWORD(lParam);
			m_pDisplayListener->OnMouseMove(x, y);
			}*/
			mouseRDown = true;
			mLastX = (int)LOWORD(lParam);
			mLastY = (int)HIWORD(lParam);
			Mouse(2, 0, mLastX, mLastY);
			break;
		}
		case WM_RBUTTONUP:
		{
			mouseRDown = false;
			mLastX = (int)LOWORD(lParam);
			mLastY = (int)HIWORD(lParam);
			Mouse(2, 1, mLastX, mLastY);
			break;
		}
		case WM_MOUSEMOVE:
		{
			if (mouseLDown || mouseRDown)
			{
				int x = (int)LOWORD(lParam);
				int y = (int)HIWORD(lParam);
				/*std::cout << "x = " << x << ";     y = " << y << std::endl;*/
				MouseMotion(x, y);
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			short zDelta = (short)HIWORD(wParam);
			if (zDelta < 0)
			{
				// 向后滚
				Mouse(4, 0, 0, 0);
			}
			else if (zDelta > 0)
			{
				// 向前滚
				Mouse(3, 0, 0, 0);
			}
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

	bool HXGDIRenderSystem::mouseLDown = false;
	bool HXGDIRenderSystem::mouseRDown = false;
	HXGDIRenderSystem::HXGDIRenderSystem()
	{
		HXGraphics::GetInstance()->InitGraphics();
	}

	HXGDIRenderSystem::~HXGDIRenderSystem()
	{
		HXGraphics::GetInstance()->ShutDownGraphics();
	}

	void HXGDIRenderSystem::CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen)
	{
		LPCTSTR lpClassName = "HXWinClass";
		strName += "-GDI";
		LPCTSTR lpWinName = strName.c_str();
		HINSTANCE hInstance = ::GetModuleHandle(NULL);
		RegisterMyWindow(lpClassName, hInstance);
		m_hWnd = CreateMyWindow(lpClassName, lpWinName, hInstance);
		DisplayMyWnd(m_hWnd);
	}

	void HXGDIRenderSystem::MainLoop()
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

			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(m_hWnd, &ps);
			// HXWindow::pInstance->OnPaint(hdc);
			Display(hdc);
			EndPaint(m_hWnd, &ps);
			UpdateMyWnd(m_hWnd);
		}
	}

	void HXGDIRenderSystem::Display(HDC hdc)
	{
		if (m_pDisplayListener)
		{
			HXGraphics::GetInstance()->ClearBuffer();

			// 仅用作相机和gameobject状态更新
			m_pDisplayListener->OnDisplay(true);

			m_pDisplayListener->OnDisplay(false);
			// HXStatus::GetInstance()->ShowStatusInfo();

			// 双缓冲技术防止闪烁
			HXGraphics::GetInstance()->SwapBuffer(hdc);
		}
	}

	void HXGDIRenderSystem::Reshape(int nWidth, int nHeight)
	{

	}

	HXRenderable* HXGDIRenderSystem::GenerateRenderable(HXSubMesh* pSubMesh)
	{
		HXRenderable* pRenderable = new HXGDIRenderable();
		pRenderable->GenerateArguments(pSubMesh);
		return pRenderable;
	}

	void HXGDIRenderSystem::RenderSingle(HXRenderable* pRenderable, bool shadow)
	{
		pRenderable->Render();
	}

	HXICamera* HXGDIRenderSystem::CreateCamera(const HXCameraInfo* cameraInfo)
	{
		HXICamera* pCam = new HXGDICamera();
		pCam->Initialize(cameraInfo->position, cameraInfo->rotation, cameraInfo->nearZ, cameraInfo->farZ);
		pCam->name = cameraInfo->name;
		pCam->clearFlag = cameraInfo->clearFlag;
		pCam->background = cameraInfo->background;
		pCam->cullingMask = cameraInfo->cullingMask;
		pCam->projection = cameraInfo->projection;
		pCam->depth = cameraInfo->depth;
		return pCam;
	}

	/*void HXGDIRenderSystem::BeginText()
	{

	}*/

	void HXGDIRenderSystem::_DrawText(float x, float y, std::string text, const HXCOLOR& color)
	{
		HXGraphics::GetInstance()->DrawString(text, x, y, color, HXCOLOR(128,128,128,255));
	}

	HXITransform* HXGDIRenderSystem::CreateTransform()
	{
		return new HXGDITransform();
	}

	HXMaterial* HXGDIRenderSystem::CreateMaterial(HXMaterialInfo* info)
	{
		return new HXGDIMaterial(info);
	}

	/*void HXGDIRenderSystem::EndText()
	{

	}*/

	// 3、注册窗口类型
	BOOL HXGDIRenderSystem::RegisterMyWindow(LPCSTR lpcWndName, HINSTANCE hInstance)
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
	HWND HXGDIRenderSystem::CreateMyWindow(LPCTSTR lpClassName, LPCTSTR lpWinName, HINSTANCE hInstance)
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

		// ::SetTimer(hWnd, WM_TIMER, 15, NULL);	// 每15毫秒传送一次WM_TIMER消息 

		// 手动播种
		srand((unsigned)time(NULL));

		return hWnd;
	}

	// 5、 显示窗口
	void HXGDIRenderSystem::DisplayMyWnd(HWND hWnd)
	{
		::ShowWindow(hWnd, SW_SHOW);
		::UpdateWindow(hWnd);
	}

	void HXGDIRenderSystem::UpdateMyWnd(HWND hWnd)
	{
		::InvalidateRect(hWnd, NULL, FALSE);	// 要求重新绘制
		::UpdateWindow(hWnd);
	}
}