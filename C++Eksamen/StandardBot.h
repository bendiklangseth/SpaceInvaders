#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include "Component.h"
#include "Bullet.h"
#include <vector>
#include <memory>

class StandardBot : public Component
{
public:
	StandardBot(int xpos, int ypos, int height, int width, int direction, int velocity, const char * path);
	~StandardBot();

	void update();
	void render();

	void setDirection(int direction);
	void setVelocity(int velocity);
	void moveDown(int pixels);

private:
	int _direction;
	int _velocity;
	

};

#endif // !STANDARD_BOT_H



