#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"

class BallObject : public GameObject {
	public:
		float			r;
		unsigned int	brickVal;
		bool			stuck, sticky, PassThrough;

		BallObject();
		BallObject(glm::vec2 pos, float r, glm::vec2 vel, Texture2D spr);

		glm::vec2 Move(float dt, unsigned int window_width);

		void Reset(glm::vec2 pos, glm::vec2 vel);
};

#endif
