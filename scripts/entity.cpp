#include "entity.h"

Entity::Entity() : GameObject() {
	this->charSheet		= "NULL";
	this->script		= "NULL";
	this->state			= IDLE;
}

Entity::~Entity() { }

void Entity::Move() {
}

void Entity::setState(EntityState newState) {
}
