#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXGLERMap;
	class HXGLConvolutionCubeMap;
	class HXGLPreprocessHandler
	{
	public:
		HXGLPreprocessHandler();
		~HXGLPreprocessHandler();

		void Preprocess(std::string strERMapFile);
		HXGLERMap* GetErmap();
		HXGLConvolutionCubeMap* GetConvolutionCubeMap();

		bool m_bPreprocess;
		HXGLERMap* m_pErmap;
		HXGLConvolutionCubeMap* m_ConvolutionCubeMap;
	};
}

