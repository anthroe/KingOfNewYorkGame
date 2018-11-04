#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Map.h"

using namespace std;

Map::Map() {
	name = "none";
	regions = {};
}

Map::Map(string name) {
	this->name = name;
}

Map::Map(string name, vector<Region> regions) {
	this->name = name;
	this->regions = regions;
}

void Map::addRegion(Region region) {
	regions.push_back(region);
}

Map::~Map() {
	while (regions.size() > 0) {
		regions.pop_back();
	}
}
/*
Verify that all regions are connected in some way, be it directly or through neighbors.
*/

bool Map::checkConnection() {
	vector<Region> regions = this->regions;
	Region* trivialRegion = &regions[0];

	for (int i = 1; i < regions.size()-1; i++) {
		vector<Region*> neighbours = regions[i].getNeighbours();

		if (neighbours.size() == 0 || (neighbours.size() == 1 && neighbours[0] == trivialRegion)) {
			return false;
		}

		trivialRegion = &regions[i];
	}

	return true;
}