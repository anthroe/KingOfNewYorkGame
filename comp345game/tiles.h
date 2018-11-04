#pragma once
#ifndef TILES_H
#define TILES_H
#include <vector>

using namespace std;

class Tiles {
	private:
		vector<int> tiles;

	public:
		Tiles();
		vector<int> getTiles() { return tiles; };
		bool removeFirstTile();
		static int flipTile(int);
		void shuffle();
};

#endif
