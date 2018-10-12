//#include "cardtest.cpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Region.h"
#include "Maploader.h"
#include "playerDriver.h"
#include "mapDriver.h"
//#include "diceDriver.h"
#include "cardtest.h"
#include "player.h"

using namespace std;

int main() {
	string input;

	Maploader mapLoaded("test2Bidirectional.map");
	Map map(mapLoaded.getMap());
	//playerDriver();
	//mapDriver();
	//diceDriver();
	//cardDriver();

	cout << "What is your name?" << endl;
	cin >> input;
	player p1(input);

	vector<Region> mapRegions = map.getRegions();

	cout << "Where would you like to move to " + p1.getName() << endl;
	cin >> input;

	int position = -1;

	while (position < 0) {
		for (int i = 0; i < mapRegions.size(); i++) {
			if (mapRegions[i].getName() == input) {
				position = i;
				break;
			}
		}

		if (position < 0) {
			cout << "That region does not exist. Enter a correct Region." << endl;
			cin >> input;
		}
	}

	p1.move(mapRegions[position]);

	cout << p1.getName() + " is now in " + p1.getRegion().getName() << endl;

	system("pause");
 	return 0;
}