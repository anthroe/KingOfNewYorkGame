#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "deck.h"
#include "diceRoller.h"
#include "gameCard.h"
#include "IPlayerType.h"
#include "Map.h"
#include "monsterCard.h"
#include "Observer.h"
//#include "phaseObserver.h" //causes errors
#include "region.h"
#include "Subject.h"

using namespace std;

class IPlayerType;
class phaseObserver; //incomplete declaration causes it limited functionality

class player : public Subject {
private:
	string name;
	int id;
	static int playerId;
	MonsterCard *monsterCard;
	vector<GameCard> ownedCards;
	Region region;
	diceRoller playDice;
	int energy = 0;
	bool damaged;

	// === Strategy Design ===
	IPlayerType* playerType;
	//========================

public:
	player();
	player(string);

	int getId() { return id;  };
	string getName() { return name; };
	diceRoller getDice() { return playDice; }

	void setMonsterCard(MonsterCard *monst);
	MonsterCard *getMonsterCard() { return monsterCard; };

	bool addOwnedCard(GameCard);
	vector<GameCard> getOwnedCards() { return ownedCards; };
	void setOwnedCards(vector<GameCard>);
	bool transferSpecialCard(string);

	void addEnergy(int);
	int getEnergy() { return energy; }
	void setEnergy(int);

	void setRegion(Region);
	Region getRegion() { return region; }

	void applyDiceEffect(int, int, Deck);
	int firstRoll();

	void setDamage(bool);
	bool isDamaged();

	bool operator==(const player&) const;

	// === Strategy Design ===
	void setPlayerType(IPlayerType* type) { this->playerType = type; }
	void move();
	void chooseStartingRegion();
	void rollDice();
	void resolveDice();
	void buyCards();
	//========================

// |--------------------------------------------------------------------------|
// |The following section is methods that have to do with the observer pattern|
// |--------------------------------------------------------------------------|
private:
	vector<phaseObserver*> observers;
	int state;

public:
	int getState() { return state; };
	void setState(int);

	void attach(phaseObserver* obs) { observers.push_back(obs); };

	void notify(Observer* o);
	void notifyAll(string phase, string action);
	void notifyAll() {};
};

#endif