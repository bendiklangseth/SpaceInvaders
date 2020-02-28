#ifndef BLOCK_H
#define BLOCK_H

#include "Component.h"

class Block : public Component
{
public:
	Block(int xpos, int ypos, int height, int width, const char * path);
	~Block();

	void takeLife();
	int getLife() const;

private:
	int _life;
};


#endif // !BLOCK_H


