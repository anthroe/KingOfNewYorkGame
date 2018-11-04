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
	/*
	for (int i = 0; i < regions.size(); i++) {
		this->regions.push_back(regions[i]);
	}*/
}

Map::Map(vector<Region*> regions) {
	name = "no_name";
	for (int i = 0; i < regions.size(); i++) {
		this->regions.push_back((*regions[i]));
	}
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
	vector<Region> regionList = this->regions;
	Region trivialRegion = regionList[0];

	for (int i = 1; i < regionList.size()-1; i++) {
		vector<Region*> neighbours = regionList[i].getNeighbours();

		if (neighbours.size() == 0 || (neighbours.size() == 1 && neighbours[0] == &trivialRegion)) {
			return false;
		}

		trivialRegion = regionList[i];
	}

	return true;
}