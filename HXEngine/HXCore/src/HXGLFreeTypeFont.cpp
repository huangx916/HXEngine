#include "..\include\HXGLFreeTypeFont.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "vmath.h"
#include "HXStatus.h"

namespace HX3D
{
	HXGLFreeTypeFont::HXGLFreeTypeFont()
	{
	}

	HXGLFreeTypeFont::~HXGLFreeTypeFont()
	{
	}

	void HXGLFreeTypeFont::Initialize(const char* fontFile, int fontSize)
	{
		_fontSize = fontSize;
		_xStart = 0;
		_yStart = 0;

		memset(_character, 0, sizeof(_character));
		FT_Init_FreeType(&_library);
		assert(_library != 0);

		FT_New_Face(_library, fontFile, 0, &_face);
		FT_Set_Char_Size(_face, fontSize << 6, fontSize << 6, 72, 72);
		assert(_face != 0);

		glGenVertexArrays(1, &_vaoId);
		glGenBuffers(1, &_vboId);
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "builtin\\fonts.vert" },
			{ GL_FRAGMENT_SHADER, "builtin\\fonts.frag" },
			{ GL_NONE, NULL }
		};
		_programId = LoadShaders(shaders);
		glGenTextures(1, &_textureId);
		//glGenSamplers(1, &_samplerId);
		/**
		*   使用这个纹理id,或者叫绑定(关联)
		*/
		glBindTexture(GL_TEXTURE_2D, _textureId);
		/**
		*   指定纹理的放大,缩小滤波，使用线性方式，即当图片放大的时候插值方式
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);



		glTexImage2D(
			GL_TEXTURE_2D,      //! 指定是二维图片
			0,                  //! 指定为第一级别，纹理可以做mipmap,即lod,离近的就采用级别大的，远则使用较小的纹理
			GL_ALPHA,           //! 纹理的使用的存储格式
			1024,
			1024,
			0,                  //! 是否的边
			GL_ALPHA,           //! 数据的格式，bmp中，windows,操作系统中存储的数据是bgr格式
			GL_UNSIGNED_BYTE,   //! 数据是8bit数据
			0
		);
	}

	void HXGLFreeTypeFont::BeginText()
	{
		glBindVertexArray(_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, _vboId);
		glUseProgram(_programId);

		//glClear(GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		//glFrontFace(GL_CCW);
		glFrontFace(GL_CW);
	}

	void HXGLFreeTypeFont::_DrawText(float x, float y, const wchar_t* text, const HXCOLOR& color)
	{
		float       texWidth = 1024;
		float       texHeight = 1024;
		float       xStart = x;
		float       yStart = y + 16;
		float       zStart = -1;
		unsigned    index = 0;
		unsigned    nSize = wcslen(text);
		float       fHeight = 0;

		typedef float   TextVertex[5];
		TextVertex* pVert = new TextVertex[nSize * 4];

		for (unsigned i = 0; i < nSize; ++i)
		{
			HXCharacter*  ch = GetCharacter(text[i]);

			int         h = ch->y1 - ch->y0;
			int         w = ch->x1 - ch->x0;
			float       offset = (float(h) - float(ch->offsetY));
			float       offsetX = float(ch->offsetX);

			/**
			*   第一个点
			*/
			pVert[index + 0][0] = xStart;
			pVert[index + 0][1] = yStart - h + offset;
			pVert[index + 0][2] = zStart;
			pVert[index + 0][3] = ch->x0 / texWidth;
			pVert[index + 0][4] = ch->y0 / texHeight;
			/**
			*   第二个点
			*/
			pVert[index + 1][0] = xStart + w;
			pVert[index + 1][1] = yStart - h + offset;
			pVert[index + 1][2] = zStart;
			pVert[index + 1][3] = ch->x1 / texWidth;
			pVert[index + 1][4] = ch->y0 / texHeight;

			/**
			*   第三个点
			*/
			pVert[index + 2][0] = xStart + w;
			pVert[index + 2][1] = yStart + offset;
			pVert[index + 2][2] = zStart;
			pVert[index + 2][3] = ch->x1 / texWidth;
			pVert[index + 2][4] = ch->y1 / texHeight;

			/**
			*   第四个点
			*/
			pVert[index + 3][0] = xStart;
			pVert[index + 3][1] = yStart + offset;
			pVert[index + 3][2] = zStart;
			pVert[index + 3][3] = ch->x0 / texWidth;
			pVert[index + 3][4] = ch->y1 / texHeight;

			index += 4;
			xStart += w + (ch->offsetX);
		}

		glBufferData(GL_ARRAY_BUFFER, index * sizeof(TextVertex), pVert, GL_STATIC_DRAW);

		delete[] pVert;

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)(0 + 3 * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(1);


		glUseProgram(_programId);

		GLint render_mvp_matrix_loc = glGetUniformLocation(_programId, "mvp_matrix");
		vmath::mat4 matModelView = vmath::mat4::identity();
		vmath::mat4 matProjection = vmath::Ortho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1, -1);
		glUniformMatrix4fv(render_mvp_matrix_loc, 1, GL_FALSE, matProjection * matModelView);

		GLint font_color_loc = glGetUniformLocation(_programId, "fontColor");
		vmath::vec3 fontColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
		glUniform3fv(font_color_loc, 1, fontColor);

		// for test 单个纹理采样器可以不添加一下代码
		GLint tex_uniform_loc = glGetUniformLocation(_programId, "tex");
		glUniform1i(tex_uniform_loc, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		GLint tex_uniform_loc2 = glGetUniformLocation(_programId, "tex2");
		glUniform1i(tex_uniform_loc2, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _textureId);
		
		glDrawArrays(GL_QUADS, 0, index);

		//HXStatus::GetInstance()->nDrawCall += 1;
	}

	void HXGLFreeTypeFont::EndText()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	HXCharacter* HXGLFreeTypeFont::GetCharacter(wchar_t ch)
	{
		if (_character[ch].x0 == 0 &&
			_character[ch].x0 == 0 &&
			_character[ch].x1 == 0 &&
			_character[ch].y1 == 0
			)
		{
			/**
			*   说明字符还没有绘制到纹理上，则进行绘制
			*/
			if (_xStart + _fontSize > 1024)
			{
				/**
				*   写满一行,从新开始
				*/
				_xStart = 0;
				/**
				*   y开始位置要增加
				*/
				_yStart += _fontSize;
			}

			FT_Load_Glyph(_face, FT_Get_Char_Index(_face, ch), FT_LOAD_DEFAULT);
			FT_Glyph glyph;
			FT_Get_Glyph(_face->glyph, &glyph);

			FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
			FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
			FT_Bitmap& bitmap = bitmap_glyph->bitmap;
			/**
			*   如果没有数据，则不写，直接过去
			*/
			if (bitmap.width == 0 || bitmap.rows == 0)
			{
				_xStart += _fontSize / 2;

				_character[ch].x0 = _xStart;
				_character[ch].y0 = _yStart;
				_character[ch].x1 = _xStart + bitmap.width;
				_character[ch].y1 = _yStart + bitmap.rows;
				_character[ch].offsetY = 0;
				_character[ch].offsetX = 0;

			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, _textureId);

				_character[ch].x0 = _xStart;
				_character[ch].y0 = _yStart;
				_character[ch].x1 = _xStart + bitmap.width;
				_character[ch].y1 = _yStart + bitmap.rows;

				_character[ch].offsetY = bitmap_glyph->top;
				_character[ch].offsetX = bitmap_glyph->left;

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					_xStart,
					_yStart,
					bitmap.width,
					bitmap.rows,
					GL_ALPHA,
					GL_UNSIGNED_BYTE,
					bitmap.buffer
				);
				_xStart += bitmap.width + 1;
			}


		}
		return  &_character[ch];
	}
}