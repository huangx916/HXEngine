#include "..\include\HXGame.h"
#include "HXVector.h"
#include "HXSceneManager.h"
#include "HXGameObject.h"
#include "HXMesh.h"
#include "HXICamera.h"
#include "HXRenderSystem.h"

HXGame::HXGame()
{
	CreateGameScene();
}

HXGame::~HXGame()
{
}

////HXGLTest* pGLTest = NULL;
//void Test()
//{
//	//// for test begin
//	/*pGLTest = new HXGLTest();
//	pGLTest->InitTriangle();*/
//
//	/*HXQuaternion q;
//	q.FromAngleAxis(90, HXVector3D(0,1,0));
//	HXVector3D P(1,0,1);
//	HXVector3D destP = q.Transform(P);
//	int nTest = 0;*/
//	//// for test end
//}

void HXGame::CreateGameScene()
{
	HXSceneManager::GetInstance()->LoadScene("./scene/DuKangCun.scene");
	//Test();
}

void HXGame::OnDisplay(bool shadow)
{
	HXSceneManager::GetInstance()->OnDisplay(shadow);
}

void HXGame::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	HXSceneManager::GetInstance()->GetMainCamera()->OnViewPortResize(nScreenWidth, nScreenHeight);
}

void HXGame::OnKeyboard(unsigned char key, int x, int y)
{
	/*if (key == 'w' || key == 'W')
	{
		HXSceneManager::GetInstance()->GetMainCamera()->Forward(1);
	}
	if (key == 's' || key == 'S')
	{
		HXSceneManager::GetInstance()->GetMainCamera()->Forward(-1);
	}
	if (key == 'a' || key == 'A')
	{
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(-1, 0, 0));
	}
	if (key == 'd' || key == 'D')
	{
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(1, 0, 0));
	}*/
	if (key == 'f' || key == 'F')
	{
		HXSceneManager::GetInstance()->UseFog(!HXSceneManager::GetInstance()->fog->useFog);
	}
}

void HXGame::OnMouseMove(int nButton, int deltaX, int deltaY)
{
	if (nButton == 0)
	{
		// 左键按下状态
		//HXSceneManager::GetInstance()->GetMainCamera()->MoveHorizon(float(deltaX) / 10.0f);
		//HXSceneManager::GetInstance()->GetMainCamera()->MoveVertical(float(deltaY) / 10.0f);
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D((deltaX) / 10.0f, 0, 0));
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(0, -float(deltaY) / 10.0f, 0));
	}
	else if (nButton == 2)
	{
		// 右键按下状态
		//std::cout << "x = " << deltaX << ";     y = " << deltaY << std::endl;
		HXSceneManager::GetInstance()->GetMainCamera()->yaw(float(deltaX) / 10.0f);
		//HXSceneManager::GetInstance()->GetMainCamera()->YawLockTarget(float(deltaX) / 5.0f);
		HXSceneManager::GetInstance()->GetMainCamera()->pitch(float(deltaY) / 10.0f);
		//HXSceneManager::GetInstance()->GetMainCamera()->PitchLockTarget(float(deltaY) / 5.0f);
	}
}

void HXGame::OnMouseWheel(float fDistance)
{
	//HXSceneManager::GetInstance()->GetMainCamera()->Forward(fDistance);
	HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(0, 0, -fDistance));
}