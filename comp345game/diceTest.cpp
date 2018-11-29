#include <iostream>
#include <string>
#include <ctime>
#include "dice.h"
#include "diceRoller.h"

using namespace std;

int diceDriver()
{
	dice playDice;
	srand((unsigned)time(0));
	cout << "Rolling the dice 6 times" << endl;
	diceRoller r1;
	//r1.playerRoll();
	
	return 0;
}
