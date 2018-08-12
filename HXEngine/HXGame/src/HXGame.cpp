#include "..\include\HXGame.h"
#include "HXVector.h"
#include "HXSceneManager.h"
#include "HXGameObject.h"
#include "HXMesh.h"
#include "HXICamera.h"
#include "HXRenderSystem.h"
#include "HXStatus.h"
#include "HXLoadConfigGameIni.h"

HXGame::HXGame()
{
	CreateGameScene();
}

HXGame::~HXGame()
{
}

void HXGame::CreateGameScene()
{
	HXLoadConfigGameIni cfg;
	cfg.LoadFile("game.ini");
	HXSceneManager::GetInstance()->LoadScene(cfg.strScene);
}

void HXGame::Update()
{
	
}

void HXGame::LateUpdate()
{

}

void HXGame::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	
}

void HXGame::OnKeyboard(unsigned char key, int x, int y)
{
	if (key == 'f' || key == 'F')
	{
		HXSceneManager::GetInstance()->UseFog(!HXSceneManager::GetInstance()->fog->useFog);
	}
	if (key == 's' || key == 'S')
	{
		HXStatus::GetInstance()->showStatus = !HXStatus::GetInstance()->showStatus;
	}
}

void HXGame::OnMouseMove(int nButton, int deltaX, int deltaY)
{
	if (HXSceneManager::GetInstance()->GetMainCamera() == NULL)
	{
		return;
	}
	if (nButton == 0)
	{
		// 左键按下状态
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D((deltaX) / 10.0f, -float(deltaY) / 10.0f, 0));
	}
	else if (nButton == 2)
	{
		// 右键按下状态
		//std::cout << "x = " << deltaX << ";     y = " << deltaY << std::endl;
		HXSceneManager::GetInstance()->GetMainCamera()->yaw(float(deltaX) / 10.0f);
		HXSceneManager::GetInstance()->GetMainCamera()->pitch(float(deltaY) / 10.0f);
	}
}

void HXGame::OnMouseWheel(float fDistance)
{
	if (HXSceneManager::GetInstance()->GetMainCamera() == NULL)
	{
		return;
	}
	HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D(0, 0, -fDistance));
}