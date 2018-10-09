#include <iostream>
#include <string>
#include <ctime>
#include "dice.h"
#include "diceRoller.h"

using namespace std;

int diceDriver()
{
	srand((unsigned)time(0));
	diceRoller player1;
	player1.playerRoll();
	/*diceRoller player2;
	player2.playerRoll();*/
	system("pause");
	return 0;
}
