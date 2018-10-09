#include "card.h"

using namespace std;

Card::Card() {

}

string Card::getTypeName() {
	switch (type) {
		case 0: return "Game"; break;
		case 1: return "Special"; break;
		case 2: return "Monster"; break;
		default: return "Invalid"; break;
	}
}