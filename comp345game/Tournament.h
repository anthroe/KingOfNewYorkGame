#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "GameTournament.h"
#include "IPlayerType.h"
#include "map.h"
#include "Deck.h"

class Map;
class Player;
class Tournament {

private:
	Map map;
	vector<player*> players;
	int gamesToPlay;
	vector<GameTournament*> games;
	vector<Deck*> decks;
	
public:
	void cleanUpMap();
	void tournamentInitialization();
	void startTournament();
	void printReport();
	
};