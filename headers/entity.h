#ifndef ENTITY_H
#define ENTITY_H

#include "game_object.h"

enum EntityState {
	IDLE,
	RUN_N,
	RUN_E,
	RUN_S,
	RUN_W,
	WALK_N,
	WALK_E,
	WALK_S,
	WALK_W
};

class Entity : GameObject {
	public:
		Entity();
		~Entity();

	private:
		const char*	charSheet;
		EntityState	state;
};

#endif
