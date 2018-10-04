#include "card.h"

std::string Card::getTypeName() {
	switch (type) {
		case 0: return "Game";
		case 1: return "Special";
		case 2: return "Monster";
	}
}