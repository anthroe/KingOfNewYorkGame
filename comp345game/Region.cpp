#include <iostream>
#include "Region.h"

using namespace std;

Region::Region() {
	name = "no_name";
	id = 0;
	//owner = null;
}

Region::Region(string* name) {
	this->name = name;
	id = 0;
}

Region::Region(string* name, int id) {
	this->name = name;
	this->id = id;
}

Region::Region(string* name, int id, vector<Region*> nearbyRegions) {
	this->name = name;
	this->id = id;
	this->nearbyRegions = nearbyRegions;
}

/*
Some copy constructor, check if we need this
Region::Region(const Region& region)
{
	if (this != &region)
		*this = region;
}
*/

//Region::Region(string name, int id, Player owner) {
//	this->name = name;
//	this->id = id;
//	this->owner = owner;
//}

//Region::Region(string name, int id, Player owner, vector<Region> nearbyRegions) {
//	this->name = name;
//	this->id = id;
//	this->owner = owner;
//	this->nearbyRegions = nearbyRegions;
//}

vector<int> Region::getNearbyRegionIds() {
	vector<Region*> neighbours = this->getNearbyRegions();
	vector<int> neighbourIds;

	for (int i = 0; i < neighbours.size(); i++) {
		neighbourIds.push_back(neighbours[i]->getId());
	}

	return neighbourIds;
}

void Region::setId(int id) {
	this->id = id;
}

void Region::addNearbyRegion(Region* region) {
	nearbyRegions.push_back(region);
}

void Region::addNearbyRegions(vector<Region*> regions) {
	for (int i = 0; i < regions.size(); i++) {
		nearbyRegions.push_back(regions[i]);
	}
}