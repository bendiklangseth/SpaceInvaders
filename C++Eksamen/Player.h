#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "Bullet.h"
#include <memory>
#include <vector>
#include <SDL_mixer.h>

// : public Component

class Player 
{
public:
	Player(int xpos, int ypos, int height, int width);
	~Player();

	void update();
	void render();

	void reset();

	SDL_Rect * getRect();
	void shoot();

	bool isAlive() const;
	void takeLife();
	int getLifes() const;

	void deleteBullet(std::shared_ptr<Bullet> bullet);
	std::vector<std::shared_ptr<Bullet>> getBullets();

	void moveRight(int velocity);
	void moveLeft(int velocity);

private:
	std::vector<std::shared_ptr<Bullet>> _bullets;
	int _lifes;
	bool _moving;
	bool _switchedPng;

	Component * _current;
	Component * _idle;
	Component * _flying;

	Mix_Chunk * soundEffect;
	

};

#endif // !PLAYER_H




