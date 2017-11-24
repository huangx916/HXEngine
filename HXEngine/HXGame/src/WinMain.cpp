#include <Windows.h>
#include "DiscardHXWindow.h"
#include "HXGame.h"
#include "HXRoot.h"

using namespace HX3D;
// 入口函数
//int WINAPI WinMain(
//	HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPSTR pszCmdLine,
//	int nShowCmd)
//{
//	HXWindow::GetInstance()->StartWindow("HXWinClass", "HXWin", hInstance);
//
//	HXGame* pGame = new HXGame;
//	HXWindow::GetInstance()->SetPaintListener(pGame);
//	HXWindow::GetInstance()->AddInputListener(pGame);
//
//	//游戏主循环
//	HXWindow::GetInstance()->StartLoop();
//
//	//退出游戏
//	HXWindow::GetInstance()->ShutDownWindow();
//	
//	return 0;
//}

// 入口函数
int main(int argc, char* argv[])
{
	////////////////////////////////////////////////////////////////////////////////
	//// 原GDI渲染
	//HINSTANCE hInstance = ::GetModuleHandle(NULL);

	//HXWindow::GetInstance()->StartWindow("HXWinClass", "HXWin", hInstance);

	//HXGame* pGame = new HXGame;
	//HXWindow::GetInstance()->SetPaintListener(pGame);
	//HXWindow::GetInstance()->AddInputListener(pGame);

	////游戏主循环
	//HXWindow::GetInstance()->StartLoop();

	////退出游戏
	//HXWindow::GetInstance()->ShutDownWindow();
	///////////////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////
	// OpenGL测试
	// HXWindow::GetInstance()->TestCreateGLWindow(argc, argv);
	//////////////////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////////////////////////////////////////
	/*enum ERenderSystem
	{
		RenderSystem_GDI,
		RenderSystem_GL,
		RenderSystem_D3D
	};*/
	HXRoot::GetInstance()->Initialize(RenderSystem_GL);
	HXRoot::GetInstance()->CreateRenderWindow("HXENGINE", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	HXGame* pGame = new HXGame;
	HXRoot::GetInstance()->SetDisplayListener(pGame);
	HXRoot::GetInstance()->MainLoop();
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}