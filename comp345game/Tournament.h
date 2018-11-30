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
	vector<Map> maps;
	vector<player*> players;
	int gamesToPlay;
	vector<GameTournament*> games;
	vector<Deck*> decks;
	Map cleanUpMap(Map);
	
public:
	void tournamentInitialization();
	void startTournament();
	void printReport();
	
};