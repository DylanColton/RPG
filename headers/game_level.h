#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"

class GameLevel {
	public:
		std::vector<GameObject> Tiles;
		unsigned int			W, H;

		GameLevel() { }

		void Load(const char* file, unsigned int tileSize);
		void Draw(SpriteRenderer &renderer);
};

#endif
