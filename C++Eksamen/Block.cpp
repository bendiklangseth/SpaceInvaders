#include "Block.h"



Block::Block(int xpos, int ypos, int height, int width, const char * path) : Component(xpos, ypos, height, width, path)
{
	_life = 4;
}


Block::~Block()
{
}

void Block::takeLife()
{
	if (_life > 0)
		_life--;
}

int Block::getLife() const
{
	return _life;
}
