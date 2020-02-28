#include "StandardBot.h"
#include "GameManager.h"
#include <iostream>


StandardBot::StandardBot(int xpos, int ypos, int height, int width, int direction, int velocity, const char * path) : Component(xpos, ypos, height, width, path)
{
	_direction = direction;
	_velocity = velocity;
}

StandardBot::~StandardBot()
{
}

void StandardBot::update()
{
	switch (_direction)
	{
	case 0:
		break;
	case 1:
		_rect->x -= _velocity;
		break;
	case 2:
		_rect->y += _velocity;
		break;
	case 3:
		_rect->x += _velocity;
		break;
	case 4:
		_rect->y -= _velocity;
	default:
		break;
	}
}

void StandardBot::render()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), _texture, nullptr, _rect);
}

void StandardBot::setDirection(int direction)
{
	_direction = direction;
}

void StandardBot::setVelocity(int velocity)
{
	_velocity = velocity;
}

void StandardBot::moveDown(int pixels)
{
	_rect->y += pixels;
}

