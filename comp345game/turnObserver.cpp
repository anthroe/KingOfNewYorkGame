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
	//string ability[NUMOFSYMBOLS] = { "Energy", "Heal", "Attack", "Celebrity", "Destruction", "Ouch" };
	cout << endl << "................................................" << endl;
	cout << currPlayer->getName() << " has rolled:" << endl;
	//	int *numOfResolves = countResolves();
	cout << "Type:     Number Rolled:" << endl;
	for (int i = 0; i < playDice.size(); i++) {
		if (numOfResolves[i] > 0)
			cout << ability[i] << " : " << numOfResolves[i] << endl;
	}
}

void turnObserver::update() {

}