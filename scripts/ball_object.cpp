#include "ball_object.h"

BallObject::BallObject() : GameObject(), r(12.5f), stuck(true), sticky(false), PassThrough(false) {}

BallObject::BallObject(glm::vec2 pos, float r, glm::vec2 vel, Texture2D spr) : GameObject(pos, glm::vec2(r * 2.0f, r * 2.0f), spr, glm::vec3(1.0f), vel), r(r), stuck(true), sticky(false), PassThrough(false) {}

glm::vec2 BallObject::Move(float dt, unsigned int window_width) {
	if (!this->stuck) {
		this->pos += this->vel * dt;

		if (this->pos.x <= 0.0f) {
			this->vel.x *= -1;
			this->pos.x = 0.0f;
		} else if (this->pos.x + this->size.x >= window_width) {
			this->vel.x *= -1;
			this->pos.x = window_width - this->size.x;
		}

		if (this->pos.y <= 0.0f) {
			this->vel.y *= -1;
			this->pos.y = 0.0f;
		}
	}
	return this->pos;
}

void BallObject::Reset(glm::vec2 pos, glm::vec2 vel) {
	this->pos = pos;
	this->vel = vel;
	this->stuck = true;
}
