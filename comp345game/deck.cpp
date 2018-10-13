#include "deck.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "libraries/json.hpp"
using json = nlohmann::json;

// Opens a file and returns the ifstream object of the file
std::ifstream Deck::getCardList(std::string fileName, bool verbose) {
	// Attempt to open the list of cards.
	std::ifstream cardList(fileName);

	if (verbose) {
		std::cout << "Opening:\t" << fileName << std::endl;

		// If the file couldn't be found/opened, exit.
		if (!cardList) {
			std::cout << "Could not find:\t" << fileName;
			std::cin.get();
			exit(0);
		}
		else
			std::cout << "Found:  \t" << fileName << "\n" << std::endl;
	}

	return cardList;
}

Deck::Deck(std::string deckFile, std::string specialFile){
	json cardListJson;
	getCardList(deckFile) >> cardListJson;

	// From the JSON make the game cards based on their attributes
	for (json card : cardListJson) {
		deck.push_back(
			GameCard(card["name"],
				CardTypes::GAME_CARD,
				card["type"],
				card["effect"],
				card["cost"]));
	}

	cardListJson = NULL;
	getCardList(specialFile) >> cardListJson;

	// From the JSON make the special cards based on their attributes
	for (json card : cardListJson) {
		specialCards.push_back(
			GameCard(card["name"],
				CardTypes::SPECIAL_CARD,
				card["type"],
				card["effect"],
				card["cost"]));
	}

	shuffle();
}

void Deck::shuffle() {
	srand((unsigned)time(0));

	int randomNums[3];
	randomNums[0] = rand() % deck.size();

	// Ensure randomNums[1] is unique
	do {
		randomNums[1] = rand() % deck.size();
	} while (randomNums[1] == randomNums[0]);

	// Ensure randomNums[2] is unique
	do {
		randomNums[2] = rand() % deck.size();
	} while (randomNums[2] == randomNums[0] && randomNums[2] == randomNums[1]);

	// Only keep 3 cards face-up for purchase
	int size = purchaseableCards.size();
	for (int i = 0; i < 3-size; i++) {
		purchaseableCards.push_back(deck[randomNums[i]]);
		deck.erase(deck.begin() + randomNums[i]);
	}
}

bool Deck::discardCard(GameCard card) {
	bool cardDiscarded = false;
	std::string cardName = card.getName();

	// Search the face-up cards for the card to be discarded
	for (int i = 0; i < purchaseableCards.size(); i++) {
		if (purchaseableCards[i].getName() == cardName) {
			discard.push_back(purchaseableCards[i]);
			purchaseableCards.erase(purchaseableCards.begin() + i);
			cardDiscarded = true;
		}
	}

	// If the card was discarded from the face-up card do not search the deck
	if (!cardDiscarded) {
		for (int i = 0; i < deck.size(); i++) {
			if (deck[i].getName() == cardName) {
				discard.push_back(deck[i]);
				deck.erase(deck.begin() + i);
				cardDiscarded = true;
			}
		}
	}

	return cardDiscarded;
}


GameCard Deck::purchaseCard(GameCard card) {
	std::string cardName = card.getName();

	// Search the face-up cards for the card to be discarded
	for (int i = 0; i < purchaseableCards.size(); i++) {
		if (purchaseableCards[i].getName() == cardName) {
			purchaseableCards.erase(purchaseableCards.begin() + i);
		}
	}

	return card;
}