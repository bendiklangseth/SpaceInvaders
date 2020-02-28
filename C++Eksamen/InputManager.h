#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SDL.h"
#include <ctime>

class InputManager
{
public:
	InputManager();
	~InputManager();

	void handleInput();

private:
	SDL_Event _sdlEvent;
	Uint8 * _currentKeyStates;
	clock_t _timeStart;
	clock_t _timeStop;


};

#endif // !INPUT_MANAGER_H



