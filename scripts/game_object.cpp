#include "game_object.h"

GameObject::GameObject() : pos(0.0f, 0.0f), size(1.0f, 1.0f), vel(0.0f), col(1.0f), rot(0.0f), spr(), solid(false), destroyed(false) {
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D spr, glm::vec3 col, glm::vec2 vel) : pos(pos), size(size), vel(vel), col(col), rot(0.0f), spr(spr), solid(false), destroyed(false) {
}

void GameObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->spr, this->pos, this->size, this->rot, this->col);
}
