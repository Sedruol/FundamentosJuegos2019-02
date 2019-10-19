#include "Player.h"
#include <SDL\SDL.h>
//movi aqui

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(float _speed, glm::vec2 _position, InputManager * _inputManager)
{
	speed = _speed;
	position = _position;
	inputManager = _inputManager;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
}

void Player::update()
{
	if (inputManager->isKeyPressed(SDLK_w)) {
		position.y += speed;
	}
	if (inputManager->isKeyPressed(SDLK_s)) {
		position.y -= speed;
	}
	if (inputManager->isKeyPressed(SDLK_z)) {
		position.x -= speed;
	}
	if (inputManager->isKeyPressed(SDLK_x)) {
		position.x += speed;
	}
}
