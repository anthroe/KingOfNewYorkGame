#pragma once
#include <algorithm>
#include "player.h"
#include "startup.h"
#include "gameStart.h"

class moderateStrat : public player {
public:
	moderateStrat();
	virtual ~moderateStrat();
	moderateStrat(string);
	diceRoller playDice;
	Region region;
	bool damaged;
	string name;
	int id;
	void move();
	void rollDice();
	void resolveDice();
	void buyCards();
};
