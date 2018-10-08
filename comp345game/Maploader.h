//#ifndef MAP_LOADER_H_
//#define MAP_LOADER_H_
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