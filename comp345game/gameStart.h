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
	gameStart(/*int numberOfPlayers, string* playerNames*/);
	~gameStart();
	//void Load(string mapName);
	//int playGame();
	vector<player*> getPlayers();
private:
	dice * dice;
	Map * map;
	string * playerNames;
	int numberOfPlayers;
	int listMaps();
	void createPlayers();
	vector<player*> playersInGame;

};
