#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Region {
private:
	string name;
	int id;
	int playerCount;
	vector<Region*> Neighbours;

public:
	Region();
	Region(string, int);
	Region (const Region&);

	string getName() const { return name; }
	int getId() const { return id;  }
	vector<Region*> getNeighbours();
	vector<int> getNeighbourIDs();
	int getPlayerCount() { return playerCount; }

	void setID(int);
	void increasePlayerCount();
	void reducePlayerCount();
	void addNeighbour(Region*);
	void addNeighbours(vector<Region*>);

	bool operator==(const Region&);
};
