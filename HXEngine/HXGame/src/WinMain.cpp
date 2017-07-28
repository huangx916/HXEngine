#include <Windows.h>
#include "HXWindow.h"
#include "HXGame.h"

// 入口函数
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR pszCmdLine,
	int nShowCmd)
{
	HXWindow::GetInstance()->StartWindow("HXWinClass", "HXWin", hInstance);

	HXGame* pGame = new HXGame;
	HXWindow::GetInstance()->SetPaintListener(pGame);
	HXWindow::GetInstance()->AddInputListener(pGame);

	//游戏主循环
	HXWindow::GetInstance()->StartLoop();

	//退出游戏
	HXWindow::GetInstance()->ShutDownWindow();
	
	return 0;
}