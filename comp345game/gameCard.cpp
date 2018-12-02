#include "gameCard.h"

// |--------------------------------------------------------------------------|
// |The following section is methods that have to do with the observer pattern|
// |--------------------------------------------------------------------------|
void GameCard::notify() {
	observer->update(getName(), effect);
}