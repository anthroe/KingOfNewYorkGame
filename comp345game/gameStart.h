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

	Map* map;
	dice* dice;
	int numberOfPlayers;
	vector<Region*> mapRegions;

	vector<string> ListOfMonsterCards;

public:
	static vector<player> playersInGame;
	gameStart();
	vector<player> getPlayers() { return playersInGame; }

	int listMaps();
	void selectMonster(player *currPlayer);
	inline bool fileExists(const string&);
	bool checkMonsterExists(string);

	void selectMap();
	void createPlayers();
	void buildMonster();

};
