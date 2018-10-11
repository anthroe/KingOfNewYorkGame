#pragma once
#ifndef UNITTILES_H
#define UNITTILES_H
#include <vector>

using namespace std;

class UnitTiles {
	private:
		vector<int> unitTiles;

	public:
		UnitTiles();
		vector<int> getTiles() { return unitTiles; };
		void shuffle();
};

#endif
