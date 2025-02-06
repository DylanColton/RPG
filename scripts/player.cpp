#include "player.h"

#include <iostream>

Player::Player() : Entity() {
}

Player::~Player() {
}

void Player::Move() {
	switch (this->state) {
		case IDLE:
			break;

		case RUN_N:
			this->pos.y -= this->runMod;
			break;

		case RUN_E:
			this->pos.x += this->runMod;
			break;

		case RUN_S:
			this->pos.y += this->runMod;
			break;

		case RUN_W:
			this->pos.x -= this->runMod;
			break;

		case WLK_N:
			this->pos.y -= this->wlkMod;
			break;

		case WLK_E:
			this->pos.x += this->wlkMod;
			break;

		case WLK_S:
			this->pos.y += this->wlkMod;
			break;

		case WLK_W:
			this->pos.x -= this->wlkMod;
			break;
	}
}

void Player::setState(EntityState newState) {
	this->state = newState;
}
