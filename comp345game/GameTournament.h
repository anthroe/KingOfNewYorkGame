#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "player.h"
#include "map.h"

class GameTournament {

private:
	Map map;
	player* win;
	vector<player*> players;
	Deck* deck;
	int gameNumber;
	int maxTurns;

public:
	GameTournament(Map, vector<player*> p, int);
	void startGame();
	string getWinnerName();
};