#include "dice.h"
#include <iostream>
#include <cstdlib> 
#include <ctime> 
#include <string>
using namespace std;
dice::dice()
{
	
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



	