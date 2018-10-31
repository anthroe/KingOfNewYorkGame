#pragma once
#include <string>
#include "dice.h"
using namespace std;
class diceRoller
{
public:
	diceRoller();
	void playerRoll();
	void displayDiceContainer();
	dice *getDiceContainer();
	string getDiceContainerTop(int n);
	bool getDiceResolve(int n);
	void setDiceResolve(int n, bool res);
	const int size();


private:
	dice* diceContainer[6];

};