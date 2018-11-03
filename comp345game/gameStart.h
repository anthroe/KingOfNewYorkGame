#pragma once
#include "Map.h"
#include "Region.h"
#include "dice.h"
#include "Maploader.h"
#include "player.h"
#include <string>
using namespace std;

class gameStart {

public:
	gameStart();
	vector<player> getPlayers();
	vector<string> ListOfMonsterCards;
private:
	dice * dice;
	Map * map;
	string * playerNames = NULL;
	int numberOfPlayers;
	int listMaps();
	void createPlayers();
	void selectMap();
	MonsterCard selectMonster();
	//bool operator==(const MonsterCard &o);
	inline bool fileExists(const string&);
	bool checkMonsterExists(string);
	void buildMonster();
	vector<player> playersInGame;

};
