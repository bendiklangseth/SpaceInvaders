#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "SDL.h"
#undef main
#include "SDL_image.h"
#include "SDL_mixer.h"

#include "Menu.h"
#include "InputManager.h"
#include "BotManager.h"
#include "BlockManager.h"
#include "StatsManager.h"
#include "Player.h"
#include <memory>
#include <vector>

class GameManager
{
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	GameManager(GameManager const &) = delete;
	void operator = (GameManager const&) = delete;

	void initialize();
	void exitGame();

	SDL_Renderer * getRenderer();
	std::shared_ptr<Player> getPlayer();
	std::shared_ptr<Menu> getMenu();
	std::shared_ptr<BlockManager> getBlockManager();

	bool isMenuOpen() const;
	bool isGameRunning() const;

	bool gameHasRestarted() const;
	int readHighscore();
	int getScore();
	bool newHighscore();

	void openMenu();
	void openGame(bool reset);
	void switchSound();

	int getWindowHeight() const;
	int getWindowWidth() const;


private:
	GameManager() {}

	bool _windowIsOpen;
	bool _gameIsRunning;
	bool _windowOpen;
	bool _menuIsOpen;
	bool _soundIsOn;
	bool _gameHasRestarted;

	int _score;

	std::shared_ptr<Menu>			_menu;
	std::shared_ptr<InputManager>	_inputManager;
	std::shared_ptr<StatsManager>   _statsManager;
	std::shared_ptr<BotManager>		_botManager;
	std::shared_ptr<BlockManager>	_blockManager;
	std::shared_ptr<Player>			_player;

	SDL_Window * _window;
	SDL_Renderer * _renderer;
	Mix_Music * _bgn;
	Mix_Music * _mBgn;

	void initalizeSDL();
	void initializeComponents();
	void begin();

	void gameLoop();
	void menuLoop();

	void gameOver();

	void updateComponents();
	void renderComponents();

	void updateCollisions();

	void updateHighscore(int highscore);
};

#endif // !GAME_MANAGER_H



