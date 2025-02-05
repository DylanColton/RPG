#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "game_object.h"

enum EntityState {
	IDLE,
	RUN_N,	RUN_E,	RUN_S,	RUN_W,
	WALK_N,	WALK_E,	WALK_S,	WALK_W
};

class Entity : public GameObject {
	public:
		Entity();
		virtual ~Entity();

		// This will have default behaviour for NPC entities, usually related to their lua script
		virtual void Move();

	private:
		EntityState	state = IDLE;
		std::string	charSheet;
		std::string script;
		unsigned int runMod = 5;
		unsigned int wlkMod = 10;
};

#endif
