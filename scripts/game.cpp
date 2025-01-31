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
#include "ball_object.h"
#include "game.h"

ParticleGenerator*	ParticleGen;
SpriteRenderer*		renderer;
PostProcessor*		postproc;
TextRenderer*		Text;
GameObject*			Player;
BallObject*			Ball;

float ShakeTime	= 0.0f;

Game::Game(unsigned int w, unsigned int h) : State(GAME_ACTIVE), Keys(), W(w), H(h) { }

Game::~Game() { }

void Game::Clear() {
	delete ParticleGen;
	delete renderer;
	delete postproc;
	delete Player;
	delete Text;
	delete Ball;
}

void Game::Init() {
	// Load Shaders
	ResourceManager::LoadShader("sprite", "shaders/sprite.vs", "shaders/sprite.fs", nullptr);
	ResourceManager::LoadShader("particle", "shaders/particle.vs", "shaders/particle.fs", nullptr);
	ResourceManager::LoadShader("postprocess", "shaders/post_process.vs", "shaders/post_process.fs", nullptr);

	// Configure Shaders
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(this->W), static_cast<float>(this->H), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().setInt("tex", 0);
	ResourceManager::GetShader("sprite").setMat4("proj", proj);
	ResourceManager::GetShader("particle").Use().setInt("sprite", 0);
	ResourceManager::GetShader("particle").setMat4("proj", proj);

	// Load Textures
	ResourceManager::LoadTexture2D("background",			"resources/textures/background.jpg",			false);
	ResourceManager::LoadTexture2D("face",					"resources/textures/awesomeface.png",			true);
	ResourceManager::LoadTexture2D("block",					"resources/textures/block.png",					false);
	ResourceManager::LoadTexture2D("block_solid",			"resources/textures/block_solid.png",			false);
	ResourceManager::LoadTexture2D("paddle",				"resources/textures/paddle.png",				true);
	ResourceManager::LoadTexture2D("particle",				"resources/textures/particle.png",				true);
	ResourceManager::LoadTexture2D("powerup_speed",			"resources/textures/powerup_speed.png",			true);
	ResourceManager::LoadTexture2D("powerup_sticky",		"resources/textures/powerup_sticky.png",		true);
	ResourceManager::LoadTexture2D("powerup_increase",		"resources/textures/powerup_increase.png",		true);
	ResourceManager::LoadTexture2D("powerup_confuse",		"resources/textures/powerup_confuse.png",		true);
	ResourceManager::LoadTexture2D("powerup_chaos",			"resources/textures/powerup_chaos.png",			true);
	ResourceManager::LoadTexture2D("powerup_passthrough",	"resources/textures/powerup_passthrough.png",	true);

	// Load Music
	ResourceManager::LoadMusic("breakout",	"resources/audio/breakout.ogg", 0.5f);

	// Load SFX
	ResourceManager::LoadSoundEffect("bleep",	"resources/audio/bleep.ogg",	0.7f);
	ResourceManager::LoadSoundEffect("solid",	"resources/audio/solid.wav",	0.7f);
	ResourceManager::LoadSoundEffect("powerup",	"resources/audio/powerup.wav",	0.7f);

	// Set Rendering Controllers
	renderer		= new SpriteRenderer(ResourceManager::GetShader("sprite"));
	ParticleGen		= new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture2D("particle"), 500);
	postproc		= new PostProcessor(ResourceManager::GetShader("postprocess"), this->W, this->H);
	Text			= new TextRenderer(this->W, this->H);

	Text->Load(std::string("resources/fonts/Antonio-Bold.ttf"), 24);

	// Load Level
	GameLevel one;		one.Load("levels/one.lvl", this->W, this->H / 2);
	GameLevel two;		two.Load("levels/two.lvl", this->W, this->H / 2);
	GameLevel three;	three.Load("levels/three.lvl", this->W, this->H / 2);
	GameLevel four;		four.Load("levels/four.lvl", this->W, this->H / 2);

	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2((this->W - PLAYER_SIZE.x) / 2.0f, this->H - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture2D("paddle"));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture2D("face"));
	Ball->PassThrough = false;

	ResourceManager::GetMusic("breakout").play(true);
}

void Game::Update(float dt) {
	Ball->Move(dt, this->W);

	this->DoCollisions();

	ParticleGen->Update(dt, *Ball, 2, glm::vec2(Ball->r / 2.0f));

	this->UpdatePowerUps(dt);

	if (ShakeTime > 0.0f) {
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			postproc->shake = false;
	}

	if (Ball->pos.y >= this->H) {
		if (--this->Lives == 0) {
			this->ResetLevel();
			this->State = GAME_MENU;
		}
		this->ResetPlayer();
	}

	if (this->State == GAME_ACTIVE && this->Levels[this->Level].isComplete()) {
		this->ResetLevel();
		this->ResetPlayer();
		postproc->chaos = true;
		this->State = GAME_WIN;
	}
}

