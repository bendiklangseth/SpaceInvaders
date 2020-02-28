#include "Player.h"
#include "GameManager.h"
#include <iostream>

const char * PLAYER_IDLE_PNG_PATH = "assets/playerIdle.png";
const char * PLAYER_FLY_PNG_PATH  = "assets/playerMove.png";
const char * PLAYER_DEAD_PNG_PATH = "assets/playerCrash.png";
const char * SHOOT_SOUND	      = "shoot.wav";

const char * BULLET_PNG_PATH = "assets/playerShoot.png";

Player::Player(int xpos, int ypos, int height, int width)
{
	_lifes = 5;
	_moving = false;
	_switchedPng = false;
	_idle = new Component(xpos, ypos, height, width, PLAYER_IDLE_PNG_PATH);
	_flying = new Component(xpos, ypos, height, width, PLAYER_FLY_PNG_PATH);
	_current = _idle;
	soundEffect = Mix_LoadWAV(SHOOT_SOUND);
}

Player::~Player()
{
	Mix_FreeChunk(soundEffect);
	soundEffect = nullptr;
}

void Player::update()
{
	if (_switchedPng)
	{
		_switchedPng = false;
		_idle->loadTexture(PLAYER_IDLE_PNG_PATH);
		_flying->loadTexture(PLAYER_FLY_PNG_PATH);
	}
	if (_moving)
	{
		_current = _flying;
		_moving = false;
	}
	else
	{
		_current = _idle;
	}
	for (auto &bullet : _bullets)
	{
		bullet->update();
	}
}

void Player::render()
{
	_current->render();

	for (auto &bullet : _bullets)
	{
		bullet->render();
	}
}

void Player::reset()
{
	_lifes = 5;
	_moving = false;
	_switchedPng = false;
	_idle->loadTexture(PLAYER_IDLE_PNG_PATH);
	_flying->loadTexture(PLAYER_FLY_PNG_PATH);
	_current = _idle;
	_bullets.clear();
}

SDL_Rect * Player::getRect()
{
	return _current->getRect();
}

void Player::shoot()
{
	std::shared_ptr<Bullet> bullet(new Bullet((_current->getRect()->x + (_current->getRect()->w / 2)), _current->getRect()->y, 10, 5, 0, 10, BULLET_PNG_PATH));
	_bullets.push_back(std::move(bullet));
	Mix_PlayChannel(-1, soundEffect, 0);
}

bool Player::isAlive() const
{
	return getLifes() > 0;
}

void Player::takeLife()
{
	_current->loadTexture(PLAYER_DEAD_PNG_PATH);
	_switchedPng = true;
	_lifes--;
	if (_lifes <= 0)
	{
		_idle->loadTexture(PLAYER_IDLE_PNG_PATH);
		_flying->loadTexture(PLAYER_FLY_PNG_PATH);
		_current->loadTexture(PLAYER_DEAD_PNG_PATH);
	}
}

int Player::getLifes() const
{
	return _lifes;
}

void Player::deleteBullet(std::shared_ptr<Bullet> bullet)
{
	std::vector<std::shared_ptr<Bullet>>::iterator itr = std::find(_bullets.begin(), _bullets.end(), bullet);

	if (itr != _bullets.end())
	{
		_bullets.erase(itr);
	}
}

std::vector<std::shared_ptr<Bullet>> Player::getBullets()
{
	return _bullets;
}

void Player::moveRight(int velocity)
{
	if ((_current->getRect()->x + _current->getRect()->w) >= GameManager::getInstance().getWindowWidth())
		return;

	_moving = true;
	_idle->getRect()->x += velocity;
	_flying->getRect()->x += velocity;
}

void Player::moveLeft(int velocity)
{
	if (_current->getRect()->x < 0)
		return;

	_moving = true;
	_idle->getRect()->x -= velocity;
	_flying->getRect()->x -= velocity;
}


