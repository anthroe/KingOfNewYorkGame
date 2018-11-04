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
#include "gameStart.h"
#include "startup.h"
using namespace std;

int main() {

	gameStart();
	startup();
	//Maploader loadMap("test1GameMap.map");
	//Map map = loadMap.getMap();
	//vector<Region> regions = loadMap.getMap().getRegions();

	/*player p1("david");
	player p2("anthony");
	player p3("lucas");
	player p4("walid");
	player p5("urmom");
	player p6("urdad");

	p1.setRegion(&regions[3]);
	p2.setRegion(&regions[3]);
	p3.setRegion(&regions[4]);
	p4.setRegion(&regions[4]);
	p5.setRegion(&regions[5]);
	p6.setRegion(&regions[6]);
	
	vector<player> playerlist = { p1, p2, p3, p4, p5, p6 };*/

 	/*for (player player : playerlist) {
		player.move_kony();
	}*/

	cout << "We did it!" << endl;


	/*gameStart();
	cout << "have I entered the loop?" << endl;
	for (player player : gameStart::playersInGame) {
			cout << player.getName() << endl;
	}*/

	system("pause");
	cout << "End of test." << endl;
 	return 0;

}