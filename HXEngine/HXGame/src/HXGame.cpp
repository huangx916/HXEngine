#include "..\include\HXGame.h"
#include "HXVector.h"
#include "HXSceneManager.h"
#include "HXCamera.h"
#include "HXGameObject.h"
#include "HXMesh.h"

HXGame::HXGame()
{
	CreateGameScene();
}


HXGame::~HXGame()
{
}

#include "HXGraphics.h"
//#include "HXMatrix.h"
//#include "HXVector.h"
//#include "HXCamera.h"
//#include "HXFrustum.h"
//#include "HXMath.h"
//#include "HXMesh.h"
//#include "HXCore.h"
//#include "HXGameObject.h"
#include "HXBitmap.h"
#include "hxtest.h"

HXBitmap* Gpbitmap = NULL;
void Test()
{
	//// for test begin
	//HXMatrix44 mat(1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4);
	//HXMatrix44 mat1 = mat.Transpose();
	//HXGraphics::GetInstance()->DrawLine(0, 0, 200, 100);
	//int i = 0;

	/*HXMatrix44 mat( 1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	1,2,3,1);
	HXMatrix44 mat1(1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	-1,-2,-3,1);
	HXMatrix44 mat2 = mat * mat1;
	HXMatrix44 mat3 = mat.Transpose();
	int i = 0;*/

	/*HXVector4D worldPos(0, 0, -10);
	HXCamera cam;
	cam.setPosition(HXVector4D(0, 0, -3));
	cam.setTargetPos(HXVector4D(0, 0, -4));
	cam.mFrustum->update();
	HXVector4D pos = GetVector4DMulMatrix44(worldPos, cam.mFrustum->matWorldToCamera);
	int i = 0;*/

	//Gpbitmap = new HXBitmap("terrain_texture.bmp");
	//Gpbitmap = new HXBitmap("terrain_texture.png");
	//Gpbitmap = new HXBitmap("icon.png");

	/*Gpbitmap = new HXBitmap();
	if (!Gpbitmap->LoadBitmapFile("icon.bmp"))
	{
		delete Gpbitmap;
		Gpbitmap = NULL;
	}*/

	
	//static const char* const vars[] = {"foo", "gl_SkipComponents2", "gl_SkipComponents3", "bar", "baz"};
	//unsigned int n = sizeof(vars);	// 20 指针总字节数
	//unsigned int n1 = sizeof(vars[0]);	// 4 单个指针字节数
	//unsigned int n2 = n / n1;	// 5 指针个数(数组大小)

	/*hxtest hx;
	hx.LoadFile("DogAnim.xml");*/

	//// for test end
}

void HXGame::CreateGameScene()
{
	HXGameObject* pGameObject = NULL;
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube", "Cube");
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube", "FBX\\cubeSubMesh.FBX");
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube", "cubeSubMesh.FBX");
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube", "cubeTexture.FBX");
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube1", "cubeTexture.FBX");
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube", "shaizi888.FBX");
	
	////pGameObject->SetScale(HXVector3D(0.05f, 0.05f, 0.05f));
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXTriangle", "Triangle");
	//pGameObject->SetPostion(HXVector3D(-4, 0, 0));
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXQuad", "Quad");
	//pGameObject->SetPostion(HXVector3D(4, 0, 0));
	////pGameObject->SetPostion(HXVector3D(0, -4, 0));
	
	//pGameObject->Roll(45.0f);

	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXQuad1", "Quad");
	//pGameObject->SetPostion(HXVector3D(0, 0, 10));
	//pGameObject->Pitch(45.0f);
	//pGameObject->Yaw(45.0f);
	//pGameObject->Roll(45.0f);
	//pGameObject->SetScale(HXVector3D(0.5f, 0.5f, 0.5f));

	// dog begin===========================================
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube", "cubeTexture.FBX");

	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXDog", "Dog.FBX");
	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXDog", "FBX\\Dog\\Dog@run.FBX");
	pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXDog", "FBX\\Dog\\Dog.FBX");
	pGameObject->GetMesh()->PlayAnimation("walk");
	pGameObject->Pitch(270.0f);
	pGameObject->Yaw(90.0f);
	pGameObject->SetPostion(HXVector3D(-4, -4, 0));

	pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXCube1", "cubeTexture.FBX");
	pGameObject->SetPostion(HXVector3D(0, 0, 0));

	pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXDog1", "FBX\\Dog\\Dog.FBX");
	pGameObject->GetMesh()->PlayAnimation("run", 2);
	pGameObject->Pitch(270.0f);
	pGameObject->Yaw(90.0f);
	pGameObject->SetPostion(HXVector3D(2, 2, 0));
	// dog end===========================================

	HXCamera* pMainCamera = HXSceneManager::GetInstance()->GetMainCamera();
	pMainCamera->setPosition(HXVector4D(0, 0, -10, 1));

	/*HXLight* pLight = HXSceneManager::GetInstance()->CreateLight(LIGHT_AMBIENT);
	pLight->color = HXCOLOR(255,255,255);*/

	HXLight* pLight = HXSceneManager::GetInstance()->CreateLight(LIGHT_DIRECTION);
	pLight->color = HXCOLOR(255, 255, 255);
	pLight->direct = HXVector3D(1, -1, 1);

	Test();
}

