#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "gameCard.h"
#include "region.h"
#include "monsterCard.h"
#include "deck.h"
#include <vector>
#include <string>

using namespace std;
class player {
private:
	string name;
	int id;
	static int nextId;
	vector<Region*> regions;
	MonsterCard monsterCard;
	vector<GameCard> ownedCards;
	string region;
	int energy = 0;
	//dice* diceContainer[6];

public:
	player();
	~player();
	player(string);
	player(string, vector<Region>);

	int getId();
	vector<Region*> getRegions();


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

	void move(player* player, Region region);

	bool buyCards(Deck deck);
};

#endif