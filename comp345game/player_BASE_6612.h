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
	MonsterCard *monsterCard;
	vector<GameCard> ownedCards;
	Region region;
	diceRoller playDice;
	int energy = 0;
	bool inline responseToBool(string response);
	string inline buyCardPrompt(string prompt);
	bool damaged;

public:
	player();
	player(string);

	int getId() { return id;  };
	string getName() { return name; };


	void setMonsterCard(MonsterCard *monst);
	MonsterCard *getMonsterCard() { return monsterCard; };

	bool addOwnedCard(GameCard);
	vector<GameCard> getOwnedCards() { return ownedCards; };
	bool transferSpecialCard(string);

	void addEnergy(int);
	int getEnergy() { return energy; }

	void setRegion(Region);
	Region getRegion() { return region; }
	void move();
	void move_kony();

	void applyDiceEffect(int, int, Deck);
	void rollDice();
	void resolveDice(Deck);
	int firstRoll();

	void buyCards(Deck);

	void setDamage(bool);
	bool isDamaged();

	bool operator==(const player&) const;
};

#endif