#include "Component.h"
#include "GameManager.h"
#include <iostream>

Component::Component(int height, int width, const char * path)
{
	_rect = new SDL_Rect();
	_rect->h = height;
	_rect->w = width;
	_rect->x = 0;
	_rect->y = 0; 
	loadTexture(path);
}

Component::Component(int xpos, int ypos, int height, int width, const char * path)
{
	_rect = new SDL_Rect();
	_rect->h = height;
	_rect->w = width; 
	_rect->x = xpos;
	_rect->y = ypos;
	loadTexture(path);
}

Component::~Component()
{
}

SDL_Rect * Component::getRect() const
{
	return _rect;
}

void Component::loadTexture(const char * path)
{
	SDL_Surface * loadedSurface;
	loadedSurface = IMG_Load(path);
	if (loadedSurface == nullptr)
	{
		std::cout << IMG_GetError() << std::endl;
		return;
	}
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

	if (_texture != nullptr)
	{
		//SDL_DestroyTexture(_texture);
		//std::cout << "Destroyed old texture" << std::endl;
	}

	_texture = SDL_CreateTextureFromSurface(GameManager::getInstance().getRenderer(), loadedSurface);

	SDL_FreeSurface(loadedSurface);

	if (_texture == nullptr)
	{
		std::cout << "Failed to reset the texture" << std::endl;
		return;
	}
}

void Component::render()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), _texture, nullptr, _rect);
}
