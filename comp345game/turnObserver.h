#pragma once
#include "observer.h"
#include "player.h"
#include "diceRoller.h"

class turnObserver : public Observer
{
private:
	player* currPlayer;
	diceRoller playDice;

public:
	turnObserver() {};
	//phaseObserver(player* plr) : currPlayer(plr) {};
	void update();
	void update(player* p);
	void displayDice();
};
