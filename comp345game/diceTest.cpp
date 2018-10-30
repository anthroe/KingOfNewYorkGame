#include <iostream>
#include <string>
#include <ctime>
#include "dice.h"
#include "diceRoller.h"

using namespace std;

int diceDriver()
{
	dice playDice;
	int num = (rand() % 6);
	string topOfDice = playDice.diceSymbols[num];
	srand((unsigned)time(0));
	//int random_integer;
	cout << "Rolling the dice 6 times" << endl;
	/*
	for (int index = 0; index < 6; index++) {
		random_integer = (rand() % 6);
		topOfDice = playDice.diceSymbols[random_integer];
		cout << "We have landed on the number " << random_integer << " it's symbol is " << topOfDice << endl;
	}*/
	diceRoller r1;
	r1.playerRoll();
	r1.resolveDice();
	
	return 0;
}
