#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "./Player.h"
#include "./Map.h"
#include "./Region.h"

class startup {
private:
	vector<player*> playerOrder;
	Map* currMap;

	void clearScreen();

public:
	startup(/*vector<player*>, Map* */);
	startup(/* vector<player*> players, Map* map, bool quickStart */);
	void randomPlayerOrder();

	vector<player*> getPlayerOrder();
};
