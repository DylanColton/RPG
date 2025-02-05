#include <algorithm>
#include <sstream>
#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

#include "particle_generator.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "post_processor.h"
#include "text_renderer.h"
#include "sound_device.h"
#include "game_object.h"
#include "game.h"

ParticleGenerator*	ParticleGen;
SpriteRenderer*		renderer;
PostProcessor*		postproc;
TextRenderer*		Text;
GameObject*			Player;

float ShakeTime	= 0.0f;

Game::Game(unsigned int w, unsigned int h) : State(TITLE), Keys(), W(w), H(h) { }

Game::~Game() { }

void Game::Clear() {
	delete ParticleGen;
	delete renderer;
	delete postproc;
	delete Player;
	delete Text;
}

void Game::Init() {
	// Load Shaders
	ResourceManager::LoadShader("sprite", "sprite.vs", "sprite.fs", nullptr);
	ResourceManager::LoadShader("particle", "particle.vs", "particle.fs", nullptr);
	ResourceManager::LoadShader("postprocess", "post_process.vs", "post_process.fs", nullptr);

	// Configure Shaders
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(this->W), static_cast<float>(this->H), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().setInt("tex", 0);
	ResourceManager::GetShader("sprite").setMat4("proj", proj);

	// Load Textures
	ResourceManager::LoadTexture2D("wood", "wood.png", true);

	// Load Music

	// Load SFX

	// Set Rendering Controllers
	renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// Load Maps
	GameLevel lvl;
	lvl.Load("test_area.map", 50);
	this->Maps[lvl.name] = lvl;
	this->map = lvl.name;

	// Set up player
}

void Game::Update(float dt) {
}

void handleTitle() {
	std::cout << "In the Title" << std::endl;
}
void handleOverWorld() {
	std::cout << "In the Overworld" << std::endl;
}
void handleMenu() {
	std::cout << "In Menu" << std::endl;
}
void handleDialog() {
	std::cout << "In dialog" << std::endl;
}
void handleIllegal() {
	std::cout << "Illegal state" << std::endl;
	std::cout << "We get here when something incorrect happens" << std::endl
		<< "I suppose attempting to salvage the previous state would be appropriate" << std::endl
		<< "There should be some options to close the game, which will take a few seconds while cleanup occurs" << std::endl;
}
void Game::ProcessInput(float dt) {
	switch (this->State) {
		case TITLE:
			handleTitle();
			break;

		case OVERWORLD:
			handleOverWorld();
			break;

		case MENU:
			handleMenu();
			break;

		case DIALOG:
			handleDialog();
			break;

		default:
			handleIllegal();
			break;
	}

	/*
	if (this->State == GAME_MENU) {
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]) {
			this->State = GAME_ACTIVE;
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}
		if (this->Keys[GLFW_KEY_D] && !this->KeysProcessed[GLFW_KEY_D]) {
			this->KeysProcessed[GLFW_KEY_W] = true;
		}
		if (this->Keys[GLFW_KEY_A] && !this->KeysProcessed[GLFW_KEY_A]) {
			this->KeysProcessed[GLFW_KEY_S] = true;
		}
	}

	if (this->State == GAME_ACTIVE) {
		if (!Ball->stuck) {
			float vel = PLAYER_VELOCITY * dt;
			if (this->Keys[GLFW_KEY_A])
				if (Player->pos.x >= 0.0f)
					Player->pos.x -= vel;
			if (this->Keys[GLFW_KEY_D])
				if (Player->pos.x <= this->W - Player->size.x)
					Player->pos.x += vel;
		}

		if (this->Keys[GLFW_KEY_SPACE])
			Ball->stuck = false;
	}
	*/
}

void Game::Render() {
	this->Maps[this->map].Draw(*renderer);

	/*
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN) {
		// begin write of postproc buffer
		postproc->BeginRender();
			// Render the background
			renderer->DrawSprite(ResourceManager::GetTexture2D("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->W, this->H), 0.0f);
			// Render out the level
			this->Levels[this->Level].Draw(*renderer);
			// Render the player overtop
			Player->Draw(*renderer);
			// Draw Powerups
			for (PowerUp &powerUp : this->PowerUps)
				if (!powerUp.destroyed)
					powerUp.Draw(*renderer);
			// draw particles
			if (!Ball->stuck)
				ParticleGen->Draw();
			// Draw the ball
			Ball->Draw(*renderer);
		// end write of postproc buffer
		postproc->EndRender();

		// If anything should be post processed, now we mess up the screen
		postproc->Render(glfwGetTime());
	}

	if (this->State == GAME_MENU) {
		Text->RenderText("Press ENTER to start", 250.0f, this->H / 2.0f, 1.0f);
		Text->RenderText("Press A or D to select Level", 245.0f, this->H / 2.0f + 20.0f, 0.75f);
	}
	*/
}

void Game::ResetLevel() {
}

void Game::ResetPlayer() {
}

// COLLISIONS
bool CheckCollision(GameObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions() {
}

bool CheckCollision(GameObject &one, GameObject &two) {
	bool collX = one.pos.x + one.size.x >= two.pos.x &&
		two.pos.x + two.size.x >= one.pos.x;
	bool collY = one.pos.y + one.size.y >= two.pos.y &&
		two.pos.y + two.size.y >= one.pos.y;

	return collX && collY;
}

Direction VectorDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2( 0.0f,  1.0f),
		glm::vec2( 1.0f,  0.0f),
		glm::vec2( 0.0f, -1.0f),
		glm::vec2(-1.0f,  0.0f)
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}
