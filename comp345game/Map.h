#pragma once
#include <iostream>
#include <vector>
#include "Region.h"

using namespace std;

class Map {
private:
	string name;
	vector<Region> regions;

public:
	Map();
	Map(string);
	Map(vector<Region*>);
	Map(string, vector<Region>);
	~Map();

	vector<Region> getRegions() { return regions; };

	void update(vector<Region>);

	void addRegion(Region);

	bool checkConnection();

};