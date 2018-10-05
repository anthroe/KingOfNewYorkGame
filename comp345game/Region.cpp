#include <iostream>
#include "Region.h"

using namespace std;

Region::Region() {
	name = "no_name";
	//owner = null;
}

Region::Region(string name) {
	this->name = name;
}

Region::Region(string name, vector<Region*> nearbyRegions) {
	this->name = name;
	this->nearbyRegions = nearbyRegions;
}

//Region::Region(string name, Player owner) {
//	this->name = name;
//	this->owner = owner;
//}

//void::Region(Player owner) {
//	this->owner = owner;
//}

//Region::Region(string name, Player owner, vector<Region> nearbyRegions) {
//	this->name = name;
//	this->owner = owner;
//	this->nearbyRegions = nearbyRegions;
//}

void Region::addNearbyRegion(Region* region) {
	nearbyRegions.push_back(region);
}

void Region::addNearbyRegions(vector<Region*> regions) {
	for (int i = 0; i < regions.size(); i++) {
		nearbyRegions.push_back(regions[i]);
	}
}
