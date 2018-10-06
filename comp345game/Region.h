#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Region {
private:
	string name;
	int id;
	//Player owner;
	vector<Region*> nearbyRegions;

public:
	Region();
	Region(string, int);
	//Region(string, int, Player);
	Region(string, int, vector<Region*>);

	string getName() { return name; }
	int getId() { return id;  }
	//Player getOwner { return owner }
	vector<Region*> getNearbyRegions() { return nearbyRegions; }
	vector<int> getNearbyRegionIds();
	//vector<Player> getNearbyEnemies() { return nearbyEnemies; }

	//void setOwner(Player);
	void addNearbyRegion(Region*);
	void addNearbyRegions(vector<Region*>);

};
