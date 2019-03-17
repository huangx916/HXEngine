#include "..\include\HXGLPreprocessHandler.h"
#include "HXGLERMap.h"
#include "HXGLConvolutionCubeMap.h"

namespace HX3D
{
	HXGLPreprocessHandler::HXGLPreprocessHandler()
	{
		m_bPreprocess = true;
		m_pErmap = new HXGLERMap();
		m_ConvolutionCubeMap = new HXGLConvolutionCubeMap();
	}

	HXGLPreprocessHandler::~HXGLPreprocessHandler()
	{
		HX_SAFE_DELETE(m_pErmap);
		HX_SAFE_DELETE(m_ConvolutionCubeMap);
	}

	void HXGLPreprocessHandler::Preprocess(std::string strERMapFile)
	{
		if (m_bPreprocess && m_pErmap && m_ConvolutionCubeMap)
		{
			m_pErmap->Preprocess(strERMapFile);
			m_ConvolutionCubeMap->Preprocess(m_pErmap->GetCubeMapTexture());
			m_bPreprocess = false;
		}
	}

	HXGLERMap* HXGLPreprocessHandler::GetErmap()
	{
		return m_pErmap;
	}

	HXGLConvolutionCubeMap* HXGLPreprocessHandler::GetConvolutionCubeMap()
	{
		return m_ConvolutionCubeMap;
	}
}