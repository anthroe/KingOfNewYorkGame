#pragma once
#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
	private:
		std::string name;
		std::string type;
		// Player ownedBy = NULL;

	public:
		Card(std::string n, std::string t) : name(n), type(t) {};
		std::string getName() { return name; };
		std::string getType() { return type; };
};

#endif