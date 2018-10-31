#include <iostream>
#include <string>
#include <ctime>
#include "player.h"
#include "Map.h"

using namespace std;

int playerDriver()
{
	
	string input;
	srand((unsigned)time(0)); //can only seed here or diceTest.ccp driver
	cout << "What is your name?" << endl;
	cin >> input;
	player player1(input);
	cout << "Welcome to King of New York: " + player1.getName() +"\n" << endl;
	cout << player1.getName() + " is rolling the dice \n" << endl;
	player1.rollDice();
	player1.resolveDice();
	system("pause");
	return 0;
}
