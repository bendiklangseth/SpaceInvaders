#include "InputManager.h"
#include "GameManager.h"
#include <iostream>

InputManager::InputManager()
{
	_timeStop = clock();
	_timeStart = clock();
}

InputManager::~InputManager()
{
}

void InputManager::handleInput()
{
	while (SDL_PollEvent(&_sdlEvent) != 0)
	{
		if (_sdlEvent.type == SDL_QUIT)
		{
			GameManager::getInstance().exitGame();
			return;
		}
	}

	_currentKeyStates = (Uint8*)SDL_GetKeyboardState(nullptr);
	int keyCount = sizeof(_currentKeyStates) / sizeof(*_currentKeyStates);

	if (GameManager::getInstance().isGameRunning())
	{
		if (_currentKeyStates[SDL_SCANCODE_ESCAPE])
		{
			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().openMenu();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_RIGHT] && _currentKeyStates[SDL_SCANCODE_SPACE])
		{
			GameManager::getInstance().getPlayer()->moveRight(4);

			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().getPlayer()->shoot();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_LEFT] && _currentKeyStates[SDL_SCANCODE_SPACE])
		{
			GameManager::getInstance().getPlayer()->moveLeft(4);

			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().getPlayer()->shoot();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_SPACE])
		{
			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().getPlayer()->shoot();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			GameManager::getInstance().getPlayer()->moveRight(4);
		}
		else if (_currentKeyStates[SDL_SCANCODE_LEFT])
		{
			GameManager::getInstance().getPlayer()->moveLeft(4);
		}
	}
	else
	{
		if (_currentKeyStates[SDL_SCANCODE_ESCAPE])
		{
			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().exitGame();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_RETURN])
		{
			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().getMenu()->click();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_UP] || _currentKeyStates[SDL_SCANCODE_LEFT])
		{
			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().getMenu()->moveUp();
				_timeStop = clock();
			}
		}
		else if (_currentKeyStates[SDL_SCANCODE_DOWN] || _currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			_timeStart = clock();
			if (_timeStart - _timeStop > 250)
			{
				GameManager::getInstance().getMenu()->moveDown();
				_timeStop = clock();
			}
		}
	}
	/*
	if (_currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		if (GameManager::getInstance().isGameRunning())
		{
			// Open menu
			GameManager::getInstance().exitGame();
		}
		else if (GameManager::getInstance().isMenuOpen())
		{
			GameManager::getInstance().exitGame();
		}
		//GameManager::getInstance().exitGame();
		//return;
	}
	else if (_currentKeyStates[SDL_SCANCODE_RIGHT] && _currentKeyStates[SDL_SCANCODE_SPACE])
	{
		GameManager::getInstance().getPlayer()->moveRight(4);

		_timeStart = clock();
		if (_timeStart - _timeStop > 250)
		{
			GameManager::getInstance().getPlayer()->shoot();
			_timeStop = clock();
		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_LEFT] && _currentKeyStates[SDL_SCANCODE_SPACE])
	{
		GameManager::getInstance().getPlayer()->moveLeft(4);

		_timeStart = clock();
		if (_timeStart - _timeStop > 250)
		{
			//std::cout << "SHOOT" << std::endl;
			GameManager::getInstance().getPlayer()->shoot();
			_timeStop = clock();
		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_SPACE])
	{
		_timeStart = clock();
		if (_timeStart - _timeStop > 250)
		{
			//std::cout << "SHOOT" << std::endl;
			GameManager::getInstance().getPlayer()->shoot();
			_timeStop = clock();
		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_RETURN])
	{
		if (GameManager::getInstance().isMenuOpen())
		{

		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_UP] || _currentKeyStates[SDL_SCANCODE_LEFT])
	{
		if (GameManager::getInstance().isMenuOpen())
		{
			// Move up in menu
		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_DOWN] || _currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		if (GameManager::getInstance().isMenuOpen())
		{
			// Move doen in menu
		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		if (GameManager::getInstance().isGameRunning())
		{
			GameManager::getInstance().getPlayer()->moveRight(4);
		}
	}
	else if (_currentKeyStates[SDL_SCANCODE_LEFT])
	{
		if (GameManager::getInstance().isGameRunning())
		{
			GameManager::getInstance().getPlayer()->moveLeft(4);
		}
	}
	*/
}
