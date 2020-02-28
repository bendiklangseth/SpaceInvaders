#include "GameManager.h"
#include "MenuItems.h"

MenuItems::MenuItems()
{
	
}

MenuItems::~MenuItems()
{
	TTF_Quit();
	SDL_DestroyTexture(text);
	TTF_CloseFont(font);
}

void MenuItems::drawItems()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), text, NULL, rect);
}

void MenuItems::init(const char* msg, int x, int y, int r, int g, int b, int size)
{
	SDL_Surface* surf;

	if (TTF_Init() < 0) {
		printf("ERROR: Could not load TTF, %s", TTF_GetError());
	}
	font = TTF_OpenFont("res/slkscr.ttf", size);
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = 255;

	if (!font) {
		printf("ERROR: Could not load font, %s", TTF_GetError());
	}

	rect = new SDL_Rect();

	surf = TTF_RenderText_Solid(font, msg, color);
	text = SDL_CreateTextureFromSurface(GameManager::getInstance().getRenderer(), surf);
	rect->x = x;
	rect->y = y;
	rect->w = surf->w;
	rect->h = surf->h;
	SDL_FreeSurface(surf);
}

