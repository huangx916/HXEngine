#include "..\include\HXGame.h"
#include "HXGraphics.h"

#include "HXSceneManager.h"
#include "HXCamera.h"
#include "HXVector.h"

HXGame::HXGame()
{
	CreateGameScene();
}


HXGame::~HXGame()
{
}

void HXGame::CreateGameScene()
{
	HXSceneManager::GetInstance()->CreateGameObject("HXCube", "Cube");
	HXCamera* pMainCamera = HXSceneManager::GetInstance()->GetMainCamera();
	pMainCamera->setPosition(HXVector4D(0, 0, -10, 1));
}

//void HXGame::OnUpdate()
//{
//
//}

#include "HXMatrix.h"
#include "HXVector.h"
#include "HXCamera.h"
#include "HXFrustum.h"
#include "HXMath.h"
#include "HXMesh.h"
#include "HXCore.h"
#include "HXGameObject.h"

void TestUpdate()
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




	//HXSubMesh subMesh;
	//// 立方体
	//subMesh.vertexList.reserve(8);

	//HXVertex vertex0;
	//vertex0.pos = HXVector3D(-1,1,1);
	//subMesh.vertexList.push_back(vertex0);

	//HXVertex vertex1;
	//vertex1.pos = HXVector3D(1,1,1);
	//subMesh.vertexList.push_back(vertex1);

	//HXVertex vertex2;
	//vertex2.pos = HXVector3D(-1,1,-1);
	//subMesh.vertexList.push_back(vertex2);

	//HXVertex vertex3;
	//vertex3.pos = HXVector3D(1,1,-1);
	//subMesh.vertexList.push_back(vertex3);

	//HXVertex vertex4;
	//vertex4.pos = HXVector3D(-1,-1,1);
	//subMesh.vertexList.push_back(vertex4);

	//HXVertex vertex5;
	//vertex5.pos = HXVector3D(1,-1,1);
	//subMesh.vertexList.push_back(vertex5);

	//HXVertex vertex6;
	//vertex6.pos = HXVector3D(-1,-1,-1);
	//subMesh.vertexList.push_back(vertex6);

	//HXVertex vertex7;
	//vertex7.pos = HXVector3D(1,-1,-1);
	//subMesh.vertexList.push_back(vertex7);

	//// 上0,1,3	0,3,2	前2,3,7	2,7,6	右3,1,5	3,5,7	左0,2,6	0,6,4	后1,0,4	1,4,5	下6,7,5	6,5,4
	//subMesh.indexList.resize(36);
	//subMesh.indexList.push_back(0);
	//subMesh.indexList.push_back(1);
	//subMesh.indexList.push_back(3);

	//subMesh.indexList.push_back(0);
	//subMesh.indexList.push_back(3);
	//subMesh.indexList.push_back(2);

	//subMesh.indexList.push_back(2);
	//subMesh.indexList.push_back(3);
	//subMesh.indexList.push_back(7);

	//subMesh.indexList.push_back(2);
	//subMesh.indexList.push_back(7);
	//subMesh.indexList.push_back(6);

	//subMesh.indexList.push_back(3);
	//subMesh.indexList.push_back(1);
	//subMesh.indexList.push_back(5);

	//subMesh.indexList.push_back(3);
	//subMesh.indexList.push_back(5);
	//subMesh.indexList.push_back(7);

	//subMesh.indexList.push_back(0);
	//subMesh.indexList.push_back(2);
	//subMesh.indexList.push_back(6);

	//subMesh.indexList.push_back(0);
	//subMesh.indexList.push_back(6);
	//subMesh.indexList.push_back(4);

	//subMesh.indexList.push_back(1);
	//subMesh.indexList.push_back(0);
	//subMesh.indexList.push_back(4);

	//subMesh.indexList.push_back(1);
	//subMesh.indexList.push_back(4);
	//subMesh.indexList.push_back(5);

	//subMesh.indexList.push_back(6);
	//subMesh.indexList.push_back(7);
	//subMesh.indexList.push_back(5);

	//subMesh.indexList.push_back(6);
	//subMesh.indexList.push_back(5);
	//subMesh.indexList.push_back(4);

	//HXRenderList renderlist;
	//subMesh.Insert_To_RenderList(HXVector3D(0, 0, 0), HXVector3D(0, 0, 0), HXVector3D(1, 1, 1), &renderlist);

	//HXMesh mesh;
	//mesh.subMeshList.push_back(subMesh);

	//HXGameObject gameObj(&mesh);

	//HXCamera camera;

	//Local_To_World_RenderList(&gameObj, &renderlist);
	//World_To_Camera_RenderList(&renderlist, camera.mFrustum);
	//Camera_To_Project_RenderList(&renderlist, camera.mFrustum);
	//Project_To_ViewPort_RenderList(&renderlist, camera.mFrustum);
	//Draw_RenderList_Texture_Solid(&renderlist);


	//// for test end

}

void HXGame::OnPaint()
{
	// TODO: UI
	int nX = rand() % 800;
	HXGraphics::GetInstance()->DrawLine(-10, -10, nX, 100, HXCOLOR(255, 0, 0));
	HXGraphics::GetInstance()->DrawLine(200, 0, 0, 100);
	HXGraphics::GetInstance()->DrawString("hello world", nX, 100, HXCOLOR(255, 0, 0), HXCOLOR(0,255,0));
	HXGraphics::GetInstance()->DrawString("hello world", 0, 200);

	//for (int i = SCREEN_HEIGHT-200; i < SCREEN_HEIGHT; i++)
	//{
	//	for (int j = SCREEN_WIDTH-200; j < SCREEN_WIDTH; j++)
	//	{
	//		HXGraphics::GetInstance()->SetBufferPixel(j, i, HXCOLOR(255, 0, 0));
	//	}
	//}

	////TestUpdate();

	HXSceneManager::GetInstance()->Update();

}
