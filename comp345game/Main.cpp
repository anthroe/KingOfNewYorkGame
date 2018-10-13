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
#include "diceTest.h"
#include "cardtest.h"
#include "player.h"

using namespace std;

int main() {
	

	/*cout << "Loading player:" << endl;
	playerDriver();
	system("pause"); system("CLS");

	cout << "Loading test maps:" << endl;
	mapDriver();
	system("pause"); system("CLS");

	cout << "Rolling dice:" << endl;
	diceDriver();
	system("pause"); system("CLS");*/

	cout << "Loading cards:" << endl;
	cardDriver();
	system("pause"); system("CLS");
	
	/*cout << "Loading Map loader:" << endl;
	Maploader mapLoaded("test2Bidirectional.map");
	Map map(mapLoaded.getMap());	

	string input = "TestPlayer";
	player p1(input);

	vector<Region> mapRegions = map.getRegions();

	cout << p1.getName() + ", where would you like to move?" << endl;
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

	cout << p1.getName() + " is now in " + p1.getRegion().getName() << endl;*/
	
	system("pause");
	cout << "End of test." << endl;
 	return 0;
}