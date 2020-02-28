#include "StatsManager.h"
#include "GameManager.h"
#include <iostream>

MenuItems *text1 = new MenuItems();
MenuItems *text2 = new MenuItems();
MenuItems *text3 = new MenuItems();

MenuItems *text4 = new MenuItems();

StatsManager::StatsManager()
{
	TTF_Init();
}


StatsManager::~StatsManager()
{
	TTF_Quit();
}

void StatsManager::init()
{
	font1 = TTF_OpenFont("res/slkscr.ttf", 24);

	int w1;
	int h1;

	int w2;
	int h2;

	int w3;
	int h3;

	int w4;
	int w5;

	score = GameManager::getInstance().getScore();

	printf("%d", score);
	int winWidth = GameManager::getInstance().getWindowWidth();
	int winHeight = GameManager::getInstance().getWindowHeight();

	TTF_SizeText(font1, "SCORE:", &w1, &h1);
	TTF_SizeText(font1, "HI-SCORE:", &w2, &h2);

	int txtW1 = w1 / 2;
	int txtW2 = w2 / 2;

	_hearts.empty();
	int hpos = 1150;
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Component> newHeart(new Component(hpos, 30, 50, 50, "assets/heart.png"));
		_hearts.push_back(std::move(newHeart));
		std::cout << "added heart" << std::endl;
		hpos -= 50;
	}

	int highscore = GameManager::getInstance().readHighscore();
	std::string hs = std::to_string(highscore);
	const char* currenths = hs.c_str();

	text1->init("SCORE:", 20, 40, 255, 255, 255, 24);
	text2->init("HI-SCORE:", (winWidth * 0.45) - txtW2, 40, 255, 255, 255, 24);
	text4->init(currenths, (winWidth * 0.57) - txtW2, 40, 255, 255, 255, 24);

	
}

void StatsManager::update()
{
	score = GameManager::getInstance().getScore();
	std::string sc = std::to_string(score);
	const char* currentScore = sc.c_str();
	text3->init(currentScore, 120, 40, 255, 255, 255, 24);
}

void StatsManager::render()
{
	text1->drawItems();
	text2->drawItems();
	text3->drawItems();
	text4->drawItems();
	for (auto &heart : _hearts)
	{
		heart->render();
	}
}

void StatsManager::removeHeart()
{
	_hearts.erase(_hearts.begin());
	std::cout <<  _hearts.size() << std::endl;
}
