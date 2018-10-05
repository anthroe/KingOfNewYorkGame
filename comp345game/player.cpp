#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
player::player()
{
	cout << "I have been initialized " << endl;
}
void player::setRegion(string reg)
{
	region = reg;
}
void player::setMonsterCard(string monst)
{
	monsterCard = monst;
}
string player::getRegion()
{
	return region;
}
string player::getMonsterCard()
{
	return monsterCard;
}
void player::rollDice()
{

}
void player::resolveDice()
{

}
void player::move()
{

}

