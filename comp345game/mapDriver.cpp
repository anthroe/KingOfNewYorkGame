/*
#include <iostream>
#include <fstream>
#include <sstream>
#include "Region.h"
#include "Maploader.h"


using namespace std;

int main() {

Region canada("canada");
Region usa("usa");
Region mexico("mexico");

canada.addNearbyRegions({ &usa, &mexico });
usa.addNearbyRegions({ &canada, &mexico });
mexico.addNearbyRegions({ &usa, &canada });

vector<Region*> randomRegions{ &canada, &usa, &mexico };
Map map1(randomRegions);

if (map1.checkConnection()) {
	cout << "Map is Connected properly." << endl;
}
system("pause");

return 0;
}
*/