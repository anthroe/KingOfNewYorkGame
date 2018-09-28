#include <iostream>
#include <vector>
#include "Region.h"

using namespace std;

class Map {
private:
	vector<Region> regions;

public:
	Map();
	Map(vector<Region>);

	bool checkConnection();
};