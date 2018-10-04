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
	std::list<MonsterCard> ListOfMonsterCards;
	for (json card : monsterCardListJson) {
		std::string cname = card["name"];
		ListOfMonsterCards.push_back(MonsterCard(cname));
	}

	for (MonsterCard card : ListOfMonsterCards) {
		std::cout << "Deck card name: " << card.getName() << std::endl;
		std::cout << "Deck card type: " << card.getTypeName() << std::endl;
		std::cout << "Deck card HP: " << card.getHP() << std::endl;
		std::cout << "Deck card effect: " << card.getVP() << "\n" << std::endl;
	}

	std::cin.get();

	return 0;
}