#pragma once
#include "Map.h"
#include <string>
#include <fstream>



class Maploader {

private:
	Map* mapInPlay;

public:
	Maploader();
	Maploader(string);
	~Maploader();
};