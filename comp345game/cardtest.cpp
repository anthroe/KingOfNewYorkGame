#include "card.h"
#include "cardtest.h"
#include "deckCard.h"
#include "monsterCard.h"
#include <iostream>
#include <fstream>
#include <list>
#include "libraries/json.hpp"
using json = nlohmann::json;

// Opens a file and returns the ifstream object of the file
std::ifstream getCardList(std::string fileName) {
	// attempt to open the list of special cards.
	std::ifstream cardList(fileName);
	std::cout << "Opening " << fileName;
	std::cin.get();
	// if the file couldn't be opened/found exit.
	if (!cardList) {
		std::cout << "Could not find " << fileName;
		std::cin.get();
		exit(0);
	} else {
		std::cout << "Found " << fileName;
		std::cin.get();
	}

	return cardList;
}

int card::main() {
	json cardListJson;
	getCardList("resources/kony-card-list.json") >> cardListJson;

	json specialCardListJson;
	getCardList("resources/kony-special-card-list.json") >> specialCardListJson;

	json monsterCardListJson;
	getCardList("resources/kony-monster-card-list.json") >> monsterCardListJson;

	// Build a list of DeckCard objects listing game cards
	std::list<DeckCard> ListOfCards;
	for (json card : cardListJson) {
		ListOfCards.push_back(
			DeckCard(card["name"],
					"Deck",
					card["type"],
					card["effect"],
					card["cost"]));
	}

	// Build a list of DeckCard objects listing special cards
	std::list<DeckCard> ListOfSpecialCards;
	for (json card : specialCardListJson) {
		ListOfSpecialCards.push_back(
			DeckCard(card["name"],
					"Special",
					card["type"],
					card["effect"],
					card["cost"]));
	}

	// Build a list of MonsterCard objects listing monsters cards
	std::list<MonsterCard> ListOfMonsterCards;
	for (json card : monsterCardListJson) {
		ListOfMonsterCards.push_back(
			MonsterCard(card["name"],
						"Monster"));
	}

	for (DeckCard card : ListOfCards) {
		std::cout << "Deck card name: " << card.getName() << std::endl;
		std::cout << "Deck card type: " << card.getType() << std::endl;
		std::cout << "Deck card play type: " << card.getPlayType() << std::endl;
		std::cout << "Deck card effect: " << card.getEffect() << std::endl;
		std::cout << "Deck card cost: " << card.getCost() << "\n" << std::endl;
	}

	for (DeckCard card : ListOfSpecialCards) {
		std::cout << "Deck card name: " << card.getName() << std::endl;
		std::cout << "Deck card type: " << card.getType() << std::endl;
		std::cout << "Deck card play type: " << card.getPlayType() << std::endl;
		std::cout << "Deck card effect: " << card.getEffect() << std::endl;
		std::cout << "Deck card cost: " << card.getCost() << "\n" << std::endl;
	}

	for (MonsterCard card : ListOfMonsterCards) {
		std::cout << "Deck card name: " << card.getName() << std::endl;
		std::cout << "Deck card type: " << card.getType() << std::endl;
		std::cout << "Deck card HP: " << card.hp << std::endl;
		std::cout << "Deck card effect: " << card.vp << "\n" << std::endl;
	}

	std::cin.get();

	return 0;
}