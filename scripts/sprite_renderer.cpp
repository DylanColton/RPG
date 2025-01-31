#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader) {
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D &tex, glm::vec2 pos, glm::vec2 size, float rotate, glm::vec3 color) {
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(pos, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.Use().setMat4("model", model);

	this->shader.setVec3("sprCol", color);

	glActiveTexture(GL_TEXTURE0);
	tex.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
	unsigned int VBO;
	float verts[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
