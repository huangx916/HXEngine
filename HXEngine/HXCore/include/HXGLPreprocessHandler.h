#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXGLERMap;
	class HXGLConvolutionCubeMap;
	class HXGLSpecularLDCubeMap;
	class HXGLSpecularDFGTexture;
	class HXGLPreprocessHandler
	{
	public:
		HXGLPreprocessHandler();
		~HXGLPreprocessHandler();

		void Preprocess(std::string strERMapFile);
		void Release();
		HXGLERMap* GetErmap();
		HXGLConvolutionCubeMap* GetConvolutionCubeMap();
		HXGLSpecularLDCubeMap* GetSpecularLDCubeMap();
		HXGLSpecularDFGTexture* GetSpecularDFGTexture();

	private:
		bool m_bPreprocess;
		HXGLERMap* m_pErmap;
		HXGLConvolutionCubeMap* m_ConvolutionCubeMap;
		HXGLSpecularLDCubeMap* m_SpecularLDCubeMap;
		HXGLSpecularDFGTexture* m_SpecularDFGTexture;
	};
}

