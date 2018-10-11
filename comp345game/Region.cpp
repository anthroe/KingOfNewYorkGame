#include <iostream>
#include "Region.h"

using namespace std;

Region::Region() {
	name = "no name";
	id = 0;
	owner = NULL;
}

Region::Region(string name, int id) {
	this->name = name;
	this->id = id;
	owner = NULL;
}

Region::Region(string name, int id, vector<Region> nearbyRegions) {
	this->name = name;
	this->id = id;
	this->nearbyRegions = nearbyRegions;
	owner = NULL;
}
player* Region::getOwner() {
	return owner;
}
void Region::setOwner(player* player, Region region) {
	owner = player;
}


//Some copy constructor, check if we need this
//Region::Region(const Region& region)
//{
//	if (this != &region)
//		*this = region;
//}

Region::Region(string name, int id, player* owner) {
	this->name = name;
	this->id = id;
	this->owner = owner;
}

Region::Region(string name, int id, player* owner, vector<Region> nearbyRegions) {
	this->name = name;
	this->id = id;
	this->owner = owner;
	this->nearbyRegions = nearbyRegions;
}

vector<int> Region::getNearbyRegionIds() {
	vector<Region> neighbours = this->getNearbyRegions();
	vector<int> neighbourIds;

	for (int i = 0; i < neighbours.size(); i++) {
		neighbourIds.push_back(neighbours[i].getId());
	}

	return neighbourIds;
}

void Region::setId(int id) {
	this->id = id;
}

void Region::addNearbyRegion(Region region) {
	nearbyRegions.push_back(region);
}

void Region::addNearbyRegions(vector<Region> regions) {
	for (int i = 0; i < regions.size(); i++) {
		nearbyRegions.push_back(regions[i]);
	}
}

bool Region::operator==(const Region &o)
{
	return (this->getName() == o.getName() && this->getId() == o.getId());
}