#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "text_renderer.h"
#include "resource_manager.h"

TextRenderer::TextRenderer(unsigned int w, unsigned int h) {
	this->textShader = ResourceManager::LoadShader("text", "shaders/text_2d.vs", "shaders/text_2d.fs", nullptr).Use();
	this->textShader.setMat4("proj", glm::ortho(0.0f, static_cast<float>(w), static_cast<float>(h), 0.0f), true);
	this->textShader.setInt("text", 0);

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void TextRenderer::Load(std::string font, unsigned int fontSize) {
	this->Characters.clear();

	FT_Library ft;

	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	FT_Error error = FT_New_Face(ft, font.c_str(), 0, &face);
	if (error)
		std::cout << "ERROR::FREETYPE: Failed to load font: " << error << std::endl;

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
			continue;
		}
		unsigned int tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Char chara = {
			tex,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<unsigned int>(face->glyph->advance.x)
		};
		Characters.insert(std::pair<char, Char>(c, chara));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color) {
	this->textShader.Use();
	this->textShader.setVec3("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	std::string::const_iterator c;

	for (c = text.begin(); c != text.end(); c++) {
		Char ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		float vertices[6][4] = {
			{ xpos,		ypos + h,	0.0f, 1.0f },
			{ xpos + w,	ypos,		1.0f, 0.0f },
			{ xpos,		ypos,		0.0f, 0.0f },

			{ xpos,		ypos + h,	0.0f, 1.0f },
			{ xpos + w,	ypos + h,	1.0f, 1.0f },
			{ xpos + w,	ypos,		1.0f, 0.0f }
		};

		glBindTexture(GL_TEXTURE_2D, ch.texID);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scale;
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
