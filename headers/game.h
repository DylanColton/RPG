#ifndef GAME_H
#define GAME_H

#include <vector>
#include <tuple>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

enum GameState {
	TITLE,
	OVERWORLD,
	MENU,
	DIALOG
};

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

const float PLAYER_WLK(500.0f);
const float PLAYER_RUN(1000.0f);

class Game {
	public:
		GameState				State;
		bool					Keys[1024], KeysProcessed[1024];
		unsigned int 			W, H;
		std::vector<GameLevel>	Maps;
		unsigned int			map;

		Game(unsigned int w, unsigned int h);
		~Game();

		void Init();

		void ProcessInput(float dt);
		void Update(float dt);
		void Render();
		void DoCollisions();

		void ResetLevel();
		void ResetPlayer();

		void Clear();
};

#endif
