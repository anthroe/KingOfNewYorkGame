#include "startup.h"

using namespace std;

startup::startup() {

}

void randomPlayerOrder() {

}

void diceRoller::firstRoll()
{
	const string enable = "enable";
	const string disable = "disable";
	const int size = sizeof(diceContainer) / sizeof(*diceContainer);
	int numberOfMaxRerolls = 2;
	//first roll
	for (int index = 0; index < diceRoller::size(); index++) {
		diceContainer[index]->rollDice();
		diceContainer[index]->setResolve(true);
	}
}

int player::firstRoll()
{
	playDice.firstRoll();
	playDice.displayDiceContainer();
	int count = 0;
	for (int i = 0; i < playDice.size(); i++)
	{
		if (playDice.getDiceContainerTop(i).compare("Attack") == 0)
		{
			count++;
		}

	}
	return count;
}