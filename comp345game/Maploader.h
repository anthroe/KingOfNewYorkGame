//#ifndef MAP_LOADER_H_
//#define MAP_LOADER_H_
#pragma once
#include "Map.h"
#include <string>
#include <fstream>



class Maploader {

private:
	Map* mapInPlay;
	string readLine(ifstream&);
	string strip(string);
	vector<string> split(string, char);


public:
	Maploader();

	Maploader(string);

	~Maploader();

	Map* getMap();
	void parseMap(string);
};