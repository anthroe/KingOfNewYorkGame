#include "diceRoller.h"
#include "player.h"
#include "turnObserver.h"
#include <iostream>
#include <ctime> 
#include <string>
#include <sstream>
#include <vector>
#include "diceRoller.h"

using namespace std;

// creating a diceRoller object that initializes 6 dices
diceRoller::diceRoller()
{

	for (int i = 0; i < 6; i++) {
		diceContainer.push_back(new dice());
	}

}

void diceRoller::playerRoll(player* currentPlayer)
{
	const string enable = "enable";
	const string disable = "disable";
	int numberOfMaxRerolls = 2;

	//first roll
	for (int i = 0; i < diceContainer.size(); i++) {
		diceContainer[i]->rollDice();
		diceContainer[i]->setResolve(true);
	}
	notifyAllTurnObs(currentPlayer);
	displayDiceContainer();

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
		bool enableArray[6] = { false, false, false, false, false, false };
		int num = 0, count = 0;

		//making substrings and parsing the input string to know which dices to reroll, from string to int
		while (getline(ss, token, ','))
		{
			istringstream buffer(token);
			buffer >> num;
			if (num >= 1 && num <= diceContainer.size())
			{
				enableArray[num - 1] = true;
			}

		}

		//rerolling desired dices
		for (int i = 0; i < diceContainer.size(); i++)
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

		notifyAllTurnObs(currentPlayer);
		displayDiceContainer();

		if (optionalRoll <= numberOfMaxRerolls)
		{
			cout << "Would you like to roll again? y/n" << endl;
			cin >> input;
		}
	}
}

void diceRoller::botRoll(string botType, player* currentPlayer)
{
	for (int i = 0; i < diceContainer.size(); i++) {
		diceContainer[i]->rollDice(); // has no value
	}

	notifyAllTurnObs(currentPlayer);

	int roll = 0; // bot rolls twice without input

	while (roll < 2)
	{
		cout << "Rerolling..." << endl;
		roll++;
		if (botType.compare("agressive") == 0)
		{
			for (int i = 0; i < diceContainer.size(); i++)
			{

				if (getDiceContainerTop(i).compare("Attack") != 0 && getDiceContainerTop(i).compare("Destruction") != 0) {
					diceContainer[i]->rollDice();
				}

			}
		}
		else if (botType.compare("moderate") == 0)
		{
			for (int i = 0; i < diceContainer.size(); i++)
			{

				if (getDiceContainerTop(i).compare("Heal") != 0 && getDiceContainerTop(i).compare("Energy") != 0 && getDiceContainerTop(i).compare("Celebrity") != 0) {
					diceContainer[i]->rollDice();
				}
			}
		}
		notifyAllTurnObs(currentPlayer);
	}
	displayDiceContainer();
}

void diceRoller::displayDiceContainer()
{
	for (int i = 0; i < diceContainer.size(); i++) {
		cout << "Dice number "<< i+1 << " has the value " << diceContainer[i]->getDiceTop() << endl;
	}
}

vector<dice*> diceRoller::getDiceContainer()
{
	return diceContainer;
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

void diceRoller::firstRoll(){
	const string enable = "enable";
	const string disable = "disable";
	int numberOfMaxRerolls = 2;

	//first roll
	for (int i = 0; i < diceContainer.size(); i++) {
		diceContainer[i]->rollDice();
		diceContainer[i]->setResolve(true);
	}
}

void diceRoller::rollNDice(int n) {
	if (n >= 0 && n < diceContainer.size())
		diceContainer[n]->rollDice();
}

void diceRoller::notifyAllTurnObs(player *p)
{
	for (turnObserver* obs : turnObservers) {
		obs->update(p);
	}
}

int diceRoller::size() {
	return diceContainer.size();
}