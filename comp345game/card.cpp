#include "card.h"

using namespace std;

Card::Card() {
	name = "Unavailable";
	type = 3;
}

string Card::getTypeName() {
	switch (type) {
		case 0: return "Game"; break;
		case 1: return "Special"; break;
		case 2: return "Monster"; break;
		default: return "Invalid"; break;
	}
}