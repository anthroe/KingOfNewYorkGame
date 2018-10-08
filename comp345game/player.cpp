#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;
player::player() {
	cout << "I have been initialized " << endl;
}

void player::setRegion(string reg) {
	region = reg;
}

string player::getRegion() {
	return region;
}

void player::setMonsterCard(MonsterCard monst) {
	monsterCard = monst;
}

MonsterCard player::getMonsterCard() {
	return monsterCard;
}

bool player::addOwnedCard(GameCard card) {
	std::string cardName = card.getName();
	bool cardNotOwned = true;
	for (GameCard c : ownedCards) {
		if (c.getName() == cardName) {
			cardNotOwned == false;
		}
	}

	if (cardNotOwned)
		ownedCards.push_back(card);
	else
		return false;

	return true;
}

std::vector<GameCard> player::getOwnedCards() {
	return ownedCards;
}

void player::rollDice() {

}

void player::resolveDice() {

}

void player::move() {

}