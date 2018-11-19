#pragma once
#include "GameStatsObserver.h"
#include "player.h"

class mainLoop {
private:
	vector<player> playerOrder;
	Map currMap;
	int turn;
	vector<GameStatsObserver*> observers;

	void attach(GameStatsObserver* obs) { observers.push_back(obs); };
	void notify();
	
public:
	mainLoop();
	void play();
};