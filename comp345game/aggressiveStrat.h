#pragma once
#include <algorithm>
#include "../player.h"
#include "../startup.h"
#include "../gameStart.h"

class aggressiveStrat : public player {
public:
	aggressiveStrat();
	virtual ~aggressiveStrat();
	aggressiveStrat(string);
	diceRoller playDice;
	Region region;
	bool damaged;
	string name;
	int id;
	void move();
	void rollDice();
	void resolveDice(Deck deck);
	void buyCards();
};
