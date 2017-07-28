#include "..\include\HXGame.h"
#include "HXGraphics.h"


HXGame::HXGame()
{
}


HXGame::~HXGame()
{
}

//void HXGame::OnUpdate()
//{
//
//}

void HXGame::OnPaint()
{
	HXGraphics::GetInstance()->DrawLine(0, 0, 200, 100, RGB(255, 0, 0));
	HXGraphics::GetInstance()->DrawString("hello world", 0, 100, RGB(255, 0, 0));
}