#include "particle_generator.h"

ParticleGenerator::ParticleGenerator(Shader shader, Texture2D tex, unsigned int amount) : shader(shader), tex(tex), amount(amount) {
	this->init();
}

void ParticleGenerator::Update(float dt, GameObject &obj, unsigned int newParticles, glm::vec2 offset) {
	for (unsigned int i = 0; i < newParticles; i++) {
		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(this->particles[unusedParticle], obj ,offset);
	}

	for (unsigned int i = 0; i < this->amount; i++) {
		Particle &p = this->particles[i];
		p.life -= dt;
		if (p.life > 0.0f) {
			p.pos -= p.vel * dt;
			p.col.a -= dt * 2.5f;
		}
	}
}

void ParticleGenerator::Draw() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.Use();

	for (Particle part : this->particles) {
		if (part.life > 0.0f) {
			this->shader.setVec2("offset", part.pos);
			this->shader.setVec4("color", part.col);
			this->tex.Bind();

			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init() {
	unsigned int VBO;
	float particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	for (unsigned int i = 0; i < this->amount; i++)
		this->particles.push_back(Particle());
}

unsigned int lastUsedPart = 0;
unsigned int ParticleGenerator::firstUnusedParticle() {
	for (unsigned int i = lastUsedPart; i < this->amount; i++) {
		if (this->particles[i].life <= 0.0f) {
			lastUsedPart = i;
			return i;
		}
	}

	for (unsigned int i = 0; i < lastUsedPart; i++) {
		if(this->particles[i].life <= 0.0f) {
			lastUsedPart = i;
			return i;
		}
	}
	lastUsedPart = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle &part, GameObject &obj, glm::vec2 offset) {
	float random = ((rand() % 100) - 50) / 10.0f;
	float rColor = 0.5f + ((rand() % 100) / 100.0f);
	part.pos		= obj.pos + random + offset;
	part.col		= glm::vec4(rColor, rColor, rColor, 1.0f);
	part.life		= 1.0f;
	part.vel		= obj.vel * 0.1f;
}
