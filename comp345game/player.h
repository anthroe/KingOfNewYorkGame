#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "gameCard.h"
#include "monsterCard.h"
#include "deck.h"
#include <vector>
#include <string>

using namespace std;
class player {
private:
	MonsterCard monsterCard;
	std::vector<GameCard> ownedCards;
	string region;
	int energy = 0;
	//dice* diceContainer[6];

public:
	player();
	void setRegion(string reg);
	string getRegion();

	void setMonsterCard(MonsterCard monst);
	MonsterCard getMonsterCard();

	bool addOwnedCard(GameCard monst);
	std::vector<GameCard> getOwnedCards();

	void addEnergy(int n);
	int getEnergy() { return energy; };

	void rollDice();
	void resolveDice();

	void move();

	bool buyCards(Deck deck);
};

#endif