#include "BlockManager.h"
#include "GameManager.h"

const char * BLOCK_100_PNG_PATH = "assets/block_100.png";
const char * BLOCK_75_PNG_PATH = "assets/block_75.png";
const char * BLOCK_50_PNG_PATH = "assets/block_50.png";
const char * BLOCK_25_PNG_PATH = "assets/block_25.png";

const int blockPositions[][2] = 
{
	{100, 800}, 
	{300, 800}, 
	{500, 800 },
	{700, 800 },
	{900, 800 }
};

BlockManager::BlockManager()
{
}


BlockManager::~BlockManager()
{
}

void BlockManager::initialize()
{
	_blocks.clear();
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<Block> component(new Block(blockPositions[i][0], blockPositions[i][1], 50, 150, BLOCK_100_PNG_PATH));
		_blocks.push_back(std::move(component));
	}
}

void BlockManager::render()
{
	for (auto &block : _blocks)
	{
		block->render();
	}
}

std::vector<std::shared_ptr<Block>> BlockManager::getBlocks()
{
	return _blocks;
}

void BlockManager::hitBlock(std::shared_ptr<Block> block)
{
	block->takeLife();

	if (block->getLife() == 4)
	{
		block->loadTexture(BLOCK_100_PNG_PATH);
	}
	else if (block->getLife() == 3)
	{
		block->loadTexture(BLOCK_75_PNG_PATH);
	}
	else if (block->getLife() == 2)
	{
		block->loadTexture(BLOCK_50_PNG_PATH);
	}
	else if (block->getLife() == 1)
	{
		block->loadTexture(BLOCK_25_PNG_PATH);
	}
	else
	{
		int c = 0;
		for (auto &x : _blocks)
		{
			if (x == block)
			{
				std::vector<std::shared_ptr<Block>>::iterator index = std::find(_blocks.begin(), _blocks.end(), _blocks.at(c));

				if (index != _blocks.end())
				{
					_blocks.erase(index);
				}
				return;
			}
			c++;
		}
	}
}
