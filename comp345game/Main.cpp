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
using namespace std;

int main() {

	//gameStart();

	Region r1("canada", 1);
	Region r2("usa", 2);
	Region r3("mexico", 3);

	r1.addNeighbours({ &r2, &r3 });
	r2.addNeighbours({ &r1, &r3 });
	r3.addNeighbours({ &r1, &r2 });

	player p1("david");
	player p2("anthony");

	p1.setRegion(&r1);
	p1.move();

	system("pause");
	cout << "End of test." << endl;
 	return 0;
}