#include "GameManager.h"
#include <iostream>
#include <fstream>

const char * BG_M_INTRO = "intro.ogg";
const char * mGB_MAIN = "main.ogg";

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int WINDOW_HEIGHT;
int WINDOW_WIDTH;

Uint32 _frameStart;
int _frameTime;


void GameManager::initialize()
{
	if (_gameIsRunning)
		return;

	_windowOpen = true;
	_soundIsOn = true;
	_gameHasRestarted = false;

	_score = 0;

	initalizeSDL();
	initializeComponents();
	begin();
	
}

void GameManager::exitGame()
{
	std::cout << "Exiting game" << std::endl;
	_gameIsRunning = false;
	_windowOpen = false;
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	Mix_FreeMusic(_bgn);
	Mix_FreeMusic(_mBgn);
	_mBgn = nullptr;
	_bgn = nullptr;
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}


SDL_Renderer * GameManager::getRenderer()
{
		return _renderer;
}

std::shared_ptr<Player> GameManager::getPlayer()
{
	return _player;
}

std::shared_ptr<Menu> GameManager::getMenu()
{
	return _menu;
}

std::shared_ptr<BlockManager> GameManager::getBlockManager()
{
	return _blockManager;
}

bool GameManager::isMenuOpen() const
{
	return _menuIsOpen;
}

bool GameManager::isGameRunning() const
{
	return _gameIsRunning;
}

bool GameManager::gameHasRestarted() const
{
	return _gameHasRestarted;
}

int GameManager::readHighscore()
{
	std::ifstream file;
	file.open("highscore.txt");
	char score[1000];
	file >> score;
	file.close();
	int ret = atoi(score);
	return ret;
}

int GameManager::getScore()
{
	return _score;
}

