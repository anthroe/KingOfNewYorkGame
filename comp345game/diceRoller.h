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
	void playerRoll(player* currentPlayer);
	void botRoll(string type, player* currentPlayer);
	void displayDiceContainer();
	vector<dice*> getDiceContainer();
	string getDiceContainerTop(int n);
	bool getDiceResolve(int n);
	void setDiceResolve(int n, bool res);
	void firstRoll(); 
	void rollNDice(int);
	void attachTurnObs(turnObserver* obs) { turnObservers.push_back(obs); }
	void notifyAllTurnObs(player *p);
	int size();

private:
	vector<dice*> diceContainer;
	vector<turnObserver*> turnObservers;

};