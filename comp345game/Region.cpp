#include <iostream>
#include "Region.h"

using namespace std;

Region::Region() {
	name = "no_name";
	id = 0;
	playerCount = 0;
	Neighbours = {};
}

Region::Region(string name, int id) {
	this->name = name;
	this->id = id;
	playerCount = 0;
	Neighbours = {};
}

vector<int> Region::getNeighbourIDs() {
	vector<Region*> neighbours = this->getNeighbours();
	vector<int> neighbourIds;

	for (int i = 0; i < neighbours.size(); i++) {
		neighbourIds.push_back((*neighbours[i]).getId());
	}

	return neighbourIds;
}

vector<Region*> Region::getNeighbours() {
	return Neighbours;
}

void Region::setID(int id) {
	this->id = id;
}

void Region::increasePlayerCount() {
	playerCount++;
}

void Region::reducePlayerCount() {
	if (playerCount > 0) {
		playerCount--;
	}
}

void Region::addNeighbour(Region* region) {
	Neighbours.push_back(region);
}

void Region::addNeighbours(vector<Region*> regions) {
	for (int i = 0; i < regions.size(); i++) {
		Neighbours.push_back(regions[i]);
	}
}

bool Region::operator==(const Region &o)
{
	return (this->getName() == o.getName() && this->getId() == o.getId());
}

Region::Region(const Region& region)
{
	if (this != &region)
		*this = region;
}