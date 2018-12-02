#include "CardObserver.h"

void cardObserver::update(string cardName, string effect) {
	displayCardEffect(cardName, effect);
}

void cardObserver::displayCardEffect(string cardName, string effect) {
	cout << cardName << " has been used. It's effect is:" << endl;
	cout << effect << endl;
}