#pragma once
#include "player.h"
class mainLoop {
private:
	vector<player> playerOrder;
	Map currMap;
	int turn;
public:
	mainLoop();
	void play();
};