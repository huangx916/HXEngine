#include <Windows.h>
#include "HXGame.h"
#include "HXRoot.h"

using namespace HX3D;

// 入口函数
int main(int argc, char* argv[])
{
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
	return 0;
}