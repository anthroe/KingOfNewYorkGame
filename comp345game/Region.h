#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Region {
private:
	string name;
	//Player owner;
	vector<Region> nearbyRegions;

public:
	Region();
	Region(string);
	//Region(string, Player);
	Region(string, vector<Region>);

	string getName() { return name; }
	//Player getOwner { return owner }
	vector<Region> getNearbyRegions() { return nearbyRegions; }
	//vector<Player> getNearbyEnemies() { return nearbyEnemies; }

	//void setOwner(Player);
	void addNearbyRegion(Region);
	void addNearbyRegions(vector<Region>);

};
