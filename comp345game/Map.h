#pragma once
#include <iostream>
#include <vector>
#include "Region.h"

using namespace std;

class Map {
private:
	string cityName;
	vector<Region> regions;

public:
	Map();
	Map(vector<Region>);
	~Map();

	vector<Region> getRegions() { return regions; };

	void addRegion(Region);

	bool checkConnection();


};