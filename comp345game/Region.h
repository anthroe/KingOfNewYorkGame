#pragma once
#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

class Region {
private:
	string name;
	int id;
	player* owner;
	vector<Region> nearbyRegions;

public:
	Region();
	Region(string, int);
	Region(string, int, player*);
	Region(string name, int id, vector<Region> nearbyRegions);
	Region(string name, int id, player owner);
	Region(string, int, player*, vector<Region> regions);

	player* getOwner();
	void setOwner(player* player, Region region);

	string getName() const { return name; }
	int getId() const { return id;  }
	//player::getRegions{ return regions }
	vector<Region> getNearbyRegions() const { return nearbyRegions; }
	vector<int> getNearbyRegionIds();
	

	void setId(int);

	//void setOwner(Player);
	void addNearbyRegion(Region);
	void addNearbyRegions(vector<Region>);

	bool operator==(const Region&);
};
