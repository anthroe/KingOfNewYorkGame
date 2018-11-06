#pragma once
#include "player.h"
class mainLoop {
private:
	vector<player> playerOrder;
	Map currMap;
	int turn;
	//player* getWinner();
public:
	mainLoop();
	void play();
	//int getTurn();
};