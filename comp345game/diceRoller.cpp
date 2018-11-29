#include "diceRoller.h"
#include "player.h"
#include "turnObserver.h"
#include <iostream>
#include <ctime> 
#include <string>
#include <sstream>
#include <vector>
using namespace std;
// creating a diceRoller object that initializes 6 dices, based on the size of the container
diceRoller::diceRoller()
{
	if (diceContainer == NULL)
		cout << "No dice container created" << endl;
	const int size = (sizeof(diceContainer) / sizeof(*diceContainer));
	for (int index = 0; index < size; index++) {
		diceContainer[index] = new dice();
	}
}
void diceRoller::playerRoll(player* currentPlayer)
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
	//diceRoller::displayDiceContainer();
	notifyAllTurnObs(currentPlayer);
	string input;
	cout << "Would you like to roll again? y/n" << endl;
	cin >> input;

	while (input != "y" && input != "Y" && input != "n" && input != "N") {
		cin.clear();
		cin.ignore(256, '\n');
		cin >> input;
	}

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
		//diceRoller::displayDiceContainer(); 
		notifyAllTurnObs(currentPlayer);
		if (optionalRoll <= numberOfMaxRerolls)
		{
			cout << "Would you like to roll again? y/n" << endl;
			cin >> input;
		}
	}
}
void diceRoller::botRoll(string botType, player* currentPlayer)
{
	const int size = sizeof(diceContainer) / sizeof(*diceContainer);
	for (int index = 0; index < size; index++) {
		diceContainer[index]->rollDice(); // has no value
	}

	int numberOfMaxRerolls = 2;
	//first roll
	notifyAllTurnObs(currentPlayer);
	//displayDiceContainer();


	int roll = 0; // bot rolls twice without input

	while (roll < numberOfMaxRerolls)
	{
		cout << "Rerolling..." << endl;
		roll++;
		if (botType.compare("agressive") == 0)
		{
			for (int i = 0; i < size; i++)
			{

				if (getDiceContainerTop(i).compare("Attack") != 0 && getDiceContainerTop(i).compare("Destruction") != 0) {
					diceContainer[i]->rollDice();
				}

			}
		}
		else if (botType.compare("moderate") == 0)
		{
			for (int i = 0; i < size; i++)
			{

				if (getDiceContainerTop(i).compare("Heal") != 0
					&& getDiceContainerTop(i).compare("Energy") != 0
					&& getDiceContainerTop(i).compare("Celebrity") != 0) {
					diceContainer[i]->rollDice();
				}

			}
		}
		notifyAllTurnObs(currentPlayer);
		
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
dice *diceRoller::getDiceContainer()
{
	return *diceContainer;
}
string diceRoller::getDiceContainerTop(int n)
{
	return diceContainer[n]->getDiceTop();
}
void diceRoller::setDiceResolve(int n, bool res)
{
	diceContainer[n]->setResolve(res);
}
bool diceRoller::getDiceResolve(int n)
{
	return diceContainer[n]->getResolve();
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

void diceRoller::rollNDice(int n)
{
	if (n >= 0 && n <= 6)
		diceContainer[n]->rollDice();
}
void diceRoller::notifyAllTurnObs(player *p)
{
	for (turnObserver* obs : turnObservers) {
		obs->update(p);
	}
}