void Game::ProcessInput(float dt) {
	if (this->State == GAME_MENU) {
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER]) {
			this->State = GAME_ACTIVE;
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
		}
		if (this->Keys[GLFW_KEY_D] && !this->KeysProcessed[GLFW_KEY_D]) {
			this->Level = (++this->Level) % 4;
			this->KeysProcessed[GLFW_KEY_W] = true;
		}
		if (this->Keys[GLFW_KEY_A] && !this->KeysProcessed[GLFW_KEY_A]) {
			if (this->Level > 0)
				--this->Level;
			else
				this->Level = 3;
			this->KeysProcessed[GLFW_KEY_S] = true;
		}
	}

	if (this->State == GAME_WIN) {
		if (this->Keys[GLFW_KEY_ENTER]) {
			this->KeysProcessed[GLFW_KEY_ENTER] = true;
			postproc->chaos = false;
			this->State = GAME_MENU;
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
}

void Game::Render() {
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

	if (this->State == GAME_WIN) {
		Text->RenderText("YOU WON!!!", 320.0f, this->H / 2.0f - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, this->H / 2.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	}
}

void Game::ResetLevel() {
	if (this->Level == 0)
		this->Levels[0].Load("levels/one.lvl", this->W, this->H / 2);
	if (this->Level == 1)
		this->Levels[1].Load("levels/two.lvl", this->W, this->H / 2);
	if (this->Level == 2)
		this->Levels[2].Load("levels/three.lvl", this->W, this->H / 2);
	if (this->Level == 3)
		this->Levels[3].Load("levels/four.lvl", this->W, this->H / 2);

	this->Lives = 3;
}

void Game::ResetPlayer() {
	for (PowerUp &powerup : this->PowerUps) {
		powerup.destroyed = true;
	}

	Player->size = PLAYER_SIZE;
	Player->pos = glm::vec2((this->W - PLAYER_SIZE.x) / 2.0f, this->H - PLAYER_SIZE.y);
	Ball->Reset(Player->pos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);

	postproc->chaos = postproc->confuse = false;
	Ball->PassThrough = Ball->sticky = false;
	Player->col = glm::vec3(1.0f);
	Ball->col = glm::vec3(1.0f);
}

// Poweups
bool IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type);
void Game::UpdatePowerUps(float dt) {
	for (PowerUp &powerUp : this->PowerUps) {
		powerUp.pos += powerUp.vel * dt;

		if (powerUp.Activated) {
			powerUp.Duration -= dt;
			if((powerUp.Duration -= dt) <= 0.0f) {
				powerUp.Activated = false;
				
				if (powerUp.Type == "sticky") {
					if (!IsOtherPowerUpActive(this->PowerUps, "sticky")) {
						Ball->sticky = true;
						Player->col = glm::vec3(1.0f);
					}
				} else if (powerUp.Type ==  "pass-through") {
					if (!IsOtherPowerUpActive(this->PowerUps, "pass-through")) {
						Ball->sticky = false;
						Player->col = glm::vec3(1.0f);
					}
				} else if (powerUp.Type == "confuse") {
					if (!IsOtherPowerUpActive(this->PowerUps, "confuse")) {
						postproc->confuse = false;
					}
				} else if (powerUp.Type == "chaos") {
					if (!IsOtherPowerUpActive(this->PowerUps, "chaos")) {
						postproc->chaos = false;
					}
				}
			}
		}
	}

	this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
		[](const PowerUp &powerUp) { return powerUp.destroyed && !powerUp.Activated; }
	), this->PowerUps.end());
}

