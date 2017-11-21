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

	enum Program_IDs
	{
		TriangleProgram,
		NumPrograms
	};

	enum Attrib_IDs
	{
		vPosition = 0,
		vColor = 1
	};

	class HXFreeTypeFont;
	class HXIFreeTypeFont;
	class HXGLTest
	{
	public:
		HXGLTest();
		~HXGLTest();

		
		void CreateGLWindow(int argc, char* argv[]);

	private:
		void InitTriangle();
		void InitFont();
		static void Display();
		static void RenderTriangle();
		static void RenderFont();

		static unsigned int VAOs[NumVAOs];
		static unsigned int Buffers[NumBuffers];
		
		static int _nWidth;
		static int _nHeight;

		static HXIFreeTypeFont* font;
	public:
		static unsigned int Programs[NumPrograms];
	};
}