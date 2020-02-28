#ifndef BULLET_H
#define BULLET_H

#include "Component.h"

class Bullet : public Component
{
public:
	Bullet(int xpos, int ypos, int height, int width, int xvel, int yvel, const char * path);
	~Bullet();

	void update();
	void render();

private:
	int _xVelocity;
	int _yVelocity;

};

#endif // !BULLET_H



