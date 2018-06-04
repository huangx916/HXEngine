#pragma once
#include "HXCommon.h"

namespace HX3D
{
	class HXRenderSystem;
	class HXIDisplayListener;
	class HXRoot
	{
	public:
		static HXRoot* GetInstance()
		{
			if (NULL == m_pInstance)
			{
				m_pInstance = new HXRoot();
			}
			return m_pInstance;
		}

		~HXRoot();

		void Initialize(ERenderSystem rs);
		void CreateRenderWindow(std::string strName, int nWidth, int nHeight, bool bFullScreen);
		void SetDisplayListener(HXIDisplayListener* pDisplayListener);
		void MainLoop();

		HXRenderSystem* GetRenderSystem();
	private:
		HXRoot();
		static HXRoot* m_pInstance;
		HXRenderSystem* m_pRenderSystem;
	};
}