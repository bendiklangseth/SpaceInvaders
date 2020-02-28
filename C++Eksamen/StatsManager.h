#ifndef STATS_MANAGER_H
#define STATS_MANAGER_H
#include "Component.h"
#include "SDL_ttf.h"
#include <string.h>
#include <sstream>
#include <vector>
#include <memory>

class StatsManager
{
public:
	StatsManager();
	~StatsManager();

	void init();
	void update();
	void render();

	void removeHeart();
	

private:

	TTF_Font *font1;

	std::vector<std::shared_ptr<Component>> _hearts;

	Component *heart1;
	Component *heart2;

	int score;
	int prevLives;
	
};

#endif // !STATS_MANAGER_H



