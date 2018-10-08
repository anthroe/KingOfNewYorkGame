#include "cardtest.h"
#include "deck.h"
#include <iostream>
#include <fstream>
#include <list>
#include "libraries/json.hpp"
using json = nlohmann::json;

int card::main() {
	json monsterCardListJson;
	Deck::getCardList("resources/kony-monster-card-list.json") >> monsterCardListJson;

	// Build a list of MonsterCard objects listing monsters cards
	std::vector<MonsterCard> ListOfMonsterCards;
	for (json card : monsterCardListJson) {
		std::string cname = card["name"];
		ListOfMonsterCards.push_back(MonsterCard(cname));
	}

	for (MonsterCard card : ListOfMonsterCards) {
		std::cout << "Monster card name: " << card.getName() << std::endl;
		std::cout << "Monster card type: " << card.getTypeName() << std::endl;
		std::cout << "Monster card HP: " << card.getHP() << std::endl;
		std::cout << "Monster card effect: " << card.getVP() << "\n" << std::endl;
	}

	// Testing Monster Card Functions
	if (!ListOfMonsterCards[0].changeHP(-1))
		std::cout << "HP could not decrease" << std::endl;
	std::cout << "HP: " << ListOfMonsterCards[0].getHP() << std::endl;
	if (!ListOfMonsterCards[0].changeHP(1))
		std::cout << "HP could not increase" << std::endl;
	std::cout << "HP: " << ListOfMonsterCards[0].getHP() << std::endl;
	if (!ListOfMonsterCards[0].changeHP(1))
		std::cout << "HP is at max" << std::endl;
	std::cout << "HP: " << ListOfMonsterCards[0].getHP() << std::endl;
	if (!ListOfMonsterCards[0].changeHP(-10))
		std::cout << "HP could not decrease" << std::endl;
	std::cout << "HP: " << ListOfMonsterCards[0].getHP() << std::endl;
	if (!ListOfMonsterCards[0].changeHP(-1))
		std::cout << "HP is at min" << std::endl;
	std::cout << "HP: " << ListOfMonsterCards[0].getHP() << std::endl;

	if (!ListOfMonsterCards[0].changeVP(-1))
		std::cout << "VP is at minimum" << std::endl;
	std::cout << "VP: " << ListOfMonsterCards[0].getVP() << std::endl;
	if (!ListOfMonsterCards[0].changeVP(1))
		std::cout << "VP could not increase" << std::endl;
	std::cout << "VP: " << ListOfMonsterCards[0].getVP() << std::endl;
	if (!ListOfMonsterCards[0].changeVP(-1))
		std::cout << "VP could not decrease" << std::endl;
	std::cout << "VP: " << ListOfMonsterCards[0].getVP() << std::endl;
	if (!ListOfMonsterCards[0].changeVP(20))
		std::cout << "VP could not increase (20)" << std::endl;
	std::cout << "VP: " << ListOfMonsterCards[0].getVP() << std::endl;
	if (!ListOfMonsterCards[0].changeVP(1))
		std::cout << "VP is at max" << std::endl;
	std::cout << "VP: " << ListOfMonsterCards[0].getVP() << std::endl;

	// Testing Deck Fucntions
	Deck d;
	std::cout << "Before Delete:" << std::endl;
	for (GameCard gc : d.getPurchaseableCards()) {
		std::cout << "Deck card name: " << gc.getName() << std::endl;
		std::cout << "Deck card type: " << gc.getTypeName() << std::endl;
		std::cout << "Deck card HP: " << gc.getCost() << std::endl;
		std::cout << "Deck card effect: " << gc.getEffect() << "\n" << std::endl;
	}

	std::cout << "\n\n\nAfter Delete:" << std::endl;
	if (d.discardCard(d.getPurchaseableCards()[1])) {
		d.shuffle();
		for (GameCard gc : d.getPurchaseableCards()) {
			std::cout << "Deck card name: " << gc.getName() << std::endl;
			std::cout << "Deck card type: " << gc.getTypeName() << std::endl;
			std::cout << "Deck card HP: " << gc.getCost() << std::endl;
			std::cout << "Deck card effect: " << gc.getEffect() << "\n" << std::endl;
		}
	}
	else
		std::cout << "Could not delete from Purchaseable Cards." << std::endl;

	std::cout << "\n\n\nDeck Delete:" << std::endl;
	if (d.discardCard(d.getDeck()[5])) {
		d.shuffle();
		for (GameCard gc : d.getPurchaseableCards()) {
			std::cout << "Deck card name: " << gc.getName() << std::endl;
			std::cout << "Deck card type: " << gc.getTypeName() << std::endl;
			std::cout << "Deck card HP: " << gc.getCost() << std::endl;
			std::cout << "Deck card effect: " << gc.getEffect() << "\n" << std::endl;
		}
	}
	else
		std::cout << "Could not delete from Deck." << std::endl;

	std::cin.get();

	return 0;
}