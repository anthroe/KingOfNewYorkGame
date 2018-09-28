#include <iostream>
#include "Region.h"

using namespace std;

Region::Region() {
	name = "no_name";
}

Region::Region(string name) {
	this->name = name;
}

Region::Region(string name, vector<Region> nearbyRegions) {
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

void Region::addNearbyRegion(Region region) {
	nearbyRegions.push_back(region);
}
