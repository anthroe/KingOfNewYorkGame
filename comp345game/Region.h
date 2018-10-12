#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Region {
private:
	string name;
	int id;
	vector<Region> nearbyRegions;

public:
	Region();
	Region(string, int);
	Region(string name, int id, vector<Region> nearbyRegions);
	Region (const Region&);

	string getName() const { return name; }
	int getId() const { return id;  }
	vector<Region> getNearbyRegions() const { return nearbyRegions; }
	vector<int> getNearbyRegionIds();
	

	void setId(int);

	void addNearbyRegion(Region);
	void addNearbyRegions(vector<Region>);

	bool operator==(const Region&);
};
