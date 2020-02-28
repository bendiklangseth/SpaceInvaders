#ifndef BLOCK_MANAGER_H
#define BLOCK_MANAGER_H

#include "Block.h"
#include <memory>
#include <vector>

class BlockManager
{
public:
	BlockManager();
	~BlockManager();

	void initialize();
	void render();
	
	std::vector<std::shared_ptr<Block>> getBlocks();
	void hitBlock(std::shared_ptr<Block> block);

private:
	std::vector<std::shared_ptr<Block>> _blocks;

};

#endif // !BLOCK_MANAGER_H



