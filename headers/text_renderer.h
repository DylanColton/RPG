#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"

struct Char {
	unsigned int	texID;
	glm::ivec2		Size;
	glm::ivec2		Bearing;
	unsigned int	Advance;
};

class TextRenderer {
	public:
		std::map<char, Char>	Characters;
		Shader					textShader;

		TextRenderer(unsigned int w, unsigned int h);

		void Load(std::string font, unsigned int fontSize);

		void RenderText(std::string text, float x, float y, float scale, glm::vec3 color=glm::vec3(1.0f));

	private:
		unsigned int VAO, VBO;
};

#endif
