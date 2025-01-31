#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"
#include "game_object.h"

struct Particle {
	glm::vec2	pos, vel;
	glm::vec4	col;
	float		life;

	Particle() : pos(0.0f), vel(0.0f), col(1.0f), life(0.0f) { }
};

class ParticleGenerator {
	public:
		ParticleGenerator(Shader shader, Texture2D tex, unsigned int amount);

		void Update(float dt, GameObject &obj, unsigned int newPart, glm::vec2 offset=glm::vec2(0.0f, 0.0f));

		void Draw();

	private:
		std::vector<Particle> particles;
		unsigned int amount;
		Shader shader;
		Texture2D tex;
		unsigned int VAO;
		
		void init();

		unsigned int firstUnusedParticle();
		void respawnParticle(Particle &part, GameObject &obj, glm::vec2 offset=glm::vec2(0.0f, 0.0f));
};

#endif
