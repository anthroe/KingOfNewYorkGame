#include <iostream>
#include "PhaseObserver.h"

void phaseObserver::update(player* p, string phase, string action) 
{
	if (p == NULL) {
		cout << "Cannot update null player" << endl;
	}
	else
	{
		currPlayer = p;
		currPhase = phase;
		currAction = action;

		displayPhase();
	}
}
void phaseObserver::displayPhase() {
	cout << endl << "................................................" << endl;
	cout << currPlayer->getName() + ": " + currPhase + " step" << endl;
	if (currAction.compare("") != 0 && currAction.compare(" ") != 0)
		cout << currPlayer->getName() + "'s action is: " << currAction << endl;
	cout << endl << "................................................" << endl << endl;
}

void phaseObserver :: update() {

}