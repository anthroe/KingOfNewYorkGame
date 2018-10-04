#pragma once
#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
	private:
		std::string name;
		int type;
		// Player ownedBy = NULL;

	public:
		Card(std::string n, int t) : name(n), type(t) {};
		std::string getName() { return name; };
		std::string getTypeName();
};

#endif