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
#include "mainLoop.h"

using namespace std;

int main() {

	gameStart();
	startup();
	//mainLoop();

	for (int i = 0; i < gameStart::playersInGame.size(); i++) {

	}

	system("pause");
	cout << "End of test." << endl;
 	return 0;

}