bool GameManager::newHighscore()
{
	int highscore = readHighscore();
	if (_score > highscore)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameManager::openMenu()
{
	Mix_HaltMusic();
	_gameIsRunning = false;
	_menuIsOpen = true;
}

void GameManager::openGame(bool reset)
{
	if (reset)
	{
		_blockManager->initialize();
		_botManager->reset();
		_player->reset();
		_score = 0;
	}

	_statsManager->init();
	_gameHasRestarted = true;
	_gameIsRunning = true;
	_menuIsOpen = false;
}

void GameManager::switchSound()
{
	_soundIsOn = !_soundIsOn;
}

int GameManager::getWindowHeight() const
{
	return WINDOW_HEIGHT;
}

int GameManager::getWindowWidth() const
{
	return WINDOW_WIDTH;
}

void GameManager::initalizeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << Mix_GetError() << std::endl;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		std::cout << "ERROR AUDIO: %s\n" << Mix_GetError() << std::endl;
	}

	_bgn = Mix_LoadMUS(BG_M_INTRO);
	_mBgn = Mix_LoadMUS(mGB_MAIN);

	if (_bgn == nullptr || _mBgn == nullptr)
	{
		std::cout << Mix_GetError() << std::endl;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "WARNING: Linear texture filtering not enabled" << std::endl;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << IMG_GetError() << std::endl;
	}

	WINDOW_HEIGHT = 1000;
	WINDOW_WIDTH = 1200;

	_window = SDL_CreateWindow("SDL WINDOW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (_window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	int *h;
	int *w;
	h = &WINDOW_HEIGHT;
	w = &WINDOW_WIDTH;
	SDL_GL_GetDrawableSize(_window, w, h);

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

	if (_renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
}

void GameManager::initializeComponents()
{
	_menu.reset(new Menu());
	_inputManager.reset(new InputManager());
	_statsManager.reset(new StatsManager());
	_botManager.reset(new BotManager());
	_blockManager.reset(new BlockManager());
	_player.reset(new Player(550, 900, 100, 100));
	//_statsManager->init();
	_menu->init();
	_botManager->initializeStandardBots();
	_botManager->animateStandardBots();
	_blockManager->initialize();
}

void GameManager::begin()
{
	_windowIsOpen = true;
	_gameIsRunning = false;
	_menuIsOpen = true;


	while (_windowIsOpen)
	{
		gameLoop();
		menuLoop();
	}
	exitGame();
}

void GameManager::gameLoop()
{
	int _framesCount = 0;

	if (_soundIsOn)
	{
		if (Mix_PlayMusic(_mBgn, -1) < 0)
		{
			std::cout << "CAN'T PLAY MUSIC?: %s\n" << Mix_GetError() << std::endl;
		}
	}

	while (_gameIsRunning)
	{
		_frameStart = SDL_GetTicks();

		_inputManager->handleInput();

		updateComponents();

		updateCollisions();

		SDL_RenderClear(_renderer);

		if (_framesCount >= 10)
		{
			_framesCount = 0;
			_botManager->animateStandardBots();
		}

		renderComponents();

		SDL_RenderPresent(_renderer);

		_frameTime = SDL_GetTicks() - _frameStart;

		if (_framesCount >= 10)
		{
			_framesCount = 0;
			_botManager->animateStandardBots();
		}

		_framesCount++;

		if (FRAME_DELAY > _frameTime)
		{
			SDL_Delay(FRAME_DELAY - _frameTime);
		}
		else if (FRAME_DELAY < _frameTime)
		{
			std::cout << "SLOW RENDERING" << std::endl;
		}

		if (!_player->isAlive())
		{
			SDL_Delay(1000);
			gameOver();
		}

		if (_gameHasRestarted)
			_gameHasRestarted = false;


	}
}

void GameManager::menuLoop()
{


	if (_soundIsOn)
	{
		if (Mix_PlayMusic(_bgn, -1) < 0)
		{
			std::cout << "CAN'T PLAY MUSIC?: %s\n" << Mix_GetError() << std::endl;
		}
	}

	while (_menuIsOpen)
	{
		SDL_RenderClear(_renderer);
		_inputManager->handleInput();
		_menu->update();
		_menu->render();
		SDL_RenderPresent(_renderer);
	}
}

void GameManager::gameOver()
{
	int highscore = readHighscore();
	std::cout << "highscore: " << highscore << std::endl;
	if (_score > highscore)
	{
		std::cout << "new highscore" << std::endl;
		updateHighscore(_score);
	}
	openMenu();
}


void GameManager::updateComponents()
{
	_botManager->update();
	_player->update();
	_statsManager->update();
}

void GameManager::renderComponents()
{
	_player->render();
	_botManager->renderBots();
	_blockManager->render();
	_statsManager->render();
}

void GameManager::updateCollisions()
{
	// Check if player hit standardbots
	for (auto &bullet : _player->getBullets())
	{
		for (auto &bot : _botManager->getBots())
		{
			if (SDL_HasIntersection(bullet->getRect(), bot->getRect()))
			{
				_botManager->deleteBot(bot);
				_player->deleteBullet(bullet);
				_score++;
				std::cout << "Score: " << _score << std::endl;
				return;
			}
		}
	}

	// Check if bots bullets hit player
	for (auto &bullet : _botManager->getBullets())
	{
		if (SDL_HasIntersection(bullet->getRect(), _player->getRect()))
		{
			_player->takeLife();
			_statsManager->removeHeart();
			_botManager->deleteBullet(bullet);
			std::cout << "Player lifes: " << _player->getLifes() << std::endl;
			return;
		}
	}

	// Check if bots hit player
	for (auto &bot : _botManager->getBots())
	{
		if (SDL_HasIntersection(bot->getRect(), _player->getRect()))
		{
			gameOver();
			return;
		}
	}

	// Check if bullets hit blocks
	for (auto &bullet : _botManager->getBullets())
	{
		for (auto &block : _blockManager->getBlocks())
		{
			if (SDL_HasIntersection(bullet->getRect(), block->getRect()))
			{
				_botManager->deleteBullet(bullet);
				_blockManager->hitBlock(block);
			}
		}
	}

	// Check if player hit blocks
	for (auto &bullet : _player->getBullets())
	{
		for (auto &block : _blockManager->getBlocks())
		{
			if (SDL_HasIntersection(bullet->getRect(), block->getRect()))
			{
				_player->deleteBullet(bullet);
				_blockManager->hitBlock(block);
			}
		}
	}
}

void GameManager::updateHighscore(int highscore)
{
	std::ofstream file;
	file.open("highscore.txt");
	file << highscore << std::endl;
	file.close();
}
