#pragma once
#include <string>
#include <vector>
#include "dice.h"
#include "Subject.h"
using namespace std;
class player;
class turnObserver;
class diceRoller : public Subject
{
public:
	diceRoller();
	void playerRoll();
	void botRoll(string type, player* currentPlayer);
	void displayDiceContainer();
	dice *getDiceContainer();
	string getDiceContainerTop(int n);
	bool getDiceResolve(int n);
	void setDiceResolve(int n, bool res);
	const int size();
	void firstRoll(); 
	void rollNDice(int);
	void attachTurnObs(turnObserver* obs) { turnObservers.push_back(obs); }
	void notifyAllTurnObs(player *p);

private:
	dice* diceContainer[6];
	vector<turnObserver*> turnObservers;

};