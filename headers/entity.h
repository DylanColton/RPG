#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <glm/glm.hpp>

#include "game_object.h"

enum EntityState {
	IDLE,
	RUN_N,	RUN_E,	RUN_S,	RUN_W,
	WLK_N,	WLK_E,	WLK_S,	WLK_W
};

class Entity : public GameObject {
	public:
		Entity();
		virtual ~Entity();

		// This will have default behaviour for NPC entities, usually related to their lua script
		virtual void setState(EntityState newState);
		virtual void Move();

	protected:
		EntityState		state = IDLE;
		std::string		charSheet;
		std::string		script;
		unsigned int	runMod = 10;
		unsigned int	wlkMod = 5;

	private:
};

#endif
