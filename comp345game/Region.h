#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Region {
private:
	string name;
	int id;
	//Player owner;
	vector<Region> nearbyRegions;

public:
	Region();
	Region(string);
	Region(string, int);
	//Region(string, int, Player);
	//Region(string, int, vector<Region>);

	string getName() const { return name; }
	int getId() const { return id;  }
	//Player getOwner { return owner }
	vector<Region> getNearbyRegions() const { return nearbyRegions; }
	vector<int> getNearbyRegionIds();
	//vector<Player> getNearbyEnemies() { return nearbyEnemies; }

	void setId(int);

	//void setOwner(Player);
	void addNearbyRegion(Region);
	void addNearbyRegions(vector<Region>);

	bool operator==(const Region&);
};
