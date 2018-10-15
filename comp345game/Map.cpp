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
checkConnection method will verify that all regions have a bidirectional connection. 
Each region will be iterated through and their neighbours' Ids will be stored in a vector during the process.
The neighbours of the regions containing the Ids in this vector will be verified.
A region is considered bidirectional to another if its neighbours have that very region as their neighbour as well. 
Therefore, checkConnection will return false the moment a region's neighbour does not have that very region as its own neighbour. 
*/
bool Map::checkConnection() {
	vector<Region> regions = this->regions;

	for (int i = 0; i < regions.size(); i++) {
		Region currentRegion = regions[i];
		int currentRegionId = currentRegion.getId();
		vector<int> neighbourIds = currentRegion.getNearbyRegionIds();

		cout << "Region: " + currentRegion.getName() << endl;

		for (int i = 0; i < neighbourIds.size(); i++) {

			int currentNeighbourId = neighbourIds[i];
			int currentNeighbourIndex = 0;

			for (int i = 0; i < regions.size(); i++) {
				if (regions[i].getId() == currentNeighbourId) {
					currentNeighbourIndex = i;
				}
			}

			Region currentNeighbour = regions[currentNeighbourIndex];
			vector<int> innerNeighbours = currentNeighbour.getNearbyRegionIds();

			cout << currentNeighbour.getName() << endl;

			if (find(innerNeighbours.begin(), innerNeighbours.end(), currentRegionId) == innerNeighbours.end()) {
				cout << "Region: " + currentRegion.getName() + " is not properly connected. Please load a proper map." << endl;
				return false;
			}

		}

	}
	cout << "The map has been connected successfully." << endl;
	return true;
};

/*
Static verification for one directional maps
	*I'm leaving this here in case it becomes useful

vector<int> a1 = { 2, 3, 4, 5 };
vector<int> a2 = { 1, 3, 4, 5 };
vector<int> a3 = { 1, 2, 4, 5 };
vector<int> a4 = { 1, 2, 3, 5 };
vector<int> a5 = { 1, 2, 3, 4, 6 };
vector<int> a6 = { 1, 2, 3, 4, 7 };
vector<int> a7 = { 1, 2, 3, 4 };
vector<int> a7 = { 1, 2, 3, 4, 5 };

bool Map::checkConnection() {
	vector<Region> regions = this->regions;

	for (int i = 0; i < regions.size(); i++) {
		Region currentRegion = regions[i];
		int id = currentRegion.getId();


		switch (id) {
		case 1:
			if (currentRegion.getNearbyRegionIds() != a1)
				return false;
			break;

		case 2:
			if (currentRegion.getNearbyRegionIds() != a2)
				return false;
			break;

		case 3:
			if (currentRegion.getNearbyRegionIds() != a3)
				return false;
			break;

		case 4:
			if (currentRegion.getNearbyRegionIds() != a4)
				return false;

			break;

		case 5:
			if (currentRegion.getNearbyRegionIds() != a5)
				return false;
			break;

		case 6:
			if (currentRegion.getNearbyRegionIds() != a6)
				return false;
			break;

		case 7:
			if (currentRegion.getNearbyRegionIds() != a7)
				return false;
			break;
		}

	}

	cout << "we made it " << endl;

	return true;
}
*/
