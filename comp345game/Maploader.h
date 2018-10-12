#pragma once

#include <string>
#include <fstream>
#include "Map.h"



class Maploader {

private:
	Map mapInPlay;

public:
	Maploader();
	Maploader(string);

	Map getMap() { return mapInPlay; }
};