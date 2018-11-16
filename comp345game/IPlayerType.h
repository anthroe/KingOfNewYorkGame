#pragma once
#include "player.h"
#include "deck.h"

class player;

class IPlayerType {

public:
	virtual void rollDice(player*);
	virtual void resolveDice(player*);
	virtual void move(player*);
	virtual void chooseStartingRegion(player*);
	virtual void buyCards(player*);
};

class aggressiveBot : public IPlayerType {
public:
	virtual void rollDice(player*);
	virtual void move(player*);
};

class moderateBot : public IPlayerType {
public:
	virtual void rollDice(player*);
	virtual void move(player*);
};

class client : public IPlayerType {
public:
	virtual void rollDice(player*);
	virtual void resolveDice(player*);
	virtual void move(player*);
	virtual void chooseStartingRegion(player*);
};