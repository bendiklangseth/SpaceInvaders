#ifndef BOT_MANAGER_H
#define BOT_MANAGER_H

#include <SDL_mixer.h>
#include "StandardBot.h"
#include <memory>
#include <vector>
#include <ctime>

class BotManager
{
public:
	BotManager();
	~BotManager();

	void reset();
	void initializeStandardBots(); 
	void update();
	void renderBots();

	void deleteBot(std::shared_ptr<StandardBot> bot);
	void deleteBullet(std::shared_ptr<Bullet> bullet);

	std::vector<std::shared_ptr<StandardBot>> getBots() const;
	std::vector<std::shared_ptr<Bullet>> getBullets() const;
	

	void animateStandardBots();

private:
	std::vector<std::shared_ptr<StandardBot>> _currentBots;
	std::vector<std::shared_ptr<StandardBot>> _idleBots;
	std::vector<std::shared_ptr<StandardBot>> _flyingBots;
	std::vector<std::shared_ptr<Bullet>> _bullets;

	std::shared_ptr<StandardBot> _generalBot;
	std::shared_ptr<StandardBot> _masterBot;

	int _level;

	clock_t _timeStart;
	clock_t _timeStop;
	Mix_Chunk * botSound;

	void setBotsDirection(int direction);
	void pushStandardBotsDown(int pixels);

};

#endif // !BOT_MANAGER_H



