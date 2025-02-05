#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject {
	public:
		glm::vec2	pos, size, vel;
		glm::vec3	col;
		float		rot;
		bool		coll[4];
		bool		port[4];
		Texture2D	spr;

		GameObject();
		GameObject(glm::vec2 pos, glm::vec2 size, Texture2D spr, glm::vec3 col=glm::vec3(1.0f), glm::vec2 vel=glm::vec2(0.0f, 0.0f));

		virtual void Draw(SpriteRenderer &renderer);
};

#endif
