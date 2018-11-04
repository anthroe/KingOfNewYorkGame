#pragma once
#include "Map.h"
#include "Region.h"
#include "dice.h"
#include "Maploader.h"
#include "player.h"
#include <string>

using namespace std;

class gameStart {

private:

	Map map;
	vector<Region> mapRegions;
	dice* dice;
	int numberOfPlayers;
	vector<player> playersInGame;
	vector<string> ListOfMonsterCards;

public:

	gameStart();
	vector<player> getPlayers() { return playersInGame; }

	int listMaps();
	MonsterCard selectMonster();
	inline bool fileExists(const string&);
	bool checkMonsterExists(string);

	void selectMap();
	void createPlayers();
	void buildMonster();

};
