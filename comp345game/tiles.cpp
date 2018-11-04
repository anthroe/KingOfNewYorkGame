#include "tiles.h"
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

Tiles::Tiles() {
	// Fill the vector with the health of the tiles
	// which vary between 1 and 3.
	for (int i = 0; i < 45; i++) {
		tiles.push_back((i % 3) + 1);
	}

	shuffle();
}

bool Tiles::removeFirstTile() {
	int before = tiles.size();
	tiles.erase(tiles.begin());
	int after = tiles.size();

	return before > after;
}

int Tiles::flipTile(int tileHP) {
	return tileHP + 1;
}

void Tiles::shuffle() {
	auto rng = default_random_engine{(unsigned)time(0)};
	std::shuffle(tiles.begin(), tiles.end(), rng);
}