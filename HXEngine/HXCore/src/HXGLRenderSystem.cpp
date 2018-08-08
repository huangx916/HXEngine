#include "..\include\HXGLRenderSystem.h"
#include "vgl.h"
#include "HXIDisplayListener.h"
#include "HXGLRenderable.h"
#include "HXGLCamera.h"
#include "HXGLFreeTypeFont.h"
#include "HXGLTransform.h"
#include "HXGLShadowMap.h"
#include "HXGLMaterial.h"
#include "HXLoadConfigScene.h"

namespace HX3D
{
	HXGLShadowMap* HXGLRenderSystem::mShadowMap = NULL;
	HXGLRenderSystem::HXGLRenderSystem():mFont(NULL)
	{
		
	}

	HXGLRenderSystem::~HXGLRenderSystem()
	{
		if (mFont)
		{
			delete mFont;
			mFont = NULL;
		}
		if (mShadowMap)
		{
			delete mShadowMap;
			mShadowMap = NULL;
		}
	}

	void HXGLRenderSystem::CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen)
	{
		int one = 1;
		char * name = "name";
		strName += "-GL";

//#ifdef _DEBUG
//		glutInitContextFlags(GLUT_DEBUG);
//#endif

		glutInitWindowSize(nWidth, nHeight);
		gCurScreenWidth = nWidth;
		gCurScreenHeight = nHeight;
		//gAspect = (float)gCurScreenHeight / (float)gCurScreenWidth;
		// glutInitWindowPosition(140, 140);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);	// 双缓存
		// glutInitContextVersion(4, 3);	// 使用后会宕 ?
		//glutInitContextProfile(GLUT_CORE_PROFILE);

		glutInit(&one, &name);

		glutCreateWindow(strName.c_str());
		//glutIconifyWindow();
		//glutSetIconTitle("icon.png");
		//glutSetWindowTitle("HXEngine");
		//HWND hwnd = GetActiveWindow();


		if (glewInit())
		{
			std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
			exit(EXIT_FAILURE);
		}

		Initialize();
	}

	void HXGLRenderSystem::MainLoop()
	{
		glutDisplayFunc(Display);
		glutReshapeFunc(Reshape);
		glutKeyboardFunc(Keyboard);
		glutMouseFunc(Mouse);
		glutMotionFunc(MouseMotion);

		glutMainLoop();
	}

	void HXGLRenderSystem::Display()
	{
		RenderScene();

		glutSwapBuffers();
		glutPostRedisplay();
	}

	void HXGLRenderSystem::Reshape(int nWidth, int nHeight)
	{
		glViewport(0, 0, nWidth, nHeight);
		HXRenderSystem::Reshape(nWidth, nHeight);
	}

	HXRenderable* HXGLRenderSystem::GenerateRenderable(HXSubMesh* pSubMesh)
	{
		HXRenderable* pRenderable = new HXGLRenderable();
		pRenderable->GenerateArguments(pSubMesh);
		return pRenderable;
	}


	void HXGLRenderSystem::RenderSingle(HXRenderable* pRenderable, bool shadow)
	{
		if (shadow && mShadowMap)
		{
			pRenderable->RenderShadowMap();
		}
		else
		{
			pRenderable->Render();
		}
	}

	HXICamera* HXGLRenderSystem::CreateCamera(const HXCameraInfo* cameraInfo)
	{
		HXICamera* pCam = new HXGLCamera();
		pCam->Initialize(cameraInfo->position, cameraInfo->rotation, cameraInfo->nearZ, cameraInfo->farZ);
		pCam->clearFlag = cameraInfo->clearFlag;
		pCam->background = cameraInfo->background;
		pCam->cullingMask = cameraInfo->cullingMask;
		pCam->projection = cameraInfo->projection;
		pCam->depth = cameraInfo->depth;
		return pCam;
	}

	void HXGLRenderSystem::BeginText()
	{
		if (mFont)
		{
			mFont->BeginText();
		}
	}

	void HXGLRenderSystem::_DrawText(float x, float y, std::string text, const HXCOLOR& color)
	{
		if (mFont)
		{
			std::wstring wstr = std::wstring(text.begin(), text.end());
			mFont->_DrawText(x, y, wstr.c_str(), color);
		}
	}

	void HXGLRenderSystem::EndText()
	{
		if (mFont)
		{
			mFont->EndText();
		}
	}

	HXITransform* HXGLRenderSystem::CreateTransform()
	{
		return new HXGLTransform();
	}

	HXMaterial* HXGLRenderSystem::CreateMaterial(HXMaterialInfo* info)
	{
		return new HXGLMaterial(info);
	}

	void HXGLRenderSystem::Initialize()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_MULTISAMPLE);
		// InitTriangle();
		mFont = new HXGLFreeTypeFont();
		mFont->Initialize("default.ttf", 16);
		mShadowMap = new HXGLShadowMap();
		mShadowMap->Initialize();
	}

	void HXGLRenderSystem::InitForEditor()
	{
		Initialize();
	}

	void HXGLRenderSystem::RenderScene()
	{
		//begin shadow
		if (mShadowMap && mShadowMap->IsEnable())
		{
			mShadowMap->PreRender();
			// TODO: draw
			if (m_pDisplayListener)
			{
				// TODO: gameobject和UI分离
				m_pDisplayListener->OnDisplay(true);
			}
			mShadowMap->PostRender();
		}
		//end shadow

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (m_pDisplayListener)
		{
			// TODO: gameobject和UI分离
			m_pDisplayListener->OnDisplay(false);
		}
	}
}
