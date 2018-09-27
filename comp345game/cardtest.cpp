#include "card.h"
#include "deckCard.h"
#include <iostream>

int main() {
	Card c { "testName", "testType" };
	std::cout << "Card name: " << c.getName() << std::endl;
	std::cout << "Card type: " << c.getType() << std::endl;
	DeckCard dc { "Deck Card 1", "Deck Card", "Discard", "Eat three (3) dicks", 5 };
	std::cout << "Deck card name: " << dc.getName() << std::endl;
	std::cout << "Deck card type: " << dc.getType() << std::endl;
	std::cout << "Deck card play type: " << dc.getPlayType() << std::endl;
	std::cout << "Deck card effect: " << dc.getEffect() << std::endl;
	std::cout << "Deck card cost: " << dc.getCost() << std::endl;
	std::cin.get();
	return 0;
}