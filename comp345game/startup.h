#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>
#include "./Player.h"
#include "./Map.h"
#include "./Region.h"

class startup {
private:
	vector<player> playerOrder;
	Map currMap;

public:
	startup();
	void decidePlayerOrder();
	void chooseStartingRegion();
	
};
