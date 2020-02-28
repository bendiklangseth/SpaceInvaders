
#ifndef MENU_ITEMS_H
#define MENU_ITEMS_H
#include <SDL_ttf.h>
class MenuItems
{
public:
	MenuItems();
	~MenuItems();

	void drawItems();
	void init(const char* msg,int x, int y, int r, int g, int b, int size);

private:

	SDL_Texture * text;
	SDL_Rect* rect;
	TTF_Font *font;
	
};
#endif // !MENU_ITEMS_H





