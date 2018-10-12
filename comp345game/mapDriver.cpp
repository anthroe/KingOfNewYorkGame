
#include <iostream>
#include <fstream>
#include <sstream>
#include "Region.h"
#include "Maploader.h"
#include "Map.h"

using namespace std;

int mapDriver() {
//Map that does work
Region canada("canada", 1);
Region usa("usa", 2);
Region mexico("mexico", 3);

canada.addNearbyRegions({ usa, mexico });
usa.addNearbyRegions({ canada, mexico });
mexico.addNearbyRegions({ usa, canada });

vector<Region> randomRegions{canada, usa, mexico };
Map map1("New York", randomRegions);

if (map1.checkConnection()) {
	cout << "Map is Connected properly." << endl;
}
else {
	cout << "Map is NOT Connected properly." << endl;
}
system("pause");

//Map that does not work
Region montreal("montreal", 1);
Region toronto("toronto", 2);
Region edmonton("edmonton", 3);
Region newyork("newyork", 4);

montreal.addNearbyRegions({ montreal, newyork });
toronto.addNearbyRegions({ toronto, montreal });
edmonton.addNearbyRegions({ newyork, edmonton });
newyork.addNearbyRegions({ newyork, edmonton });

vector<Region> cityRegions{ montreal, toronto, edmonton, newyork };
Map map2("New York", cityRegions);

if (map2.checkConnection()) {
	cout << "Map is Connected properly." << endl;
}
else {
	cout << "Map is NOT Connected properly." << endl;
}
return 0;
}
