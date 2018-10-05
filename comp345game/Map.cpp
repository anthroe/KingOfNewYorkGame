#include <iostream>
#include <ostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Map.h"

using namespace std;

Map::Map() {

}

Map::Map(vector<Region*> regions) {
	this->regions = regions;
}

void Map::addRegion(Region* region) {
	regions.push_back(region);
}

Map::~Map() {
	while (regions.size() > 0) {
		//delete regions.back();		if using pointers
		regions.pop_back();
	}
}

bool Map::checkConnection() {
	vector<Region*> regions = this->regions;

	for (int i = 0; i < regions.size(); i++) {
		Region* currentRegion = regions[i];
		vector<Region*> neighbours = currentRegion->getNearbyRegions();

		cout << "Region: " + currentRegion->getName() << endl;
	
		for (int i = 0; i < neighbours.size(); i++) {
			Region* neighbour = neighbours[i];
			vector<Region*> innerNeighbours = neighbour->getNearbyRegions();

			cout << "	neighbour: " + neighbour->getName() << endl;

			for (int i = 0; i < innerNeighbours.size(); i++) {
				Region* innerNeighbour = innerNeighbours[i];

				cout << "		innerNeighbour: " + innerNeighbour->getName() << endl;
			}

			if (find(innerNeighbours.begin(), innerNeighbours.end(), currentRegion) == innerNeighbours.end()) {
				cout << "Region: " + currentRegion->getName() + " is not properly connected. Please load a proper map." << endl;
				return false;
			}
			
		}

	}

	return true;
};
