#include "Bullet.h"
#include "GameManager.h"
#include <iostream>


Bullet::Bullet(int xpos, int ypos, int height, int width, int xvel, int yvel, const char * path) : Component(xpos, ypos, height, width, path)
{
	_xVelocity = xvel;
	_yVelocity = yvel;
}


Bullet::~Bullet()
{
}

void Bullet::update()
{
	_rect->x -= _xVelocity;
	_rect->y -= _yVelocity;
}

void Bullet::render()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), _texture, nullptr, _rect);
}