//void HXGame::OnUpdate()
//{
//
//}


void HXGame::OnPaint()
{
	// TODO: UI
	int nX = rand() % 800;
	//HXGraphics::GetInstance()->DrawLine(-10, -10, nX, 100, HXCOLOR(255, 0, 0));
	//HXGraphics::GetInstance()->DrawLine(200, 0, 0, 100);
	//HXGraphics::GetInstance()->DrawString("hello world", nX, 100, HXCOLOR(255, 0, 0), HXCOLOR(0,255,0));
	//HXGraphics::GetInstance()->DrawString("hello world", 0, 200);

	//for (int i = SCREEN_HEIGHT-200; i < SCREEN_HEIGHT; i++)
	//{
	//	for (int j = SCREEN_WIDTH-200; j < SCREEN_WIDTH; j++)
	//	{
	//		HXGraphics::GetInstance()->SetBufferPixel(j, i, 0, HXCOLOR(255, 0, 0));
	//	}
	//}

	/*if(Gpbitmap != NULL)
	{
		for(int i = 0; i < Gpbitmap->GetHeight(); i++)
		{ 
			for(int j = 0; j < Gpbitmap->GetWidth(); j++)
			{ 
				HXGraphics::GetInstance()->SetBufferPixel(j, i, 0, Gpbitmap->GetPixel(j,i));
			}
		}		
	}*/

	HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXCube");
	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXTriangle");
	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXQuad");
	if (pGameObject)
	{
		//pGameObject->Pitch(pGameObject->GetRotation().x + 1.0f);
		//pGameObject->Yaw(pGameObject->GetRotation().y + 1.0f);
		//pGameObject->Roll(pGameObject->GetRotation().z + 1.0f);
	}
	
	HXSceneManager::GetInstance()->Update();

}

void HXGame::OnKeyDown(int msg)
{
	HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXCube");
	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXTriangle");
	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXQuad");
	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXQuad1");
	if (pGameObject)
	{
		//pGameObject->Pitch(pGameObject->GetRotation().x + 1.0f);
		//pGameObject->Yaw(pGameObject->GetRotation().y + 1.0f);
		//pGameObject->Roll(pGameObject->GetRotation().z + 1.0f);
	}
	else
	{
		return;
	}

	if (msg == 'W')
	{
		pGameObject->Move(HXVector3D(0, 0.5f, 0));
	}
	else if (msg == 'S')
	{
		pGameObject->Move(HXVector3D(0, -0.5f, 0));
	}
	else if (msg == 'A')
	{
		pGameObject->Move(HXVector3D(-0.5f, 0, 0));
	}
	else if (msg == 'D')
	{
		pGameObject->Move(HXVector3D(0.5f, 0, 0));
	}
	else if (msg == 'Z')
	{
		pGameObject->Move(HXVector3D(0, 0, 0.5f));
	}
	else if (msg == 'X')
	{
		pGameObject->Move(HXVector3D(0, 0, -0.5f));
	}
	else if (msg == 'P')
	{
		pGameObject->Pitch(pGameObject->GetRotation().x + 1.0f);
	}
	else if (msg == 'Y')
	{
		pGameObject->Yaw(pGameObject->GetRotation().y + 1.0f);
	}
	else if (msg == 'R')
	{
		pGameObject->Roll(pGameObject->GetRotation().z + 1.0f);
	}
}

void HXGame::OnKeyUp(int msg)
{

}