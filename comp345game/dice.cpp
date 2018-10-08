#include "dice.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <string>
using namespace std;
dice::dice()
{
	//
	//cout << "i am a dice" << endl;
}
void dice::setDiceTop(string top)
{
	topOfDice = top;
}
void dice::setStatus(string str)
{
	status = str;
}
void dice::printTop()
{
	cout << "Top of dice is " << topOfDice << endl;
}
string dice::getDiceTop()
{
	return topOfDice;
}
string dice::getStatus()
{
	return status;
}
void dice::rollDice()
{
	int num = (rand() % 6);
	topOfDice = dice::diceSymbols[num];

	
}
//cout <<"We have landed on the number " << num << " it's symbol is " << topOfDice << endl;


	//testing rollDice() functionality
	/*srand((unsigned)time(0));
	int random_integer;
	for (int index = 0; index < 20; index++) {
		random_integer = (rand() % 6);
		topOfDice = dice::diceSymbols[random_integer];
		cout << "We have landed on the number " << random_integer << " it's symbol is " << topOfDice << endl;
	}*/