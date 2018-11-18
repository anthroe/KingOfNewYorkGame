#pragma once

#include <string>
#include <fstream>
#include "Map.h"
#include "tiles.h"



class Maploader {
private:
	Map mapInPlay;
public:
	Maploader();
	Maploader(string);
	~Maploader();
	Map getMap() { return mapInPlay; }
};