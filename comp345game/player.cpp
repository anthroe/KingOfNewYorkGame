#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "player.h"
#include "diceRoller.h"

using namespace std;

int player::playerId = 1;

player::player() {
	name = "";
	id = playerId; playerId++;
<<<<<<< HEAD
	
=======
	//add dice
>>>>>>> 7c6523a5ec1099057c39b58eeda98f832d73b20d
}

player::player(string name) {
	this->name = name;
	id = playerId; playerId++;
<<<<<<< HEAD
	
=======
	//add dice
>>>>>>> 7c6523a5ec1099057c39b58eeda98f832d73b20d
}

player::player(string name, Region region) {
	this->name = name;
	id = playerId; playerId++;
	this->region = region;
<<<<<<< HEAD
	
=======
	//add dice
>>>>>>> 7c6523a5ec1099057c39b58eeda98f832d73b20d
}

void player::setMonsterCard(MonsterCard monst) {
	monsterCard = monst;
}

bool player::addOwnedCard(GameCard card) {
	std::string cardName = card.getName();
	bool cardNotOwned = true;
	// Ensure that the player doesn't already own the card trying to be added
	for (GameCard c : ownedCards) {
		if (c.getName() == cardName) {
			cardNotOwned = false;
		}
	}
	

	if (cardNotOwned)
		ownedCards.push_back(card);
	else
		return false;

	return true;
}

void player::addEnergy(int n) {
	if (energy + n > 0)
		energy += n;
}

void player::rollDice() {
	diceRoller playDice;
	playDice.playerRoll();
}

void player::resolveDice() {

}

void player::move(Region region) {
	this->region = region;

}

void player::buyCards(Deck deck) {
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
				for (int i = 0; i < deck.getPurchaseableCards().size(); i++) {
					GameCard card = deck.getPurchaseableCards()[i];
					cout << i + 1 << ". " << card.getName() << " (Cost: " << card.getCost() << ")" << endl;
				}
				cin >> response;
			} while (response > deck.getPurchaseableCards().size());

			// Ensure that they have enough money
			if (energy >= deck.getPurchaseableCards()[response].getCost()) {
				// If the card type is Discard, discard the card (in the future, it should also use the effect)
				if (deck.purchaseCard(deck.getPurchaseableCards()[response]).getPlayType() == "Discard") {
					deck.discardCard(deck.getPurchaseableCards()[response]);
				}
				// Otherwise, the card be purchased is Keep type and should be added to the player's hand
				else {
					addOwnedCard(deck.purchaseCard(deck.getPurchaseableCards()[response]));
					energy -= deck.getPurchaseableCards()[response].getCost();
					deck.shuffle();
				}
			}

			// Ask the player if they want to buy another card, and repeat until they answer properly
			do {
				cout << "Would you like to buy another card? (Y/N)" << endl;
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