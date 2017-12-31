#include "..\include\HXGame.h"
#include "HXVector.h"
#include "HXSceneManager.h"
#include "DiscardHXCamera.h"
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
//#include "HXGLTest.h"
#include "HXLoadConfigMat.h"
#include "HXLoadConfigPrefab.h"
#include "HXLoadConfigModel.h"
#include "HXLoadConfigScene.h"
#include "HXQuaternion.h"

HXBitmap* Gpbitmap = NULL;
//HXGLTest* pGLTest = NULL;
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
	hx.LoadFile("Dog.anim");*/

	/*HXLoadConfigMat cfg;
	cfg.LoadFile("./FBX/Dog/Dog.material");*/

	/*HXLoadConfigPrefab cfg;
	cfg.LoadFile("./FBX/Dog/Dog.prefab");*/

	/*HXLoadConfigScene cfg;
	cfg.LoadFile("./scene/DuKangCun.scene");*/

	/*pGLTest = new HXGLTest();
	pGLTest->InitTriangle();*/

	/*HXQuaternion q;
	q.FromAngleAxis(90, HXVector3D(0,1,0));
	HXVector3D P(1,0,1);
	HXVector3D destP = q.Transform(P);
	int nTest = 0;*/
	//// for test end
}

void HXGame::CreateGameScene()
{
	HXGameObject* pGameObject = NULL;

	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXQuad", "FBX\\Quad\\Quad.prefab");
	////pGameObject->Yaw(90.0f);
	////pGameObject->Roll(90.0f);
	////pGameObject->Pitch(90.0f);
	////pGameObject->SetPostion(HXVector3D(-4, -4, -10));
	//pGameObject->SetPostion(HXVector3D(0, 0, -300));
	//HXICamera* pMainCamera = HXSceneManager::GetInstance()->CreateMainCamera(HXVector3D(0, 0, 0), HXVector3D(0, 0, -1));

	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXTerrain", "FBX\\Terrain\\Terrain.prefab");
	//if (NULL == pGameObject)
	//{
	//	return;
	//}
	//pGameObject->Pitch(270.0f);
	////pGameObject->Roll(90.0f);
	////pGameObject->SetPostion(HXVector3D(-4, -4, -10));
	//pGameObject->SetPostion(HXVector3D(0, 0, -100));
	//HXICamera* pMainCamera = HXSceneManager::GetInstance()->CreateMainCamera(HXVector3D(0, 20, 0), HXVector3D(0, 0, -100));


	//pGameObject = HXSceneManager::GetInstance()->CreateGameObject("HXDog", "FBX\\Dog\\Dog.prefab");
	//if (NULL == pGameObject)
	//{
	//	return;
	//}
	//pGameObject->GetMesh()->PlayAnimation("walk");
	//pGameObject->Pitch(270.0f);
	//pGameObject->Roll(90.0f);
	////pGameObject->SetPostion(HXVector3D(-4, -4, -10));
	//pGameObject->SetPostion(HXVector3D(0, 0, -5));
	//HXICamera* pMainCamera = HXSceneManager::GetInstance()->CreateMainCamera(HXVector3D(0, 0, 0), HXVector3D(0, 0, -5));



	// TODO: 新建LoadScene(string strSceneCfg) 提取到 HXSceneManager里
	HXLoadConfigScene cfg;
	cfg.LoadFile("./scene/DuKangCun.scene");
	// fog 要放在HXPrefabGameObjInfo之前加载
	HXSceneManager::GetInstance()->CreateFog(&cfg.mSceneInfo.fogInfo);

	for (std::vector<HXPrefabGameObjInfo>::iterator itr = cfg.mSceneInfo.vctGameObjInfo.begin(); itr != cfg.mSceneInfo.vctGameObjInfo.end(); ++itr)
	{
		HXPrefabGameObjInfo& prefabgoinfo = *itr;
		HXGameObject* pFatherGameObject = HXSceneManager::GetInstance()->CreateGameObject(prefabgoinfo.strGameObjName, "", prefabgoinfo.nPriority);
		if (NULL == pFatherGameObject)
		{
			return;
		}
		if (pFatherGameObject->GetMesh())
		{
			pFatherGameObject->GetMesh()->PlayDefaultAnimation();
		}
		pFatherGameObject->SetScale(prefabgoinfo.scale);
		pFatherGameObject->SetRotation(prefabgoinfo.rotation);
		pFatherGameObject->SetPostion(prefabgoinfo.position);

		HXLoadConfigPrefab cfgPrefab;
		cfgPrefab.LoadFile(prefabgoinfo.strPrefabFile);
		for (std::vector<HXModelGameObjInfo>::iterator itr1 = cfgPrefab.mPrefabInfo.vctGameObjInfo.begin(); itr1 != cfgPrefab.mPrefabInfo.vctGameObjInfo.end(); ++itr1)
		{
			HXModelGameObjInfo& modelgoinfo = *itr1;
			pGameObject = HXSceneManager::GetInstance()->CreateGameObject(modelgoinfo.strGameObjName, modelgoinfo.strModelFile, prefabgoinfo.nPriority);
			if (NULL == pGameObject)
			{
				return;
			}
			if (pGameObject->GetMesh())
			{
				pGameObject->GetMesh()->PlayDefaultAnimation();
			}
			pGameObject->SetScale(modelgoinfo.scale);
			pGameObject->SetRotation(modelgoinfo.rotation);
			pGameObject->SetPostion(modelgoinfo.position);

			pGameObject->SetFather(pFatherGameObject);
		}
	}
	
	HXICamera* pMainCamera = HXSceneManager::GetInstance()->CreateMainCamera(HXVector3D(0, 5, 10), HXVector3D(0, 0, 0));
	// 创建天空盒
	HXSceneManager::GetInstance()->CreateSkyBox(HXVector3D(200,200,200));


	/*HXCamera* pMainCamera = HXSceneManager::GetInstance()->GetMainCamera();
	pMainCamera->setPosition(HXVector4D(0, 0, -10, 1));*/
	
	//HXICamera* pMainCamera = HXSceneManager::GetInstance()->CreateMainCamera(HXVector3D(0,0,0), HXVector3D(0,0,-1));

	/*HXLight* pLight = HXSceneManager::GetInstance()->CreateLight(LIGHT_AMBIENT);
	pLight->color = HXCOLOR(255,255,255);*/



	/*HXLight* pLight = HXSceneManager::GetInstance()->CreateLight(LIGHT_DIRECTION);
	pLight->color = HXCOLOR(255, 255, 255);
	pLight->direct = HXVector3D(1, -1, 1);*/

	Test();
}

