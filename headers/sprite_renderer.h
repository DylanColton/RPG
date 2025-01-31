#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer {
	public:
		SpriteRenderer(Shader &shader);
		~SpriteRenderer();

		void DrawSprite(Texture2D &tex, glm::vec2 pos, glm::vec2 size=glm::vec2(5.0f, 5.0f), float rotate=0.0f, glm::vec3 color=glm::vec3(1.0f));

	private:
		Shader		shader;
		unsigned int quadVAO;
		void initRenderData();
};

#endif
