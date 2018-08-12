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

//#include "HXGLMaterial.h"
//void Test()
//{
//	HXGLMaterial* mat = new HXGLMaterial(NULL);
//	delete mat;
//}

void HXGame::CreateGameScene()
{
	HXLoadConfigGameIni cfg;
	cfg.LoadFile("game.ini");
	HXSceneManager::GetInstance()->LoadScene(cfg.strScene);
	//HXSceneManager::GetInstance()->LoadScene("./scene/DuKangCun.scene");
	//HXSceneManager::GetInstance()->LoadScene("./scene/Test.scene");
	//Test();
}

void HXGame::OnDisplay()
{
	HXSceneManager::GetInstance()->OnDisplay();
}

void HXGame::OnViewPortResize(int nScreenWidth, int nScreenHeight)
{
	/*if (HXSceneManager::GetInstance()->mainCamera)
	{
		HXSceneManager::GetInstance()->mainCamera->OnViewPortResize(nScreenWidth, nScreenHeight);
	}*/
	for (std::vector<HXICamera*>::iterator itr = HXSceneManager::GetInstance()->cameraVct.begin(); itr != HXSceneManager::GetInstance()->cameraVct.end(); ++itr)
	{
		(*itr)->OnViewPortResize(nScreenWidth, nScreenHeight);
	}
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
		// ×ó¼ü°´ÏÂ×´Ì¬
		HXSceneManager::GetInstance()->GetMainCamera()->move(HXVector3D((deltaX) / 10.0f, -float(deltaY) / 10.0f, 0));
	}
	else if (nButton == 2)
	{
		// ÓÒ¼ü°´ÏÂ×´Ì¬
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