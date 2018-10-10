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
	// Ensure that the player doesn't already own the card trying to be added
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

void player::addEnergy(int n) {
	if (energy + n > 0)
		energy += n;
}

void player::rollDice() {

}

void player::resolveDice() {

}

void player::move() {

}

bool player::buyCards(Deck deck) {
	// Store the response in a character
	char response;
	// Ask the player if they want to buy a card, and repeat until they answer properly
	do {
		cout << "Would you like to buy a card? (Y/N)" << endl;;
		cin >> response;
		if (response != 'Y' || response != 'y' || response != 'N' || response != 'n')
			cout << "Invalid response. Try again." << endl;
	} while (response != 'Y' || response != 'y' || response != 'N' || response != 'n');

	// If they want to buy a card, show them what they can buy
	if (response == 'Y' || response == 'y') {
		bool cont = false; // continuation condition
		do {
			// Ask which card they want to buy, and repeat until they answer properly
			do {
				cout << "Which card would you like to buy? (Enter the row number)" << endl;
				// Give a list of cards
				for (int i = 0; i < deck.getPurchaseableCards.size(); i++) {
					cout << i + 1 << ". " << deck.getPurchaseableCards[i] << endl;
				}
				cin >> response;
			} while (response > deck.getPurchaseableCards().size());

			// Ensure that they have enough money
			if (energy >= deck.getPurchaseableCards()[response].getCost()) {
				addOwnedCard(deck.purchaseCard(deck.getPurchaseableCards()[response]));
				energy -= deck.getPurchaseableCards()[response].getCost();
			}

			// Ask the player if they want to buy another card, and repeat until they answer properly
			do {
				cout << "Would you like to buy another card? (Y/N)" << endl;;
				cin >> response;
				if (response != 'Y' || response != 'y' || response != 'N' || response != 'n')
					cout << "Invalid response. Try again." << endl;
			} while (response != 'Y' || response != 'y' || response != 'N' || response != 'n');

			// If they want to buy another card set cont to true
			if (response == 'Y' || response == 'y')
				cont = true;

		} while (cont);
	}
}