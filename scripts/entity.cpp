#include "entity.h"

Entity::Entity() : GameObject() {
	charSheet		= "NULL";
	state			= IDLE;
}

Entity::~Entity() { }
