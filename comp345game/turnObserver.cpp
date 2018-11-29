#include <iostream>
#include "turnObserver.h"
#include "dice.h"
void turnObserver::update(player* p)
{
	if (p == NULL) {
		cout << "Cannot update null player" << endl;
	}
	else
	{
		currPlayer = p;
		playDice = p->getDice();
		displayDice();
	}
}

void turnObserver::displayDice() {
	const int NUMOFSYMBOLS = 6;
	int numOfResolves[NUMOFSYMBOLS];
	string ability[NUMOFSYMBOLS] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
	for (int i = 0; i < NUMOFSYMBOLS; i++)
	{
		numOfResolves[i] = 0;
	}

	for (int i = 0; i < NUMOFSYMBOLS; i++)
	{
		for (int j = 0; j < currPlayer->getDice().size(); j++)
		{
			if (currPlayer->getDice().getDiceContainerTop(j).compare(ability[i]) == 0)
				numOfResolves[i]++;
		}
	}
	cout << endl << "................................................" << endl;
	cout << currPlayer->getName() << " has rolled:" << endl;
	cout << "Type and the number of time they have been rolled:" << endl;
	for (int i = 0; i < playDice.size(); i++) {
		if (numOfResolves[i] > 0)
		{
			cout << ability[i] << " : " << numOfResolves[i] << endl;
		}
	}
	cout << "Dices symbols: ordered from 1-6" << endl;
	for (int i = 0; i < playDice.size(); i++) {
		cout << i + 1 << " : " << playDice.getDiceContainerTop(i) << endl;
	}

}

void turnObserver::update() {

}