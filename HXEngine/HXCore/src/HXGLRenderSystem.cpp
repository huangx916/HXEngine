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
#include "HXSceneManager.h"
#include "HXGLRenderTarget.h"
#include "HXRoot.h"

namespace HX3D
{
	HXGLShadowMap* HXGLRenderSystem::mShadowMap = NULL;
	HXGLRenderSystem::HXGLRenderSystem():mFont(NULL), mDefaultRenderTarget(NULL)
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
		// 各camera preRender里设置
		//glViewport(0, 0, nWidth, nHeight);
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
		pCam->name = cameraInfo->name;
		pCam->enable = cameraInfo->enable;
		pCam->clearFlag = cameraInfo->clearFlag;
		pCam->background = cameraInfo->background;
		pCam->cullingMask = cameraInfo->cullingMask;
		pCam->projection = cameraInfo->projection;
		pCam->mField = cameraInfo->feild;
		pCam->mSize = cameraInfo->size;
		pCam->mViewportRectX = cameraInfo->viewportRectX;
		pCam->mViewportRectY = cameraInfo->viewportRectY;
		pCam->mViewportRectW = cameraInfo->viewportRectW;
		pCam->mViewportRectH = cameraInfo->viewportRectH;
		pCam->depth = cameraInfo->depth;
		pCam->Initialize(cameraInfo->position, cameraInfo->rotation, cameraInfo->nearZ, cameraInfo->farZ);
		return pCam;
	}

	void HXGLRenderSystem::BeginText()
	{
		if (mFont)
		{
			mFont->BeginText();
		}
	}

	void HXGLRenderSystem::_DrawText(float x, float y, std::string text, const HXColor& color)
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

	void HXGLRenderSystem::InitDefaultRenderTarget()
	{
		if (NULL == mDefaultRenderTarget)
		{
			mDefaultRenderTarget = new HXGLRenderTarget();
		}
	}

	HXRenderTarget* HXGLRenderSystem::GetDefaultRenderTarget()
	{
		return mDefaultRenderTarget;
	}

	HXRenderTarget* HXGLRenderSystem::CreateRenderTarget(int width, int height)
	{
		return new HXGLRenderTarget(width, height);
	}

	void HXGLRenderSystem::Initialize()
	{
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);  // For cubemap seamless filtering
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
		HXRoot::GetInstance()->GetRenderSystem()->InitDefaultRenderTarget();

		if (m_pDisplayListener)
		{
			m_pDisplayListener->Update();
			HXSceneManager::GetInstance()->OnDisplay();
			m_pDisplayListener->LateUpdate();
		}
	}
}
