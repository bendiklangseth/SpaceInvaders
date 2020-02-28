#ifndef MENU_H
#define MENU_H
#include "SDL_mixer.h"
#include "MenuItems.h"
#include "SDL_ttf.h"
#include "Component.h"
#include <memory>
#include <ctime>

class Menu
{
public:
	Menu();
	~Menu();

	// Updates position and settings
	void update();
	// Render the menu
	void render();
	void moveUp();
	void moveDown();
	void click();
	void init();

private:
	bool _pause;
	

	int menuPos[4][2];
	int cursorPos;

	Mix_Music * _bgn;
	Component *c;
	Component *speaker;
	Component *mute;
	Component *cBox;

	Component *title1;
	Component *title2;
	Component *titleBox;

	
	TTF_Font *font2;

	clock_t _timeStart;
	clock_t _timeStop;

};


#endif // !#MENU_H



