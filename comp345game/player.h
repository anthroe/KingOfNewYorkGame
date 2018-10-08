#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "gameCard.h"
#include "monsterCard.h"
#include <vector>
#include <string>

using namespace std;
class player {
private:
	MonsterCard monsterCard;
	std::vector<GameCard> ownedCards;
	string region;
	//dice* diceContainer[6];

public:
	player();
	void setRegion(string reg);
	string getRegion();

	void setMonsterCard(MonsterCard monst);
	MonsterCard getMonsterCard();

	bool addOwnedCard(GameCard monst);
	std::vector<GameCard> getOwnedCards();

	void rollDice();
	void resolveDice();

	void move();
};

#endif