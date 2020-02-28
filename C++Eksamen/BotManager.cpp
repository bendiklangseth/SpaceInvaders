#include "BotManager.h"
#include "GameManager.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

const char * STANDARD_BOT_FLY_PATH = "assets/standarFly.png";
const char * STANDARD_BOT_IDLE_PATH = "assets/standarIdle.png";

const char * MEDIUM_BOT_FLY_PATH = "assets/mediumFly.png";
const char * MEDIUM_BOT_IDLE_PATH = "assets/mediumIdle.png";

const char * HARD_BOT_FLY_PATH = "assets/hardFly.png";
const char * HARD_BOT_IDLE_PATH = "assets/hardIdle.png";

const char * ELITE_BOT_FLY_PATH = "assets/eliteMove.png";
const char * ELITE_BOT_IDLE_PATH = "assets/eliteIdle.png";

const char * BULLETS_PNG_PATH = "assets/botShoot.png";
const char * BOT_SOUND = "jumpS.wav";

bool _switch = false;

BotManager::BotManager()
{
	srand(time(nullptr));
	_level = 1;
	_currentBots.clear();
	_idleBots.clear();
	_flyingBots.clear();
	_timeStart = clock();
	_timeStop = clock();
	botSound = Mix_LoadWAV(BOT_SOUND);
}


BotManager::~BotManager()
{
}

void BotManager::reset()
{
	_level = 1;
	initializeStandardBots();
}

void BotManager::initializeStandardBots()
{
	int _botStartX = 10;
	int _botStartY = 150;

	_bullets.clear();
	_idleBots.clear();
	_currentBots.clear();
	_flyingBots.clear();

	std::cout << "init" << std::endl;
	
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> idleBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, ELITE_BOT_IDLE_PATH));
		_idleBots.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, ELITE_BOT_FLY_PATH));
		_flyingBots.push_back(std::move(flyingBot));

		_botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			_botStartX = 10;
			_botStartY += 80;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> idleBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, HARD_BOT_IDLE_PATH));
		_idleBots.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, HARD_BOT_FLY_PATH));
		_flyingBots.push_back(std::move(flyingBot));

		_botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			_botStartX = 10;
			_botStartY += 80;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> idleBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, MEDIUM_BOT_IDLE_PATH));
		_idleBots.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, MEDIUM_BOT_FLY_PATH));
		_flyingBots.push_back(std::move(flyingBot));

		_botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			_botStartX = 10;
			_botStartY += 80;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> idleBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, STANDARD_BOT_IDLE_PATH));
		_idleBots.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(_botStartX, _botStartY, 60, 60, 3, _level, STANDARD_BOT_FLY_PATH));
		_flyingBots.push_back(std::move(flyingBot));

		_botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			_botStartX = 10;
			_botStartY += 80;
		}
	}
}

void BotManager::update()
{
	if (_currentBots.empty())
	{
		_timeStart = clock();
		if (_timeStart - _timeStop > 3000)
		{
			if (_level < 7)
			{
				_level++;
			}
			std::cout << "empty" << std::endl;
			initializeStandardBots();
			_timeStop = clock();
		}
	}
	for (auto &bot : _currentBots)
	{
		int r = rand() % 1000;
		if (r == 5)
		{
			std::unique_ptr<Bullet> bullet(new Bullet(bot->getRect()->x, bot->getRect()->y, 10, 5, 0, -3, BULLETS_PNG_PATH));
			_bullets.push_back(std::move(bullet));
		}

		if ( (bot->getRect()->x + bot->getRect()->w) >= GameManager::getInstance().getWindowWidth())
		{
			setBotsDirection(1);
			pushStandardBotsDown(25);
			Mix_PlayChannel(1, botSound, 0);
			break;
		}
		else if (bot->getRect()->x <= 0)
		{
			setBotsDirection(3);
			pushStandardBotsDown(25);
			Mix_PlayChannel(1, botSound, 0);
			break;
		}
	}
	for (auto &bot : _idleBots)
	{
		bot->update();
	}
	for (auto &bot : _flyingBots)
	{
		bot->update();
	}
}

void BotManager::renderBots()
{
	for (auto &bullet : _bullets)
	{
		bullet->update();
		bullet->render();
	}

	for (auto &bot : _currentBots)
	{
		bot->render();
	}
}

void BotManager::deleteBot(std::shared_ptr<StandardBot> bot)
{
	int c = 0;
	for (auto &x : _currentBots)
	{
		if (x == bot)
		{
			std::vector<std::shared_ptr<StandardBot>>::iterator currIndex = std::find(_currentBots.begin(), _currentBots.end(), _currentBots.at(c));
			std::vector<std::shared_ptr<StandardBot>>::iterator idleIndex = std::find(_idleBots.begin(), _idleBots.end(), _idleBots.at(c));
			std::vector<std::shared_ptr<StandardBot>>::iterator flyindIndex = std::find(_flyingBots.begin(), _flyingBots.end(), _flyingBots.at(c));

			if (currIndex != _currentBots.end())
			{
				_currentBots.erase(currIndex);
			}
			if (idleIndex != _idleBots.end())
			{
				_idleBots.erase(idleIndex);
			}
			if (flyindIndex != _flyingBots.end())
			{
				_flyingBots.erase(flyindIndex);
			}

			return;
		}
		c++;
	}
}

void BotManager::deleteBullet(std::shared_ptr<Bullet> bullet)
{
	int c = 0;
	for (auto &x : _bullets)
	{
		if (x == bullet)
		{
			std::vector<std::shared_ptr<Bullet>>::iterator index = std::find(_bullets.begin(), _bullets.end(), _bullets.at(c));

			if (index != _bullets.end())
			{
				_bullets.erase(index);
			}
			return;
		}
		c++;
	}
}

std::vector<std::shared_ptr<StandardBot>> BotManager::getBots() const
{
	return _currentBots;
}

std::vector<std::shared_ptr<Bullet>> BotManager::getBullets() const
{
	return _bullets;
}

void BotManager::animateStandardBots()
{
	if (_switch)
	{
		_currentBots = _idleBots;
	}
	else
	{
		_currentBots = _flyingBots;
	}
	_switch = !_switch;
}

void BotManager::setBotsDirection(int direction)
{
	for (auto &bot : _idleBots)
	{
		bot->setDirection(direction);
	}
	for (auto &bot : _flyingBots)
	{
		bot->setDirection(direction);
	}
}

void BotManager::pushStandardBotsDown(int pixels)
{
	for (auto &bot : _idleBots)
	{
		bot->moveDown(pixels);
	}
	for (auto &bot : _flyingBots)
	{
		bot->moveDown(pixels);
	}
}

