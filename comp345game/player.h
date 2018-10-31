#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "region.h"
#include "deck.h"
#include "gameCard.h"
#include "monsterCard.h"
#include "Map.h"
#include "diceRoller.h"

using namespace std;

class player {
private:
	string name;
	int id;
	static int playerId;
	MonsterCard monsterCard;
	vector<GameCard> ownedCards;
	Region region;
	diceRoller playDice;
	int energy = 0;

public:
	player();
	player(string);
	player(string, Region);

	int getId() { return id;  };
	string getName() { return name; };

	Region getRegion() { return region; }

	void setMonsterCard(MonsterCard);
	MonsterCard getMonsterCard() { return monsterCard; };

	bool addOwnedCard(GameCard);
	vector<GameCard> getOwnedCards() { return ownedCards; };

	void addEnergy(int);
	int getEnergy() { return energy; }

	void rollDice();
	void resolveDice();

	void move(Region);

	void buyCards(Deck);
};

#endif