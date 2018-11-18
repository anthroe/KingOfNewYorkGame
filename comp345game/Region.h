#pragma once
#include <iostream>
#include <vector>
#include "tiles.h"

using namespace std;

class Region {
private:
	static const int BUILDING_UNIT_SIZE = 3;
	string name;
	int id;
	int playerCount;
	vector<Region> Neighbours;
	vector<vector<int>> buildings;
	vector<vector<int>> units;

public:
	Region();
	Region(string, int);
	Region(string, int, Tiles);
	Region (const Region&);
	~Region();

	string getName() const { return name; }
	int getId() const { return id;  }
	vector<Region> getNeighbours();
	vector<int> getNeighbourIDs();
	int getPlayerCount() { return playerCount; }

	void setID(int);
	void increasePlayerCount();
	void decreasePlayerCount();
	void setPlayerCount(int);
	void addNeighbour(Region);
	void addNeighbours(vector<Region>);

	vector<vector<int>> getBuildings() { return buildings; };
	vector<vector<int>> getUnits() { return units; };
	void flipTile(int, int);

	bool operator==(const Region&);
	bool operator!=(const Region&);
};
