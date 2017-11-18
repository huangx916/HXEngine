#pragma once
#include "HXCommon.h"

namespace HX3D
{
	enum VAO_IDs
	{
		Triangles,
		NumVAOs
	};
	enum Buffer_IDs
	{
		ArrayBuffer,
		NumBuffers
	};

	enum Attrib_IDs
	{
		vPosition = 0,
		vColor = 1
	};

	class HXGLTest
	{
	public:
		HXGLTest();
		~HXGLTest();

		
		void CreateGLWindow(int argc, char* argv[]);

	private:
		void Init();
		static void Display();

		static unsigned int VAOs[NumVAOs];
		unsigned int Buffers[NumBuffers];
	};
}