bool ShouldSpawn(unsigned int chance) {
	unsigned int random = rand() % chance;
	return random == 0;
}
void Game::SpawnPowerUps(GameObject &block) {
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("speed",				glm::vec3(0.5f, 0.5f, 1.0f),	0.0f,	block.pos, ResourceManager::GetTexture2D("powerup_speed")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("sticky",				glm::vec3(0.5f, 0.5f, 1.0f),	20.0f,	block.pos, ResourceManager::GetTexture2D("powerup_sticky")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pass-through",		glm::vec3(0.5f, 0.5f, 1.0f),	10.0f,	block.pos, ResourceManager::GetTexture2D("powerup_passthrough")));
	if (ShouldSpawn(75))
		this->PowerUps.push_back(PowerUp("pad-size-increase",	glm::vec3(0.5f, 0.5f, 1.0f),	0.0f,	block.pos, ResourceManager::GetTexture2D("powerup_increase")));
	if (ShouldSpawn(15))
		this->PowerUps.push_back(PowerUp("confuse",				glm::vec3(0.5f, 0.5f, 1.0f),	15.0f,	block.pos, ResourceManager::GetTexture2D("powerup_confuse")));
	if (ShouldSpawn(15))
		this->PowerUps.push_back(PowerUp("chaos",				glm::vec3(0.5f, 0.5f, 1.0f),	15.0f,	block.pos, ResourceManager::GetTexture2D("powerup_chaos")));
}

void ActivatePowerUp(PowerUp &powerUp) {
	if (powerUp.Type == "speed") {
		Ball->vel *= 1.2;
	} else if (powerUp.Type == "sticky") {
		Ball->sticky = true;
		Player->col = glm::vec3(1.0f, 0.5f, 1.0f);
	} else if (powerUp.Type == "pass-through") {
		Ball->PassThrough = true;
		Ball->col = glm::vec3(1.0f, 0.5f, 0.5f);
	} else if (powerUp.Type == "pad-size-increase") {
		Player->size.x += 50;
	} else if (powerUp.Type == "confuse") {
		if (!postproc->chaos)
			postproc->confuse = true;
	} else if (powerUp.Type == "chaos") {
		if (!postproc->confuse)
			postproc->chaos = true;
	}
}

bool IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type) {
	for (const PowerUp &powerUp : powerUps)
		if (powerUp.Activated)
			if (powerUp.Type == type)
				return true;
	return false;
}


// COLLISIONS
bool CheckCollision(GameObject &one, GameObject &two);
Collision CheckCollision(BallObject &one, GameObject &two);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions() {
	for (GameObject &box : this->Levels[this->Level].Bricks) {
		if (!box.destroyed) {
			Collision coll = CheckCollision(*Ball, box);
			if (std::get<0>(coll)) {
				if (!box.solid) {
					box.destroyed = true;
					SpawnPowerUps(box);
					ResourceManager::GetSoundEffect("bleep").play();
				} else {
					ShakeTime		= 0.05f;
					postproc->shake	= true;
					ResourceManager::GetSoundEffect("solid").play();
				}

				Direction dir = std::get<1>(coll);
				glm::vec2 diff = std::get<2>(coll);

				if (!(Ball->PassThrough && !box.solid)) {
					if (dir == LEFT || dir == RIGHT) {
						Ball->vel.x *= -1;
						float penetrate = Ball->r - std::abs(diff.x);
						if (dir == LEFT)
							Ball->pos.x += penetrate;
						else
							Ball->pos.x -= penetrate;
					} else {
						Ball->vel.y *= -1;
						float penetrate = Ball->r - std::abs(diff.y);
						if (dir == DOWN)
							Ball->pos.y += penetrate;
						else
							Ball->pos.y -= penetrate;
					}
				}
			}
		}
	}

	for (PowerUp &powerUp : this->PowerUps) {
		if (!powerUp.destroyed) {
			if (powerUp.pos.y >= this->H)
				powerUp.destroyed = true;
			if (CheckCollision(*Player, powerUp)) {
				ActivatePowerUp(powerUp);
				powerUp.destroyed = true;
				powerUp.Activated = true;
				ResourceManager::GetSoundEffect("powerup").play();
			}
		}
	}

	Collision res = CheckCollision(*Ball, *Player);
	if (!Ball->stuck && std::get<0>(res)) {
		float centerBoard = Player->pos.x + Player->size.x / 2.0f;
		float distance = (Ball->pos.x + Ball->r) - centerBoard;
		float percent = distance / (Player->size.x / 2.0f);

		float strength = 2.0f;
		glm::vec2 oldVel = Ball->vel;
		Ball->vel.x = INITIAL_BALL_VELOCITY.x * percent * strength;
		Ball->vel = glm::normalize(Ball->vel) * glm::length(oldVel);
		Ball->vel.y = -1.0f * abs(Ball->vel.y);

		Ball->stuck = Ball->sticky;
		ResourceManager::GetSoundEffect("bleep").play();
	}
}

bool CheckCollision(GameObject &one, GameObject &two) {
	bool collX = one.pos.x + one.size.x >= two.pos.x &&
		two.pos.x + two.size.x >= one.pos.x;
	bool collY = one.pos.y + one.size.y >= two.pos.y &&
		two.pos.y + two.size.y >= one.pos.y;

	return collX && collY;
}

Collision CheckCollision(BallObject &one, GameObject &two) {
	glm::vec2 center(one.pos + one.r);

	glm::vec2 aabb_half_extents(two.size.x / 2.0f, two.size.y / 2.0f);
	glm::vec2 aabb_center(two.pos.x + aabb_half_extents.x, two.pos.y + aabb_half_extents.y);

	glm::vec2 diff = center - aabb_center;
	glm::vec2 clamped = glm::clamp(diff, -aabb_half_extents, aabb_half_extents);

	glm::vec2 closest = aabb_center + clamped;

	diff = closest - center;

	if (glm::length(diff) < one.r)
		return std::make_tuple(true, VectorDirection(diff), diff);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
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
