#include "Menu.h"
#include "GameManager.h"
#include <iostream>

const char *IMG_CURSOR = "assets/cursor.png";

MenuItems *m1 = new MenuItems();
MenuItems *m2 = new MenuItems();
MenuItems *m3 = new MenuItems();
MenuItems *m4 = new MenuItems();



Menu::Menu()
{
	// Initialize menu and add items, images ++
	TTF_Init();
	cursorPos = 1;
	_timeStop = clock();
	_timeStart = clock();
}


Menu::~Menu()
{
	TTF_CloseFont(font2);
}

void Menu::update()
{
	c->getRect()->x = menuPos[cursorPos][0];
	c->getRect()->y = menuPos[cursorPos][1];
}

void Menu::render()
{
	_timeStart = clock();

	if (_timeStart - _timeStop > 250) {
		if (titleBox == title1) {

			titleBox = title2;
			_timeStop = clock();
		}

		else {
			titleBox = title1;
			_timeStop = clock();
		}
	}

	if (_pause) {
		m2->drawItems();
	}

	titleBox->render();

	m1->drawItems();
	m3->drawItems();
	m4->drawItems();
	c->render();
	cBox->render();
}

void Menu::moveUp()
{
	if (cursorPos <= 0) {
		cursorPos = 3;
	}

	else {
		cursorPos--;
	}
}

void Menu::moveDown()
{
	if (cursorPos >= 3) {
		cursorPos = 0;
	}
	else {
		cursorPos++;
	}
}

void Menu::click()
{
	if (cursorPos == 0) { //RESUME
		GameManager::getInstance().openGame(false);
		if (GameManager::getInstance().isGameRunning()) {
		}
	}
	else if (cursorPos == 1) { //NEW GAME
		GameManager::getInstance().openGame(true);
		if (GameManager::getInstance().isGameRunning()) {
			_pause = true;
		}
	}
	 else if (cursorPos == 2) { //SOUND
		if (cBox == speaker) {
			cBox = mute;
			Mix_PauseMusic();
		}
		else {
			Mix_ResumeMusic();
			cBox = speaker;
		}
	}
	else { //EXIT
		GameManager::getInstance().exitGame();
	}
}

void Menu::init()
{

	int w1;
	int h1;

	int w2;
	int h2;

	int w3;
	int h3;

	int w4;
	int h4;

	int winWidth = GameManager::getInstance().getWindowWidth();
	int winHeight = GameManager::getInstance().getWindowHeight();

	font2 = TTF_OpenFont("res/slkscr.ttf", 35);

	TTF_SizeText(font2, "New Game", &w1, &h1);
	TTF_SizeText(font2, "Resume", &w2, &h2);
	TTF_SizeText(font2, "Music", &w3, &h3);
	TTF_SizeText(font2, "Exit", &w4, &h4);

	int txtW1 = w1 / 2;
	int txtW2 = w2 / 2;
	int txtW3 = w3 / 2;
	int txtW4 = w4 / 2;

	title1 = new Component((winWidth / 2) - 300, winHeight * 0.2, 100, 600, "assets/logoWeak.png");
	title2 = new Component((winWidth / 2) - 300, winHeight * 0.2, 100, 600, "assets/logoStrong.png");

	m1->init("New Game", (winWidth * 0.5) - txtW1, winHeight * 0.5, 255, 255, 255, 35);
	m2->init("Resume", (winWidth * 0.5) - txtW2, winHeight * 0.45, 255, 255, 255, 35);
	m3->init("Music", (winWidth * 0.5) - txtW3, winHeight * 0.55, 255, 255, 255, 35);
	m4->init("Exit", (winWidth * 0.5) - txtW4, winHeight * 0.60, 255, 255, 255, 35);


	menuPos[0][0] = (winWidth / 2) - txtW2 - 25; //X verdi til Resume
	menuPos[0][1] = winHeight * 0.45 + 5;           // Y verdi til Resume
	menuPos[1][0] = (winWidth / 2) - txtW1 - 25; //X verdi til New game
	menuPos[1][1] = winHeight * 0.5 + 5;         //Y verdi til New game
	menuPos[2][0] = (winWidth / 2) - txtW3 - 25; //X verdi til sound
	menuPos[2][1] = winHeight * 0.55 + 5;      // Y verdi til sound
	menuPos[3][0] = (winWidth / 2) - txtW4 - 25; // X verdi til exit
	menuPos[3][1] = winHeight * 0.60 + 5;   // Y verdi til exit

	c	    = new Component(menuPos[1][0], menuPos[1][1], 25, 25, "assets/greenC.png");
	speaker = new Component(menuPos[2][0] + 145, menuPos[2][1] - 2, 25, 25, "assets/speaker.png");
	mute	= new Component(menuPos[2][0] + 145, menuPos[2][1] - 2, 25, 25, "assets/muteSpeaker.png");

	cBox = speaker;
	titleBox = title1;
}