//void HXGame::OnUpdate()
//{
//
//}


//void HXGame::OnPaint()
//{
//	// TODO: UI
//	int nX = rand() % 800;
//	//HXGraphics::GetInstance()->DrawLine(-10, -10, nX, 100, HXCOLOR(255, 0, 0));
//	//HXGraphics::GetInstance()->DrawLine(200, 0, 0, 100);
//	//HXGraphics::GetInstance()->DrawString("hello world", nX, 100, HXCOLOR(255, 0, 0), HXCOLOR(0,255,0));
//	//HXGraphics::GetInstance()->DrawString("hello world", 0, 200);
//
//	//for (int i = SCREEN_HEIGHT-200; i < SCREEN_HEIGHT; i++)
//	//{
//	//	for (int j = SCREEN_WIDTH-200; j < SCREEN_WIDTH; j++)
//	//	{
//	//		HXGraphics::GetInstance()->SetBufferPixel(j, i, 0, HXCOLOR(255, 0, 0));
//	//	}
//	//}
//
//	/*if(Gpbitmap != NULL)
//	{
//		for(int i = 0; i < Gpbitmap->GetHeight(); i++)
//		{ 
//			for(int j = 0; j < Gpbitmap->GetWidth(); j++)
//			{ 
//				HXGraphics::GetInstance()->SetBufferPixel(j, i, 0, Gpbitmap->GetPixel(j,i));
//			}
//		}		
//	}*/
//
//	/*if (pGLTest != NULL)
//	{
//		pGLTest->Display();
//	}*/
//
//	HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXCube");
//	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXTriangle");
//	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXQuad");
//	if (pGameObject)
//	{
//		//pGameObject->Pitch(pGameObject->GetRotation().x + 1.0f);
//		//pGameObject->Yaw(pGameObject->GetRotation().y + 1.0f);
//		//pGameObject->Roll(pGameObject->GetRotation().z + 1.0f);
//	}
//	
//	////HXSceneManager::GetInstance()->Update();
//
//}

void HXGame::OnDisplay()
{
	HXSceneManager::GetInstance()->OnDisplay();
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
		HXSceneManager::GetInstance()->GetMainCamera()->MoveHorizon(float(deltaX) / 10.0f);
		HXSceneManager::GetInstance()->GetMainCamera()->MoveVertical(float(deltaY) / 10.0f);
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
	HXSceneManager::GetInstance()->GetMainCamera()->Forward(fDistance);
}

//void HXGame::OnKeyDown(int msg)
//{
//	HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXCube");
//	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXTriangle");
//	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXQuad");
//	//HXGameObject* pGameObject = HXSceneManager::GetInstance()->GetGameObject("HXQuad1");
//	if (pGameObject)
//	{
//		//pGameObject->Pitch(pGameObject->GetRotation().x + 1.0f);
//		//pGameObject->Yaw(pGameObject->GetRotation().y + 1.0f);
//		//pGameObject->Roll(pGameObject->GetRotation().z + 1.0f);
//	}
//	else
//	{
//		return;
//	}
//
//	if (msg == 'W')
//	{
//		pGameObject->Move(HXVector3D(0, 0.5f, 0));
//	}
//	else if (msg == 'S')
//	{
//		pGameObject->Move(HXVector3D(0, -0.5f, 0));
//	}
//	else if (msg == 'A')
//	{
//		pGameObject->Move(HXVector3D(-0.5f, 0, 0));
//	}
//	else if (msg == 'D')
//	{
//		pGameObject->Move(HXVector3D(0.5f, 0, 0));
//	}
//	else if (msg == 'Z')
//	{
//		pGameObject->Move(HXVector3D(0, 0, 0.5f));
//	}
//	else if (msg == 'X')
//	{
//		pGameObject->Move(HXVector3D(0, 0, -0.5f));
//	}
//	else if (msg == 'P')
//	{
//		pGameObject->Pitch(pGameObject->GetRotation().x + 1.0f);
//	}
//	else if (msg == 'Y')
//	{
//		pGameObject->Yaw(pGameObject->GetRotation().y + 1.0f);
//	}
//	else if (msg == 'R')
//	{
//		pGameObject->Roll(pGameObject->GetRotation().z + 1.0f);
//	}
//}
//
//void HXGame::OnKeyUp(int msg)
//{
//
//}