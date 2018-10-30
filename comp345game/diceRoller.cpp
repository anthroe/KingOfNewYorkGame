#include "diceRoller.h"
#include <iostream>
#include <ctime> 
#include <string>
#include <sstream>
#include <vector>
using namespace std;
// creating a diceRoller object that initializes 6 dices, based on the size of the container
diceRoller::diceRoller()
{
	const int size = (sizeof(diceContainer) / sizeof(*diceContainer));
	for (int index = 0; index < size; index++) {
		diceContainer[index] = new dice();
	}
}
void diceRoller::playerRoll()
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
	diceRoller::displayDiceContainer();
	string input;
	cout << "Would you like to roll again? y/n" << endl;
	cin >> input;
	int optionalRoll = 1;
	
	while (input.compare("y") == 0 && optionalRoll <= 2)
	{
		optionalRoll++;
		cout << "Which dice number would you like to roll?" << endl << "Enter in the following format: 1,2,3,4,5,6" << endl;
		cin >> input;
		stringstream ss(input);
		string token;
		bool enableArray[size] = { false, false, false, false, false, false };
		int num = 0, count = 0;

		//making substrings and parsing the input string to know which dices to reroll, from string to int
		while (getline(ss, token, ','))
		{
			istringstream buffer(token);
			buffer >> num;
			if (num >= 1 && num <= diceRoller::size())
			{
				enableArray[num - 1] = true;
			}

		}
		//rerolling desired dices
		for (int i = 0; i < diceRoller::size(); i++)
		{
			if (enableArray[i] == true)
			{
				diceContainer[i]->setStatus(enable);
				diceContainer[i]->rollDice();
			}
			else
			{
				diceContainer[i]->setStatus(disable);
			}
			
		}
		diceRoller::displayDiceContainer();
		if (optionalRoll <= numberOfMaxRerolls)
		{
			cout << "Would you like to roll again? y/n" << endl;
			cin >> input;
		}
	}
}
void diceRoller::resolveDice()
{
	diceRoller::displayDiceContainer();
	bool resolving = true;
	cout << endl << "Press 1 to resolve Energy dices" << endl << 
	"Press 2 to resolve Heal dices" << endl << "Press 3 to resolve Attack" << endl
	<< "Press 4 to resolve Celebrity dices" << endl << "Press 5 to resolve Destruction " << endl << 
	"Press 6 to resolve Ouch dices" << endl;
	string ability[6] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
	while (resolving)
	{
		cout << "Which type of dices would you like to resolve?" << endl;
		int num;
		cin >> num;
		int count = 0;
		for (int i = 0; i < diceRoller::size(); i++)
		{
			if (diceContainer[i]->getDiceTop().compare(ability[num - 1]) == 0 && diceContainer[i]->getResolve() == true)
			{
				//call a resolve function
				cout << "Dice number " << i + 1 << " with type " << diceContainer[i]->getDiceTop() << " has been resolved " << endl;
				diceContainer[i]->setResolve(false);
			}
			if (diceContainer[i]->getResolve() == false)
				count++;
			if (count == diceRoller::size())
			{
				resolving = false;
				cout << "All dices have been resolved succesfully, you may begone thot" << endl;
			}
				
		}
	}
	
}
void diceRoller::displayDiceContainer()
{
	for (int index = 0; index < diceRoller::size(); index++) {
		cout << "Dice number "<< index+1 << " has the value " << diceContainer[index]->getDiceTop() << endl;
	}
}const int diceRoller::size()
{
	return (sizeof(diceContainer) / sizeof(*diceContainer));
}