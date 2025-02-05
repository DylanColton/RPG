#include "game_object.h"

#include <iostream>
GameObject::GameObject() : pos(0.0f, 0.0f), size(1.0f, 1.0f), vel(0.0f), col(1.0f), rot(0.0f), spr() {
	this->coll[0] = false;
	this->coll[1] = false;
	this->coll[2] = false;
	this->coll[3] = false;

	this->port[0] = false;
	this->port[1] = false;
	this->port[2] = false;
	this->port[3] = false;
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D spr, glm::vec3 col, glm::vec2 vel) : pos(pos), size(size), vel(vel), col(col), rot(0.0f), spr(spr) {
	this->coll[0] = false;
	this->coll[1] = false;
	this->coll[2] = false;
	this->coll[3] = false;

	this->port[0] = false;
	this->port[1] = false;
	this->port[2] = false;
	this->port[3] = false;
}

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->spr, this->pos, this->size, this->rot, this->col);
}
