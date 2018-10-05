#pragma once
#include <string>
using namespace std;
class player
{
public:
	player();
	void setRegion(string reg);
	void setMonsterCard(string monst);
	string getRegion();
	string getMonsterCard();
	void rollDice();
	void resolveDice();
	void move();

	

private:
	string monsterCard;
	string region;
	//dice* diceContainer[6];

};
