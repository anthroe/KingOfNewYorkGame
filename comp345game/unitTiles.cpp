#include "unitTiles.h"
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

UnitTiles::UnitTiles() {
	// Fill the vector with the health of the tiles
	// which vary between 1 and 3.
	for (int i = 0; i < 45; i++) {
		unitTiles.push_back((i % 3) + 1);
	}
}

void UnitTiles::shuffle() {
	auto rng = default_random_engine{(unsigned)time(0)};
	std::shuffle(unitTiles.begin(), unitTiles.end(), rng);
}