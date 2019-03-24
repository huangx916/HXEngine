#include "..\include\HXGLPreprocessHandler.h"
#include "HXGLERMap.h"
#include "HXGLConvolutionCubeMap.h"
#include "HXGLSpecularLDCubeMap.h"
#include "HXGLSpecularDFGTexture.h"

namespace HX3D
{
	HXGLPreprocessHandler::HXGLPreprocessHandler()
	{
		m_bPreprocess = true;
		m_pErmap = new HXGLERMap();
		m_ConvolutionCubeMap = new HXGLConvolutionCubeMap();
		m_SpecularLDCubeMap = new HXGLSpecularLDCubeMap();
		m_SpecularDFGTexture = new HXGLSpecularDFGTexture();
	}

	HXGLPreprocessHandler::~HXGLPreprocessHandler()
	{
		Release();
	}

	void HXGLPreprocessHandler::Preprocess(std::string strERMapFile)
	{
		if (m_bPreprocess && m_pErmap && m_ConvolutionCubeMap && m_SpecularLDCubeMap && m_SpecularDFGTexture)
		{
			m_pErmap->Preprocess(strERMapFile);
			m_ConvolutionCubeMap->Preprocess(m_pErmap->GetCubeMapTexture());
			m_SpecularLDCubeMap->Preprocess(m_pErmap->GetCubeMapTexture());
			m_SpecularDFGTexture->Preprocess();
			m_bPreprocess = false;
		}
	}

	void HXGLPreprocessHandler::Release()
	{
		HX_SAFE_DELETE(m_pErmap);
		HX_SAFE_DELETE(m_ConvolutionCubeMap);
		HX_SAFE_DELETE(m_SpecularLDCubeMap);
		HX_SAFE_DELETE(m_SpecularDFGTexture);
	}

	HXGLERMap* HXGLPreprocessHandler::GetErmap()
	{
		return m_pErmap;
	}

	HXGLConvolutionCubeMap* HXGLPreprocessHandler::GetConvolutionCubeMap()
	{
		return m_ConvolutionCubeMap;
	}

	HXGLSpecularLDCubeMap* HXGLPreprocessHandler::GetSpecularLDCubeMap()
	{
		return m_SpecularLDCubeMap;
	}

	HXGLSpecularDFGTexture* HXGLPreprocessHandler::GetSpecularDFGTexture()
	{
		return m_SpecularDFGTexture;
	}
}